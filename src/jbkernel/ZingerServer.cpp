/**
 * @file
 * @brief Zinger server class realization
 *
 *
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * Copyright © 2019 Nikolai Pavlov. Contacts: <pawlow_nic@mail.ru>
 * All rights reserved.
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
#include "jbkernel/ZingerServer.hpp"
#include "jbutilities/md5.hpp"
#include "jbkernel/JbKernel.hpp"
#include "jbutilities/des.h"



namespace jblib::jbkernel
{

using namespace jbutilities;



ZingerServer::ZingerServer(void)
{

}



ZingerServer::~ZingerServer(void)
{
	this->disableCrypt();
}



ZingerServer::StartParameters_t* ZingerServer::getStartParameters(void)
{
	return &this->startParameters_;
}



void ZingerServer::start(void)
{
	if(!this->memory_)
		return;
	this->stop();
	if((!this->startParameters_.channel) ||
			(!this->startParameters_.waitingTimeoutMs) ||
					(this->startParameters_.memoryBlocks.empty())){
		return;
	}
	uint8_t* rxBuffer =
			(uint8_t*)malloc_s(ZINGER_SERVER_RX_BUFFER_SIZE);
	if(!rxBuffer)
		return;
	this->rxRingBuffer_ = new RingBuffer(rxBuffer, 1,
			ZINGER_SERVER_RX_BUFFER_SIZE);
	if(!this->rxRingBuffer_){
		free_s(rxBuffer);
		return;
	}
	MemoryBlock_t block = this->startParameters_.memoryBlocks[0];
	this->protoParameters_.isFwValid =
			(block.checkHeader ? this->checkImageHeader(block.beginAddress) : true) &&
			this->checkMd5Hash(&block);
	this->startParameters_.channel->initialize(malloc_s, TX_COMMAND_MAX_SIZE, this);
	JbKernel::addMainProcedure(this);
	this->isStarted = true;
}



void ZingerServer::stop(void)
{
	if(this->isStarted){
		JbKernel::deleteMainProcedure(this);
		this->isStarted = false;
		this->startParameters_.channel->deinitialize();
		this->startParameters_.channel = NULL;
		this->startParameters_.waitingTimeoutMs = 0;
		void* buffer = this->rxRingBuffer_->getBuffer();
		delete this->rxRingBuffer_;
		free_s(buffer);
		this->startParameters_.memoryBlocks.clear();
	}
	this->reset();
}



void ZingerServer::reset(void)
{
	this->timerCounter_ = 0;
	this->timeout_ = 0;
	this->startWaitingCounter_ = 0;
	this->protoParameters_.state = protoParameters_.PARSER_STATE_START_WAITING;
	this->protoParameters_.stringsForOneGet = 0;
	this->protoParameters_.blockNumber = 0;
	this->protoParameters_.fileSizeStrings = 0;
	this->protoParameters_.getStringNumber = 0;
	this->protoParameters_.addressOffset = 0;
	this->protoParameters_.eofFlag = false;
	this->protoParameters_.getStringNumberMax = 0;
	this->protoParameters_.writeRequests.clear();
	if(this->isStarted){
		MemoryBlock_t block = this->startParameters_.memoryBlocks[0];
		this->protoParameters_.isFwValid =
				(block.checkHeader ? this->checkImageHeader(block.beginAddress) : true) &&
				this->checkMd5Hash(&block);
	}
	else{
		this->protoParameters_.isFwValid = false;
	}
}



std::queue<ZingerServer::StatusMsg_t>* ZingerServer::getStatusQueue(void)
{
	return &this->statusQueue_;
}



__inline uint16_t ZingerServer::getAddressFromCommand(void){
	return (((uint16_t)this->protoParameters_.inputCommand.data[1]<<8) +
			this->protoParameters_.inputCommand.data[2]);
}



__inline uint8_t ZingerServer::getLengthFromCommand(void){
	return this->protoParameters_.inputCommand.data[0];
}



void ZingerServer::voidCallback(void* const source, void* parameter)
{
	if(source){
		this->timerCounter_++;
		return;
	}
	if(this->protoParameters_.state == this->protoParameters_.PARSER_STATE_START_WAITING) {
		if(this->checkTimeout()) {
			this->startTimeout(ZINGER_SERVER_TIMEOUT_INI_PACKET);
			uint8_t status =
					((this->protoParameters_.stringsForOneGet != 0) ? (1 << 1) : 0) |
					(this->protoParameters_.isFwValid);
			this->sendCommand(0xffff, status);
			this->startWaitingCounter_++;
		}
		if (this->parseInput()) {
			this->startWaitingCounter_ = 0;
			if(this->protoParameters_.inputCommand.type == this->protoParameters_.INPUT_COMMAND_TYPE_STRINGS_IN_FILE) {
				this->protoParameters_.fileSizeStrings =
						*((uint16_t*)this->protoParameters_.inputCommand.data);
			}
			if((this->protoParameters_.inputCommand.type == this->protoParameters_.INPUT_COMMAND_TYPE_EXIT) &&
					(this->protoParameters_.isFwValid)){
				if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
					StatusMsg_t msg = {
							.type = ZINGER_SERVER_STATUS_RECIEVE_EXIT,
							.data = 0
					};
					this->statusQueue_.push(msg);
				}
				this->reset();
			}
			if(this->protoParameters_.inputCommand.type ==
					this->protoParameters_.INPUT_COMMAND_TYPE_STRINGS_IN_ONE_GET){
				this->protoParameters_.stringsForOneGet =
						this->protoParameters_.inputCommand.data[0];
			}
			if(this->protoParameters_.inputCommand.type == this->protoParameters_.INPUT_COMMAND_TYPE_ERASE){
				if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
					StatusMsg_t msg = {
							.type = ZINGER_SERVER_STATUS_RECIEVE_ERASE,
							.data = 0
					};
					this->statusQueue_.push(msg);
				}
				this->reset();
			}
		}
		if ((this->protoParameters_.stringsForOneGet != 0) &&
				(this->protoParameters_.fileSizeStrings != 0)) {
			this->protoParameters_.state = this->protoParameters_.PARSER_STATE_WRITE_FLASH;
		}
		if((this->startWaitingCounter_ >=
				(this->startParameters_.waitingTimeoutMs /
						ZINGER_SERVER_TIMER_PERIOD_MS / ZINGER_SERVER_TIMEOUT_INI_PACKET))) {
			if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
				StatusMsg_t msg = {
						.type = ZINGER_SERVER_STATUS_WAITING_TIMEOUT,
						.data = 0
				};
				this->statusQueue_.push(msg);
			}
			this->reset();
		}
	}
	else if (this->protoParameters_.state == this->protoParameters_.PARSER_STATE_WRITE_FLASH) {
		if (this->parseInput()) {
			if (this->protoParameters_.inputCommand.type == this->protoParameters_.getStringNumber) {
				if(this->isCryptEnabled_){
					uint16_t strLen = getLengthFromCommand();
					if(strLen) {
						for(uint16_t i = 0; i < this->cryptParameters_.baseKeySize; i++) {
							this->cryptParameters_.lineKey[i] =
									(uint8_t)((this->protoParameters_.getStringNumber * 103) +
											(this->cryptParameters_.baseKey[i] * 37) + (i * 33) +
											(53 * (i + 7)) + ((191*(i + 1)) % 256));
						}
						memcpy(&this->cryptParameters_.lineGamma[0], &this->cryptParameters_.baseGamma[0],
								this->cryptParameters_.baseGammaSize);
						des_ctx dc;
						TripleDES_ENC(&dc, &this->cryptParameters_.lineGamma[0],
								this->cryptParameters_.baseGammaSize / 8,
								&this->cryptParameters_.lineKey[0], &this->cryptParameters_.lineKey[8],
								&this->cryptParameters_.lineKey[16]);
						for(uint16_t i = 0; i < strLen; i++) {
							this->protoParameters_.inputCommand.data[i+4] ^=
									this->cryptParameters_.lineGamma[i % this->cryptParameters_.baseGammaSize];
						}
					}
				}
				uint8_t summ = 0;
				for(uint8_t i = 0; i < this->protoParameters_.inputCommand.data[0] + 5; i++){
					summ += this->protoParameters_.inputCommand.data[i];
				}
				if(!summ){
					switch (this->protoParameters_.inputCommand.data[3])
					{
						case INTEL_HEX_TYPE_DATA:
						{
							uint32_t writeAddress = this->protoParameters_.addressOffset +
									this->getAddressFromCommand();
							uint8_t stringLength = this->getLengthFromCommand();
							int blockNumber = this->getBlockNumber(writeAddress, stringLength);
							if(blockNumber >= 0){
								MemoryBlock_t* block = &this->startParameters_.memoryBlocks[blockNumber];
								if(block->eraseBlock){
									WriteRequest_t request = {
											.address = block->beginAddress,
											.data = NULL,
											.dataSize = (block->endAddress - block->beginAddress)
									};
									this->protoParameters_.writeRequests.push_back(request);
									block->eraseBlock = false;
								}
								writeAddress = writeAddress + block->recievedAddressOffset;
								WriteRequest_t request = {
										.address = writeAddress,
										.data = (uint8_t*)malloc_s(stringLength),
										.dataSize = stringLength
								};
								if(request.data){
									memcpy(request.data, &this->protoParameters_.inputCommand.data[4], stringLength);
									this->protoParameters_.writeRequests.push_back(request);
									this->protoParameters_.getStringNumber++;
								}
								break;
							}
							else{
								if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
									StatusMsg_t msg = {
											.type = ZINGER_SERVER_STATUS_WRONG_ADDR_RECIEVED,
											.data = 0
									};
									this->statusQueue_.push(msg);
								}
								this->reset();
								return;
							}
							this->protoParameters_.getStringNumber++;
						}
						break;

						case INTEL_HEX_TYPE_LINE_ADR:
						{
							this->protoParameters_.addressOffset =
									((uint32_t)this->protoParameters_.inputCommand.data[4] << 24) +
									((uint32_t)this->protoParameters_.inputCommand.data[5] << 16);
							this->protoParameters_.getStringNumber++;
						}
						break;

						case INTEL_HEX_TYPE_SEGMENT_ADR:
						{
							this->protoParameters_.addressOffset =
									((((uint32_t)this->protoParameters_.inputCommand.data[4] << 8) +
											((uint32_t)this->protoParameters_.inputCommand.data[5])) << 4);
							this->protoParameters_.getStringNumber++;
						}
						break;

						case INTEL_HEX_TYPE_EOF:
						{
							this->protoParameters_.eofFlag = true;
							this->protoParameters_.getStringNumber =
									this->protoParameters_.fileSizeStrings;
						}
						break;

						case INTEL_HEX_START_LINEAR_ADDRESS:
						{
							this->protoParameters_.getStringNumber++;
						}
						break;
					}
				}
			}
			if(this->protoParameters_.inputCommand.type == this->protoParameters_.getStringNumberMax){
				this->startTimeout(0);
			}
			if(this->protoParameters_.inputCommand.type == this->protoParameters_.INPUT_COMMAND_TYPE_ERASE){
				if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
					StatusMsg_t msg = {
							.type = ZINGER_SERVER_STATUS_RECIEVE_ERASE,
							.data = 0
					};
					this->statusQueue_.push(msg);
				}
				this->reset();
			}
			if(this->protoParameters_.inputCommand.type == this->protoParameters_.INPUT_COMMAND_TYPE_EXIT){
				MemoryBlock_t block = this->startParameters_.memoryBlocks[0];
				this->protoParameters_.isFwValid =
						(block.checkHeader ? this->checkImageHeader(block.beginAddress) : true) &&
						this->checkMd5Hash(&block);
				if(this->protoParameters_.isFwValid){
					if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
						StatusMsg_t msg = {
								.type = ZINGER_SERVER_STATUS_RECIEVE_EXIT,
								.data = 0
						};
						this->statusQueue_.push(msg);
					}
				}
				this->reset();
			}
		}
		if(this->checkTimeout()) {
			handleWriteRequests();
			if(this->protoParameters_.getStringNumber < this->protoParameters_.fileSizeStrings) {
				this->sendGetString();
				this->startTimeout(ZINGER_SERVER_TIMEOUT_BASE +
						ZINGER_SERVER_TIMEOUT_FOR_1_STRING *
						this->protoParameters_.stringsForOneGet);
			}
			else{
				uint32_t count = this->startParameters_.memoryBlocks.size();
				for(uint32_t i = 0; i < count; i++){
					MemoryBlock_t block = this->startParameters_.memoryBlocks[i];
					if(!this->checkMd5Hash(&block)){
						this->writeMd5Hash(&block);
					}
				}
				this->reset();
			}
		}
	}
}



bool ZingerServer::parseInput(void)
{
	static uint16_t len = 0;
	static uint16_t recvCnt = 0;
	static uint8_t recieveStage = 0;

	uint8_t tmp;
	if(recieveStage == 0) {
		while(this->rxRingBuffer_->pop(&tmp)) {
			if(tmp == 0x55){
				recieveStage = 1;
				recvCnt = 0;
				break;
			}
		}
	}
	if (recieveStage == 1) {
		while(this->rxRingBuffer_->find(&tmp, recvCnt)) {
			if(recvCnt == 0)
				this->protoParameters_.inputCommand.type = tmp;
			if (recvCnt == 1)
				this->protoParameters_.inputCommand.type |= (uint16_t)(tmp)<<8;
			if(recvCnt < 1)
				recvCnt++;
			else {
				if (this->protoParameters_.inputCommand.type >= 0){
					len = 5;
				}
				else if(this->protoParameters_.inputCommand.type ==
						this->protoParameters_.INPUT_COMMAND_TYPE_STRINGS_IN_FILE){
					len = 2;
				}
				else if(protoParameters_.inputCommand.type ==
						this->protoParameters_.INPUT_COMMAND_TYPE_EXIT){
					len = 0;
				}
				else if(protoParameters_.inputCommand.type ==
						this->protoParameters_.INPUT_COMMAND_TYPE_STRINGS_IN_ONE_GET){
					len = 1;
				}
				else if(protoParameters_.inputCommand.type ==
						this->protoParameters_.INPUT_COMMAND_TYPE_ERASE){
					len = 0;
				}
				else {
					recvCnt = 0;
					recieveStage = 0;
					return false;
				}
				recvCnt = 0;
				recieveStage = 2;
				break;
			}
		}
	}
	if (recieveStage == 2) {
		while(this->rxRingBuffer_->find(&tmp, recvCnt + 2)) {
			this->protoParameters_.inputCommand.data[recvCnt] = tmp;
			recvCnt++;
			if ((recvCnt == 1) && (this->protoParameters_.inputCommand.type >= 0)) {
				len = (uint16_t)this->protoParameters_.inputCommand.data[0] + 5;
			}
			if (recvCnt > len) {
				recieveStage = 0;
				if(tmp == 0xAA) {
					this->rxRingBuffer_->delMult(recvCnt + 2);
					return true;
				}
				else
					return false;
			}
		}
	}
	return false;
}



int ZingerServer::getBlockNumber(uint32_t address, uint32_t size)
{
	uint32_t count = this->startParameters_.memoryBlocks.size();
	for(uint32_t i = 0; i < count; i++){
		MemoryBlock_t block = this->startParameters_.memoryBlocks[i];
		uint32_t realAddress = address + block.recievedAddressOffset;
		if( ((realAddress + size) <= block.endAddress) && realAddress >= block.beginAddress)
			return i;
	}
	return -1;
}



void ZingerServer::handleWriteRequests(void)
{
	uint32_t count = this->protoParameters_.writeRequests.size();
	for(uint32_t i = 0; i < count; i++){
		WriteRequest_t request =
				this->protoParameters_.writeRequests[i];
		if(request.data){
			this->memory_->write(request.address, request.data,
					request.dataSize);
			free_s(request.data);
		}
		else{
			this->memory_->erase(request.address, request.dataSize);
		}
	}
	this->protoParameters_.writeRequests.clear();
}



void ZingerServer::channelCallback(uint8_t* const buffer, const uint16_t size,
			void* const source, void* parameter)
{
	this->rxRingBuffer_->insertMult(buffer, size);
}



void ZingerServer::sendCommand(uint16_t stringNumber, uint8_t count)
{
	uint8_t command[5] = {0x55,0x00,0x00,0x00,0xAA};
	command[1] = stringNumber;
	command[2] = stringNumber>>8;
	command[3] = count;
	this->startParameters_.channel->tx(command, 5, NULL);
	#if ZINGER_SERVER_USE_TX_STATUS_MSG
	if(this->statusQueue_.size() <= ZINGER_SERVER_STATUS_QUEUE_MAX_SIZE){
		StatusMsg_t msg = {
				.type = ZINGER_SERVER_STATUS_TX,
				.data = 0
		};
		this->statusQueue_.push(msg);
	}
	#endif
}



void ZingerServer::sendGetString(void)
{
	uint8_t status = ((this->protoParameters_.stringsForOneGet != 0)? (1 << 1):0) |
			(this->protoParameters_.isFwValid);
	this->sendCommand(this->protoParameters_.getStringNumber, status);
	this->protoParameters_.getStringNumberMax = this->protoParameters_.getStringNumber +
			this->protoParameters_.stringsForOneGet - 1;
	if (this->protoParameters_.getStringNumberMax > this->protoParameters_.fileSizeStrings){
		this->protoParameters_.getStringNumberMax = this->protoParameters_.fileSizeStrings - 1;
	}
}



void ZingerServer::startTimeout(uint32_t timeout)
{
	this->timeout_ = this->timerCounter_ + timeout;
}



bool ZingerServer::checkTimeout(void)
{
	return (this->timerCounter_ >= this->timeout_);
}



void ZingerServer::setMemory(IVoidMemory* memory)
{
	this->memory_ = memory;
	if(this->memory_)
		this->memory_->initialize();
}



IVoidMemory* ZingerServer::getMemory(void) const
{
	return this->memory_;
}


#if JB_LIB_PLATFORM == 0
bool ZingerServer::checkImageHeader(uint32_t imageAddress)
{
	if(!this->memory_)
		return false;
	uint32_t word = 0;
	uint32_t validUserCode = 0;
	for(uint8_t i = 0; i < 8; i++){
		this->memory_->read(imageAddress,
				(uint8_t*)&word, sizeof(uint32_t));
		if((!i) && (!word))
			return false;
		validUserCode += word;
		imageAddress += sizeof(uint32_t);
	}
	return (validUserCode == 0) ? true : false;
}
#else
bool ZingerServer::isImageHeaderValid(uint32_t imageAddress)
{
	return true;
}
#endif



uint8_t* ZingerServer::calculateMd5Hash(MemoryBlock_t* block)
{
	static uint8_t calculatedHash[16];
	if(!this->memory_)
		return NULL;
	uint32_t size = block->endAddress - block->beginAddress;
	uint32_t cacheSize = 0;
	for(uint32_t i = 0; i < 8 * sizeof(uint32_t); i++){
		cacheSize = 1 << i;
		if(size & cacheSize)
			break;
	}
	uint32_t maxCacheSize = JbKernel::getHeapFree(16) >> 1;
	if(!maxCacheSize)
		return NULL;
	if(maxCacheSize < cacheSize)
		cacheSize = maxCacheSize;
	uint8_t* cache = (uint8_t*)malloc_s(cacheSize);
	if(!cache)
		return NULL;
	Md5* md5 = new Md5();
	md5->reset();
	for(uint32_t i = block->beginAddress; i < block->endAddress; i += cacheSize){
		uint32_t tail = block->endAddress - i;
		uint32_t readenLenth = (tail >= cacheSize) ? cacheSize : tail;
		this->memory_->read(i, cache, readenLenth);
		md5->update(cache, readenLenth);
	}
	md5->final(calculatedHash);
	free_s(cache);
	delete md5;
	return calculatedHash;
}



bool ZingerServer::checkMd5Hash(MemoryBlock_t* block)
{
	uint8_t* calculatedHash =
			this->calculateMd5Hash(block);
	if(!calculatedHash)
		return false;
	uint8_t writtenHash[16];
	this->memory_->read(block->hashAddress, writtenHash, 16);
	return !(memcmp(writtenHash, calculatedHash, 16));
}



bool ZingerServer::writeMd5Hash(MemoryBlock_t* block)
{
	uint8_t* calculatedHash =
			this->calculateMd5Hash(block);
	if(!calculatedHash)
		return false;
	if(this->memory_){
		this->memory_->write(block->hashAddress, calculatedHash, 16);
		return true;
	}
	else
		return false;
}



void ZingerServer::enableCrypt(uint8_t* baseKey, uint16_t baseKeySize,
		uint8_t* baseGamma, uint16_t baseGammaSize)
{
	if(this->isCryptEnabled_)
		this->disableCrypt();
	if((!baseKey) || (!baseKeySize) || (!baseGamma) || (!baseGammaSize))
		return;
	this->cryptParameters_.lineKey = (uint8_t*)malloc_s(baseKeySize);
	if(!this->cryptParameters_.lineKey)
		return;
	this->cryptParameters_.lineGamma = (uint8_t*)malloc_s(baseGammaSize);
	if(!this->cryptParameters_.lineGamma){
		free_s(this->cryptParameters_.lineKey);
		this->cryptParameters_.lineKey = NULL;
		return;
	}
	this->cryptParameters_.baseKey = baseKey;
	this->cryptParameters_.baseGamma = baseGamma;
	this->cryptParameters_.baseKeySize = baseKeySize;
	this->cryptParameters_.baseGammaSize = baseGammaSize;
	memset(this->cryptParameters_.lineKey, 0,
			this->cryptParameters_.baseKeySize);
	memset(this->cryptParameters_.lineGamma, 0,
			this->cryptParameters_.baseGammaSize);
	this->isCryptEnabled_ = true;
}



void ZingerServer::disableCrypt(void)
{
	if(this->isCryptEnabled_){
		this->isCryptEnabled_ = false;
		free_s(this->cryptParameters_.lineKey);
		this->cryptParameters_.lineKey = NULL;
		free_s(this->cryptParameters_.lineGamma);
		this->cryptParameters_.lineGamma = NULL;
		this->cryptParameters_.baseKey = NULL;
		this->cryptParameters_.baseGamma = NULL;
		this->cryptParameters_.baseKeySize = 0;
		this->cryptParameters_.baseGammaSize = 0;
	}
}

}
