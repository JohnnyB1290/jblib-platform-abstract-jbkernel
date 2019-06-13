/**
 * @file
 * @brief Kernel Performer Timer Realization
 *
 *
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

#include "jbkernel/KernelPerformer.hpp"

namespace jblib::jbkernel
{

KernelPerformer::KernelPerformer(IVoidTimer* const voidTimer) : EventTimer(voidTimer)
{
	for(uint32_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++)
		this->isEventsReady_[i] = false;
}



void KernelPerformer::voidCallback(void* const source, void* parameter)
{
	uint32_t tempBw;
	uint32_t tempBr;

	__disable_irq();
	this->stop();
	tempBw = this->eventBw_;
	tempBr = this->eventBr_;
	__enable_irq();

	while(tempBw != tempBr) {
		if(!this->isEventsReady_[tempBr])
			break;
		if(this->callbacks_[tempBr]) {
			this->callbacks_[tempBr]->voidCallback((void*)this, this->eventsData_[tempBr]);
			this->callbacks_[tempBr] = (IVoidCallback*)NULL;
			this->eventsData_[tempBr] = NULL;
			this->isEventsReady_[tempBr] = false;
		}
		tempBr++;
		tempBr = ( tempBr == EVENT_TIMER_EVENTS_SIZE ) ? 0 : tempBr;
	}
	this->eventBr_ = tempBr;
}



void KernelPerformer::addOneTimeEvent(uint32_t delayUs, IVoidCallback* const callback, void* data)
{
	__disable_irq();
	uint32_t tempBw = this->eventBw_++;
	this->eventBw_ =
			( this->eventBw_ == EVENT_TIMER_EVENTS_SIZE ) ? 0 : this->eventBw_;
	this->eventsData_[tempBw] = data;
	this->callbacks_[tempBw] = callback;
	this->isEventsReady_[tempBw] = true;
	this->start();
	__enable_irq();
}



uint16_t KernelPerformer::getEventsInQueue(void)
{
	return D_A_MIN_B_MOD_C(this->eventBw_, this->eventBr_,
			EVENT_TIMER_EVENTS_SIZE);
}



void KernelPerformer::addCyclicEvent(uint32_t periodUs, IVoidCallback* const callback, void* data)
{

}



void KernelPerformer::deleteEvent(IVoidCallback* const callback, void* const data)
{

}



void KernelPerformer::deleteEvent(IVoidCallback* const callback)
{

}

}
