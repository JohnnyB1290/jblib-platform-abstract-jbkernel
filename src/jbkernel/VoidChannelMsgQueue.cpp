/**
 * @file
 * @brief Universal Message Queue for Void Channel realization
 *
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
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
#include "jbkernel/VoidChannelMsgQueue.hpp"
#include "jbkernel/TimeEngine.hpp"
#include "jbkernel/JbKernel.hpp"

namespace jblib::jbkernel
{

VoidChannelMsgQueue::VoidChannelMsgQueue(IVoidCallback* callback): IVoidCallback(), IChannelCallback()
{
	this->callback_ = callback;
	this->initialize();
}



VoidChannelMsgQueue::VoidChannelMsgQueue(IVoidCallback* callback, uint8_t nrtTimerNumber,
		uint32_t timerPeriodUs): IVoidCallback(), IChannelCallback()
{
	this->callback_ = callback;
	this->nrtTimerNumber_ = nrtTimerNumber;
	this->processMsgInTimer_ = true;
	this->timerPeriodUs_ = timerPeriodUs;
	this->initialize();
}



VoidChannelMsgQueue::~VoidChannelMsgQueue(void)
{
	this->stopTimer_ = true;
	while(this->stopTimer_);
}



void VoidChannelMsgQueue::initialize(void)
{
	if(this->processMsgInTimer_){
		TimeEngine::getTimeEngine()->setNrtEvent(this->nrtTimerNumber_,
				this->timerPeriodUs_, this, NULL);
	}
	else{
		JbKernel::addMainProcedure(this);
	}
}



void VoidChannelMsgQueue::voidCallback(void* const source, void* parameter)
{
	if(this->processMsgInTimer_){
		if(!this->stopTimer_){
			TimeEngine::getTimeEngine()->setNrtEvent(this->nrtTimerNumber_,
					this->timerPeriodUs_, this, NULL);
		}
		else {
			this->stopTimer_ = false;
		}
	}
	while(!this->channelMsgList_.empty()) {
		ChannelMessage_t msg = this->channelMsgList_.front();
		if(this->callback_){
			this->callback_->voidCallback(this, &msg);
		}
		if(msg.connectionParam){
			free_s(msg.connectionParam->parameters);
			free_s(msg.connectionParam);
		}
		free_s(msg.data);
		this->channelMsgList_.pop_front();
	}
}



void VoidChannelMsgQueue::channelCallback(uint8_t* const buffer, const uint16_t size,
		void* const source, void* parameter)
{
	uint8_t* data = (uint8_t*)malloc_s(size);
	if(!data)
		return;
	IVoidChannel::ConnectionParameter_t* connParam =
			(IVoidChannel::ConnectionParameter_t*)parameter;
	ChannelMessage_t newMsg;
	if(connParam){
		newMsg.connectionParam = (IVoidChannel::ConnectionParameter_t*)malloc_s(
						sizeof(IVoidChannel::ConnectionParameter_t));
		if(!newMsg.connectionParam){
			free_s(data);
			return;
		}
		newMsg.connectionParam->parameters =
				malloc_s(connParam->parametersSize);
		if(!newMsg.connectionParam->parameters){
			free_s(newMsg.connectionParam);
			free_s(data);
			return;
		}
		newMsg.connectionParam->parametersSize = connParam->parametersSize;
		memcpy(newMsg.connectionParam->parameters, connParam->parameters, connParam->parametersSize);
	}
	memcpy(data, buffer, size);
	newMsg.data = data;
	newMsg.dataSize = size;
	newMsg.source = source;
	this->channelMsgList_.push_back(newMsg);
}

}
