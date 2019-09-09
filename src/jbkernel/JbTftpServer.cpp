/**
 * @file
 * @brief JbTftp Server class Realization
 *
 * @author   Evgeniy Ivanov <strelok1290@gmail.com>
 *			 Logan Gunthorpe <logang@deltatee.com>
 *           Dirk Ziegelmeier <dziegel@gmx.de>
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * Copyright © Deltatee Enterprises Ltd. 2013
 * All rights reserved.
 *
 * @note
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 * @note
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @note
 * This file is a part of JB_Lib.
 */

// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "string.h"
#include "jbkernel/JbTftpServer.hpp"
#include "jbkernel/TimeEngine.hpp"
#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
#include "stdio.h"
#endif

#define JB_TFTP_SERVER_HEADER_LENGTH    4

#ifndef PP_HTONS
#define PP_HTONS(x) ((uint16_t)((((x) & (uint16_t)0x00ffU) << 8) | (((x) & (uint16_t)0xff00U) >> 8)))
#endif

#ifndef PP_HTONL
#define PP_HTONL(x) ((((x) & (uint32_t)0x000000ffUL) << 24) | \
                     (((x) & (uint32_t)0x0000ff00UL) <<  8) | \
                     (((x) & (uint32_t)0x00ff0000UL) >>  8) | \
                     (((x) & (uint32_t)0xff000000UL) >> 24))
#endif

