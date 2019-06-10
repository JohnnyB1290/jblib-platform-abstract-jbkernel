/**
 * @file
 * @brief Event Timer Realization
 *
 * Event Timer for cycling/one time events.
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

#include <string.h>
#include "EventTimer.hpp"

namespace jblib::jbkernel
{

EventTimer::EventTimer(IVoidTimer* const voidTimer) : IVoidCallback()
{
	this->voidTimer_ = voidTimer;
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
		this->callbacks_[i] = (IVoidCallback*)NULL;
		this->eventsPeriod_[i] = 0;
		this->eventsCounter_[i] = 0;
		this->eventsData_[i] = NULL;
		this->isOneTimeEvents_[i] = false;
	}
}



void EventTimer::voidCallback(void* const source, void* parameter)
{
	IVoidCallback* tempCallbacks[EVENT_TIMER_EVENTS_SIZE];
	void* tempEventsData[EVENT_TIMER_EVENTS_SIZE];

	__disable_irq();
	this->stop();
	this->isQueueProcessing_ = true;
	__enable_irq();
	memcpy(tempCallbacks, this->callbacks_,
			EVENT_TIMER_EVENTS_SIZE * sizeof( IVoidCallback* ));
	memcpy(tempEventsData, this->eventsData_,
			EVENT_TIMER_EVENTS_SIZE * sizeof( void* ));
	
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
		if(tempCallbacks[i]) {
			this->eventsCounter_[i]++;
			if(this->eventsCounter_[i] >= this->eventsPeriod_[i]) {
				if(this->isOneTimeEvents_[i]){
					this->eventsPeriod_[i] = 0;
					this->eventsData_[i] = NULL;
					this->isOneTimeEvents_[i] = false;
					this->callbacks_[i] = (IVoidCallback*)NULL;
				}
				this->eventsCounter_[i] = 0;
				tempCallbacks[i]->voidCallback((void*)this, tempEventsData[i]);
			}
		}
	}
	this->isQueueProcessing_ = false;
	__disable_irq();
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
		if(this->callbacks_[i]) {
			this->start();
			break;
		}
	}
	__enable_irq();
}



void EventTimer::initialize(uint32_t stepUs)
{
	if(this->voidTimer_ == (IVoidTimer*) NULL)
		return;
	this->stepUs_ = stepUs;
	this->voidTimer_->initialize(stepUs);
	this->voidTimer_->addCallback(this);
}



void EventTimer::deinitialize(void)
{
	if(this->voidTimer_ == (IVoidTimer*) NULL)
		return;
	this->voidTimer_->deinitialize();
}



void EventTimer::start(void)
{
	if(this->isQueueProcessing_)
		return;
	if(this->voidTimer_ == (IVoidTimer*) NULL)
		return;
	this->voidTimer_->start();
	this->isStopped_ = false;
}



void EventTimer::stop(void)
{
	if(this->voidTimer_ == (IVoidTimer*) NULL)
		return;
	this->voidTimer_->reset();
	this->voidTimer_->stop();
	this->isStopped_ = true;
}



void EventTimer::addCyclicEvent(uint32_t periodUs, IVoidCallback* const callback, void* data)
{
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++){
		__disable_irq();
		if(this->callbacks_[i] == (IVoidCallback*)NULL){
			this->eventsData_[i] = data;
			this->callbacks_[i] = callback;
			this->eventsCounter_[i] = 0;
			this->isOneTimeEvents_[i] = false;
			this->eventsPeriod_[i] = periodUs / this->stepUs_;
			if(this->eventsPeriod_[i] == 0)
				this->eventsPeriod_[i] = 1;
			if(this->isStopped_)
				this->start();
			__enable_irq();
			break;
		}
		__enable_irq();
	}
}



void EventTimer::addOneTimeEvent(uint32_t delayUs, IVoidCallback* const callback, void* data)
{
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++){
		__disable_irq();
		if(this->callbacks_[i] == (IVoidCallback*)NULL){
			this->eventsData_[i] = data;
			this->callbacks_[i] = callback;
			this->eventsCounter_[i] = 0;
			this->isOneTimeEvents_[i] = true;
			this->eventsPeriod_[i] = delayUs / this->stepUs_;
			if(this->eventsPeriod_[i] == 0)
				this->eventsPeriod_[i] = 1;
			if(this->isStopped_)
				this->start();
			__enable_irq();
			break;
		}
		__enable_irq();
	}
}



uint16_t EventTimer::getEventsInQueue(void)
{
	uint16_t retValue = 0;
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
		if(this->callbacks_[i])
			retValue++;
	}
	return retValue;
}



void EventTimer::deleteEvent(IVoidCallback* const callback)
{
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
		__disable_irq();
		if(this->callbacks_[i] == callback) {
			this->eventsPeriod_[i] = 0;
			this->callbacks_[i] = (IVoidCallback*)NULL;
			this->eventsCounter_[i] = 0;
			this->eventsData_[i] = NULL;
			this->isOneTimeEvents_[i] = false;
			__enable_irq();
			break;
		}
		__enable_irq();
	}
}



void EventTimer::deleteEvent(IVoidCallback* const callback, void* const data)
{
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
		__disable_irq();
		if((this->callbacks_[i] == callback) &&
				(this->eventsData_[i] == data)) {
			this->eventsPeriod_[i] = 0;
			this->callbacks_[i] = (IVoidCallback*)NULL;
			this->eventsCounter_[i] = 0;
			this->eventsData_[i] = NULL;
			this->isOneTimeEvents_[i] = false;
			__enable_irq();
			break;
		}
		__enable_irq();
	}
}

}
