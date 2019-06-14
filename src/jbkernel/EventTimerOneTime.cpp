/**
 * @file
 * @brief Event Timer Only One Time EventsRealization
 *
 * Event Timer for cycling/one time events.
 *
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * Copyright © 2019 Gleb Koba. Contacts: <koban4ik_11@mail.ru>
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

#include "jbkernel/jb_common.h"
#if !EVENT_TIMER_USE_CYCLIC_EVENTS
#include <string.h>
#include "jbkernel/EventTimer.hpp"


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
	__disable_irq();
	this->stop();
	this->isQueueProcessing_ = true;
	uint16_t tbw = this->bw_;
	uint16_t tbr = this->br_;
	__enable_irq();

	while(tbr != tbw) {
		if(this->callbacks_[tbr]) {
			this->eventsCounter_[tbr]++;
			if(this->eventsCounter_[tbr] >= this->eventsPeriod_[tbr]) {
				this->eventsCounter_[tbr] = 0;
				this->callbacks_[tbr]->voidCallback((void*)this,
						this->eventsData_[tbr]);
				this->eventsPeriod_[tbr] = 0;
				this->eventsData_[tbr] = NULL;
				this->isOneTimeEvents_[tbr] = false;
				this->callbacks_[tbr] = (IVoidCallback*)NULL;
				if(tbr == this->br_) {
					__disable_irq();
					this->br_++;
					this->br_ = this->br_ == EVENT_TIMER_EVENTS_SIZE ?
									0 : this->br_;
					__enable_irq();
				}
			}
		}
		else if(tbr == this->br_) {
			__disable_irq();
			this->br_++;
			this->br_ = this->br_ == EVENT_TIMER_EVENTS_SIZE ? 0 : this->br_;
			__enable_irq();
		}
		tbr++;
		tbr = tbr == EVENT_TIMER_EVENTS_SIZE ? 0 : tbr;
	}
	__disable_irq();
	this->isQueueProcessing_ = false;
	if(this->br_ != this->bw_ && this->isStopped_) {
		this->start();
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
	__disable_irq();
	this->voidTimer_->start();
	this->isStopped_ = false;
	__enable_irq();
}



void EventTimer::stop(void)
{
	if(this->voidTimer_ == (IVoidTimer*) NULL)
		return;
	__disable_irq();
	this->voidTimer_->reset();
	this->voidTimer_->stop();
	this->isStopped_ = true;
	__enable_irq();
}



void EventTimer::addCyclicEvent(uint32_t periodUs, IVoidCallback* const callback, void* data)
{

}



void EventTimer::addOneTimeEvent(uint32_t delayUs, IVoidCallback* const callback, void* data)
{
	__disable_irq();
	uint16_t tbw = this->bw_;
	this->eventsData_[tbw] = data;
	this->callbacks_[tbw] = callback;
	this->eventsCounter_[tbw] = 0;
	this->isOneTimeEvents_[tbw] = true;
	this->eventsPeriod_[tbw] = delayUs / this->stepUs_;
	if(this->eventsPeriod_[tbw] == 0) this->eventsPeriod_[tbw] = 1;
	tbw++;
	tbw = tbw == EVENT_TIMER_EVENTS_SIZE ? 0 : tbw;
	this->bw_ = tbw;
	if(this->isStopped_)
		this->start();
	__enable_irq();
}



uint16_t EventTimer::getEventsInQueue(void)
{
	uint16_t tbw = this->bw_;
	uint16_t tbr = this->br_;
	uint16_t retValue = tbw >= tbr ?
			(tbw - tbr) : (EVENT_TIMER_EVENTS_SIZE - tbw + tbr);
	return retValue;
}



void EventTimer::deleteEvent(IVoidCallback* const callback)
{
	uint16_t tbw = this->bw_;
	uint16_t tbr = this->br_;
	while(tbr != tbw) {
		__disable_irq();
		if(this->callbacks_[tbr] == callback) {
			this->eventsPeriod_[tbr] = 0;
			this->callbacks_[tbr] = (IVoidCallback*)NULL;
			this->eventsCounter_[tbr] = 0;
			this->eventsData_[tbr] = NULL;
			this->isOneTimeEvents_[tbr] = false;
			if(tbr == this->br_) {
				tbr++;
				tbr = tbr == EVENT_TIMER_EVENTS_SIZE ? 0 : tbr;
				this->br_ = tbr;
			}
			break;
		}
		__enable_irq();
		tbr++;
		tbr = tbr == EVENT_TIMER_EVENTS_SIZE ? 0 : tbr;
	}
}



void EventTimer::deleteEvent(IVoidCallback* const callback, void* const data)
{
	uint16_t tbw = this->bw_;
	uint16_t tbr = this->br_;
	while(tbr != tbw) {
		__disable_irq();
		if(this->callbacks_[tbr] == callback && this->eventsData_[tbr] == data) {
			this->eventsPeriod_[tbr] = 0;
			this->callbacks_[tbr] = (IVoidCallback*)NULL;
			this->eventsCounter_[tbr] = 0;
			this->eventsData_[tbr] = NULL;
			this->isOneTimeEvents_[tbr] = false;
			if(tbr == this->br_) {
				tbr++;
				tbr = tbr == EVENT_TIMER_EVENTS_SIZE ? 0 : tbr;
				this->br_ = tbr;
			}
			break;
		}
		__enable_irq();
		tbr++;
		tbr = tbr == EVENT_TIMER_EVENTS_SIZE ? 0 : tbr;
	}
}

}

#endif