namespace jblib::jbkernel
{

enum JbTftpPacketType_t
{
	JBTFTP_PACKET_TYPE_RRQ			= 1,
	JBTFTP_PACKET_TYPE_WRQ			= 2,
	JBTFTP_PACKET_TYPE_DATA			= 3,
	JBTFTP_PACKET_TYPE_ACK			= 4,
	JBTFTP_PACKET_TYPE_ERROR		= 5,
	JBTFTP_PACKET_TYPE_RFRSH		= 0xFF00,
	JBTFTP_PACKET_TYPE_FRMT			= 0xFF01,
	JBTFTP_PACKET_TYPE_DEL			= 0xFF02,
	JBTFTP_PACKET_TYPE_LIST_REQUEST	= 0xFF03,
	JBTFTP_PACKET_TYPE_LIST_REPLY	= 0xFF04,
	JBTFTP_PACKET_TYPE_INF			= 0xFF05,
	JBTFTP_PACKET_TYPE_SPC			= 0xFF06,
};



JbTftpServer::JbTftpServer(IVoidFileSystem* fileSystem,
		IVoidChannel* channel, uint8_t nrtTimerNum) : IVoidCallback()
{
	this->nrtTimerNum_ = nrtTimerNum;
	this->fileSystem_ = fileSystem;
	this->channel_ = channel;
	this->msgQueue_ = new VoidChannelMsgQueue(this);
}



JbTftpServer::~JbTftpServer(void)
{
	delete (this->msgQueue_);
}



void JbTftpServer::initialize(void)
{
	if(!this->isInitialized_){
		this->channel_->initialize(malloc_s, JB_TFTP_SERVER_HEADER_LENGTH +
				JB_TFTP_SERVER_MAX_PAYLOAD_SIZE, this->msgQueue_);
		this->timerCounter_ = 0;
		this->lastData_ = NULL;
		this->channelParameter_ = NULL;
		this->file_ = NULL;
		this->lastPacketTime_ = 0;
		this->retries_ = 0;
		this->blockNumber_ = 0;
		this->writeMode_ = false;
		this->lastDataSize_ = 0;
		this->isInitialized_ = true;
	}
}



void JbTftpServer::deInitialize(void)
{
	if(this->isInitialized_){
		this->close();
		if(this->isTimerEnabled_)
			return;
		this->channel_->deinitialize();
		this->timerCounter_ = 0;
		this->lastPacketTime_ = 0;
		this->retries_ = 0;
		this->blockNumber_ = 0;
		this->writeMode_ = false;
		this->isInitialized_ = false;
	}
}


bool JbTftpServer::isInitialized(void)
{
	return this->isInitialized_;
}



void JbTftpServer::close(void)
{
	if(this->channelParameter_){
		free_s(((IVoidChannel::ConnectionParameter_t*)this->channelParameter_)->
				parameters);
		free_s(this->channelParameter_);
		this->channelParameter_ = NULL;
	}
	if(this->lastData_){
		free_s(this->lastData_);
		this->lastData_ = NULL;
		this->lastDataSize_ = 0;
	}
	if(this->file_){
		this->fileSystem_->closeFile(this->file_);
		this->file_ = NULL;
	}
	#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
	printf("JbTftp Closing\n");
	#endif
}



void JbTftpServer::voidCallback(void* const source, void* parameter)
{
	if(source == (void*)this->msgQueue_){
		VoidChannelMsgQueue::ChannelMessage_t* msg =
				(VoidChannelMsgQueue::ChannelMessage_t*)parameter;
		uint16_t size = msg->dataSize;
		uint8_t* buffer = msg->data;
		if(size < 2)
			return;
		if((this->channelParameter_) &&
				(memcmp(((IVoidChannel::ConnectionParameter_t*)this->channelParameter_)->parameters,
						msg->connectionParam->parameters, msg->connectionParam->parametersSize))){
			#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
			printf("JbTftp: Only one connection at a time is supported, channel parameters not equal\n");
			#endif
			this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
					"Only one connection at a time is supported");
			return;
		}
		uint16_t opcode = PP_HTONS(((uint16_t*)buffer)[0]);
		this->lastPacketTime_ = this->timerCounter_;
		this->retries_ = 0;

		switch(opcode){
			case JBTFTP_PACKET_TYPE_RRQ:
			case JBTFTP_PACKET_TYPE_WRQ:
			{
				if(this->file_){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp: Only one connection at a time is supported\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Only one connection at a time is supported");
					break;
				}

				if(!this->isTimerEnabled_){
					this->isTimerEnabled_ = true;
					TimeEngine::getTimeEngine()->setNrtEvent(this->nrtTimerNum_,
							1000* JB_TFTP_SERVER_TIMER_MS, this, NULL);
				}

				char* fileName = (char*)&buffer[2];
				char* mode = (char*)memchr(fileName, 0, size - 2);
				if(!mode){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Filename not NULL terminated\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Filename not NULL terminated");
					break;
				}
				uint16_t fileNameLen = strlen(fileName) + 1;
				if((fileNameLen == 1) || ((size - 2 - fileNameLen) <= 1)){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: No mode/not NULL terminated/File name is empty\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"No mode/not NULL terminated/File name is empty");
					break;
				}
				mode++;
				char* options = (char*)memchr(mode, 0, size - 2 - fileNameLen);
				if(!options){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Mode not NULL terminated\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Mode not NULL terminated");
					break;
				}

				if(strcmp(mode, "octet")){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Unsupported mode %s\n", mode);
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Unsupported mode");
					break;
				}

				uint8_t openMode = (opcode == JBTFTP_PACKET_TYPE_WRQ) ?
						(FA_CREATE_ALWAYS | FA_WRITE) : (FA_OPEN_EXISTING | FA_READ);
				this->file_ = this->fileSystem_->openFile(fileName, openMode);
				this->blockNumber_ = 1;

				if(!this->file_){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Unable to open requested file\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_FILE_NOT_FOUND, "Unable to open requested file");
					break;
				}

				#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
				printf("JbTftp: %s request for '%s' mode '%s'\n",
						(opcode == PP_HTONS(JBTFTP_PACKET_TYPE_WRQ)) ? "write" : "read",
								fileName, mode);
				#endif

				if(msg->connectionParam){
					IVoidChannel::ConnectionParameter_t* chParam =
							(IVoidChannel::ConnectionParameter_t*)malloc_s(
									sizeof(IVoidChannel::ConnectionParameter_t));
					if(!chParam){
						#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
						printf("JbTftp Error: No heap\n");
						#endif
						this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
								"No heap memory");
						break;
					}
					chParam->parameters = malloc_s(msg->connectionParam->parametersSize);
					if(!chParam->parameters){
						free_s(chParam);
						#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
						printf("JbTftp Error: No heap\n");
						#endif
						this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
								"No heap memory");
						return;
					}

					chParam->parametersSize = msg->connectionParam->parametersSize;
					memcpy(chParam->parameters, msg->connectionParam->parameters,
							msg->connectionParam->parametersSize);
					this->channelParameter_ = chParam;
				}
				else
					this->channelParameter_ = NULL;

				if(opcode == JBTFTP_PACKET_TYPE_WRQ) {
					this->writeMode_ = true;
					this->sendAck(0);
				}
				else {
					this->writeMode_ = false;
					this->sendData();
				}
			}
			break;

			case JBTFTP_PACKET_TYPE_DATA:
			{
				if(!this->file_){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: No connection\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION, "No connection");
					break;
				}
				if(!this->writeMode_){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Not a write connection\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION, "Not a write connection");
					break;
				}

				uint16_t blockNumber = PP_HTONS(((uint16_t*)buffer)[1]);
				if (blockNumber == this->blockNumber_) {
					uint16_t dataSize = size - JB_TFTP_SERVER_HEADER_LENGTH;
					int ret = this->fileSystem_->writeFile(this->file_,
							&buffer[JB_TFTP_SERVER_HEADER_LENGTH], dataSize);
					if (ret < 0) {
						#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
						printf("JbTftp Error: Error writing file ret = %i\n", ret);
						#endif
						this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION, "error writing file");
						this->close();
					}
					else if(ret < dataSize){
						#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
						printf("JbTftp Error: Disk Full, need %u ret %i\n", dataSize, ret);
						#endif
						this->sendError(msg->connectionParam, JBTFTP_ERROR_DISK_FULL, "disk full");
						this->close();
					}
					else {
						this->sendAck(blockNumber);
					}
					if(dataSize < JB_TFTP_SERVER_MAX_PAYLOAD_SIZE){
						this->close();
					}
					else{
						this->blockNumber_++;
					}
				} else if ((uint16_t)(blockNumber + 1) == this->blockNumber_) {
					this->sendAck(blockNumber);
				} else {
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Wrong block number\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_UNKNOWN_TRFR_ID, "Wrong block number");
				}
			}
			break;

			case JBTFTP_PACKET_TYPE_ACK:
			{
				if(!this->file_){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: No connection\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION, "No connection");
					break;
				}
				if(this->writeMode_){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Not a read connection\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION, "Not a read connection");
					break;
				}

				uint16_t blockNumber = PP_HTONS(((uint16_t*)buffer)[1]);
				if (this->blockNumber_ != blockNumber) {
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Wrong block number\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_UNKNOWN_TRFR_ID, "Wrong block number");
					break;
				}
				bool lastPacket = false;
				if(!this->lastData_) {
					lastPacket = (this->lastDataSize_ != (JB_TFTP_SERVER_MAX_PAYLOAD_SIZE +
							JB_TFTP_SERVER_HEADER_LENGTH));
				}
				if (!lastPacket) {
					this->blockNumber_++;
					this->sendData();
				} else {
					this->close();
				}
			}
			break;

			case JBTFTP_PACKET_TYPE_FRMT:
			{
				this->fileSystem_->format();
				this->sendRefresh(msg->connectionParam);
			}
			break;

			case JBTFTP_PACKET_TYPE_DEL:
			{
				char* fileName = (char*)&buffer[2];
				char* res = (char*)memchr(fileName, 0, size - 2);
				if(!res){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Filename not NULL terminated\n");
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Filename not NULL terminated");
					break;
				}
				this->fileSystem_->remove(fileName);
				this->sendRefresh(msg->connectionParam);
			}
			break;

			case JBTFTP_PACKET_TYPE_LIST_REQUEST:
			{
				std::string list;
				uint16_t listSize = 0;
				list.append(sizeof(uint16_t), '\0');
				list.append(sizeof(uint16_t), '\0');
				int result = this->fileSystem_->getList(list, &listSize, (char*)"");
				if(result){
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Get list error %i\n", result);
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Get list error");
				}
				else{
					uint16_t replyOpcode = JBTFTP_PACKET_TYPE_LIST_REPLY;
					list[0] = (replyOpcode >> 8) & 0xff;
					list[1] = replyOpcode & 0xff;
					list[2] = (listSize >> 8) & 0xff;
					list[3] = listSize & 0xff;
					this->channel_->tx((uint8_t*)list.c_str(),
							list.size(), msg->connectionParam);
				}
			}
			break;

			case JBTFTP_PACKET_TYPE_INF:
			{
				IVoidFileSystem::VoidFileSystemInfo_t info;
				int result = this->fileSystem_->getInfo(&info);
				if(!result){
					uint32_t replySize = 2 + sizeof(IVoidFileSystem::VoidFileSystemInfo_t);
					uint8_t* reply = (uint8_t*)malloc_s(replySize);
					if(reply){
						((uint16_t*)reply)[0] = PP_HTONS(JBTFTP_PACKET_TYPE_SPC);
						info.totalSize = PP_HTONL(info.totalSize);
						info.freeSize = PP_HTONL(info.freeSize);
						memcpy(&reply[2], (void*)&info, sizeof(IVoidFileSystem::VoidFileSystemInfo_t));
						this->channel_->tx(reply, replySize, msg->connectionParam);
						free_s(reply);
					}
					else{
						#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
						printf("JbTftp Error: Get info error no mem\n");
						#endif
						this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
								"Get info error, no mem");
					}
				}
				else{
					#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
					printf("JbTftp Error: Get info error %i\n", result);
					#endif
					this->sendError(msg->connectionParam, JBTFTP_ERROR_ACCESS_VIOLATION,
							"Get info error");
				}
			}
			break;

			default:
			{
				#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
				printf("JbTftp Error: Unknown operation %u\n", opcode);
				#endif
				this->sendError(msg->connectionParam, JBTFTP_ERROR_ILLEGAL_OPERATION,
						"Unknown operation");
			}
			break;
		}
	}
	else{
		this->timerCounter_++;
		if(!this->file_){
			this->isTimerEnabled_ = false;
			return;
		}

		this->isTimerEnabled_ = true;
		TimeEngine::getTimeEngine()->setNrtEvent(this->nrtTimerNum_,
				1000* JB_TFTP_SERVER_TIMER_MS, this, NULL);

		if ((this->timerCounter_ - this->lastPacketTime_) > (JB_TFTP_SERVER_TIMEOUT_MS / JB_TFTP_SERVER_TIMER_MS)) {
			if ((this->lastData_) && (this->retries_ < JB_TFTP_SERVER_MAX_RETRIES)) {
				#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
				printf("JbTftp: timeout, retrying\n");
				#endif
				this->resendData();
				this->retries_++;
			}
			else {
				#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
				printf("JbTftp: timeout\n");
				#endif
				this->close();
			}
		}
	}
}



void JbTftpServer::sendRefresh(void* channelParams)
{
	uint16_t refresh = PP_HTONS(JBTFTP_PACKET_TYPE_RFRSH);
	this->channel_->tx((uint8_t*)&refresh, sizeof(refresh), channelParams);
}



void JbTftpServer::resendData(void)
{
	this->channel_->tx(this->lastData_, this->lastDataSize_, this->channelParameter_);
}



void JbTftpServer::sendAck(uint16_t blockNumber)
{
	uint16_t ack[] = {
			PP_HTONS(JBTFTP_PACKET_TYPE_ACK),
			PP_HTONS(blockNumber)
	};
	this->channel_->tx((uint8_t*)ack, sizeof(ack), this->channelParameter_);
}



void JbTftpServer::sendData(void)
{
	if(this->lastData_){
		free_s(this->lastData_);
		this->lastDataSize_ = 0;
	}
	this->lastData_ = (uint8_t*)malloc_s(JB_TFTP_SERVER_MAX_PAYLOAD_SIZE +
			JB_TFTP_SERVER_HEADER_LENGTH);
	if(!this->lastData_){
		#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
		printf("JbTftp: Error send data, no heap\n");
		#endif
		return;
	}
	((uint16_t*)this->lastData_)[0] = PP_HTONS(JBTFTP_PACKET_TYPE_DATA);
	((uint16_t*)this->lastData_)[1] = PP_HTONS(this->blockNumber_);
	int ret = this->fileSystem_->readFile(this->file_, &(((uint16_t*)this->lastData_)[2]),
			JB_TFTP_SERVER_MAX_PAYLOAD_SIZE);
	if(ret < 0){
		#if USE_CONSOLE && JB_TFTP_SERVER_USE_CONSOLE
		printf("JbTftp Error: Error occurred while reading the file.\n");
		#endif
		this->sendError(this->channelParameter_, JBTFTP_ERROR_ACCESS_VIOLATION, "Error occurred while reading the file.");
		this->close();
		return;
	}
	this->lastDataSize_ = JB_TFTP_SERVER_HEADER_LENGTH + ret;
	this->resendData();
}



void JbTftpServer::sendError(void* channelParameter, JbTftpErrorCode_t code,
		const char* description)
{
	int descriptionLen = strlen(description);
	uint16_t dataSize = JB_TFTP_SERVER_HEADER_LENGTH +
			descriptionLen + 1;
	uint8_t* data = (uint8_t*)malloc_s(dataSize);
	if(!data)
		return;

	((uint16_t*)data)[0] = PP_HTONS(JBTFTP_PACKET_TYPE_ERROR);
	((uint16_t*)data)[1] = PP_HTONS(code);
	memcpy(&(((uint16_t*)data)[2]), description, descriptionLen + 1);
	this->channel_->tx(data, dataSize, channelParameter);
	free_s(data);
}

}
