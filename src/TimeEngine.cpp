/**
 * @file
 * @brief Time Engine realization
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

#include <string.h>
#include "TimeEngine.hpp"

namespace jblib::jbkernel
{

TimeEngine* TimeEngine::timeEngine_ = (TimeEngine*)NULL;


TimeEngine* TimeEngine::getTimeEngine(void)
{
	if(TimeEngine::timeEngine_ == (TimeEngine*)NULL)
		TimeEngine::timeEngine_ = new TimeEngine();
	return TimeEngine::timeEngine_;
}



TimeEngine::TimeEngine(void) : IVoidCallback()
{
#if TIME_ENGINE_USE_RT
	for(uint8_t i = 0; i < TIME_ENGINE_NUM_MATCHES; i++){
		this->rtCallbacks_[i] = (IVoidCallback*)NULL;
		this->rtEventMatchesTicks_[i] = 0;
		this->rtCallbacksData_[i] = NULL;
	}
#endif
	memset(this->eventTimers_, 0, sizeof(EventTimer*) * TIME_ENGINE_NUM_NRT_TIMERS);
}



void TimeEngine::addNrtTimer(const uint8_t timerNumber, EventTimer* const eventTimer, uint32_t stepUs)
{
	this->eventTimers_[timerNumber] = eventTimer;
	if(this->eventTimers_[timerNumber] != (EventTimer*)NULL) {
		this->eventTimers_[timerNumber]->initialize(stepUs);
		this->eventTimers_[timerNumber]->start();
	}
}



#if TIME_ENGINE_USE_RT

void TimeEngine::addRtTimer(IRtTimer* const rtTimer)
{
	this->rtTimer_ = rtTimer;
	if(this->rtTimer_ != (IRtTimer*)NULL) {
		this->rtTimer_->initialize();
		this->rtTimer_->start();
	}
}



uint32_t TimeEngine::getRtCounter(void)
{
	if(this->rtTimer_ == (IRtTimer*)NULL)
		return 0;
	else
		return this->rtTimer_->getCounter();
}



void TimeEngine::setRtCounter(uint32_t ticks)
{
	if(this->rtTimer_)
		this->rtTimer_->setCounter(ticks);
}



void TimeEngine::setRtEvent(uint32_t matchTicks,  IVoidCallback* const callback, void* data)
{
	if(this->rtTimer_) {
		for(uint8_t i = 0; i < TIME_ENGINE_NUM_MATCHES; i++) {
			if(this->rtCallbacks_[i] == (IVoidCallback*)NULL) {
				this->rtCallbacksData_[i] = data;
				this->rtEventMatchesTicks_[i] = matchTicks;
				this->rtCallbacks_[i] = callback;
				this->rtTimer_->setMatchCallback(i, this);
				this->rtTimer_->addMatchTicks(i, matchTicks, false);
				break;
			}
		}
	}
}



void TimeEngine::changeRtEventMoment(uint32_t matchTicks, IVoidCallback* const callback, void* data)
{
	if(this->rtTimer_ && callback){
		for(uint8_t i = 0; i < TIME_ENGINE_NUM_MATCHES; i++) {
			if(this->rtCallbacks_[i] == callback
					&& this->rtCallbacksData_[i] == data) {
				this->rtEventMatchesTicks_[i] = matchTicks;
				this->rtTimer_->addMatchTicks(i, matchTicks, false);
				break;
			}
		}
	}
}



void TimeEngine::clearAllRtEvents(void) {
	for(uint8_t i = 0; i < TIME_ENGINE_NUM_MATCHES; i++) {
		this->rtTimer_->deleteMatch(i);
		this->rtTimer_->deleteMatchCallback(i);
		this->rtCallbacksData_[i] = NULL;
		this->rtCallbacks_[i] = NULL;
		this->rtEventMatchesTicks_[i] = 0;
	}
}
#endif



void TimeEngine::setNrtEvent(const uint8_t timerNumber, uint32_t us, IVoidCallback* const callback, void* data)
{
	EventTimerData_t* eventTimerDataPtr = (EventTimerData_t*)NULL;
	if(this->eventTimers_[timerNumber]) {
		for(uint8_t i = 0; i < EVENT_TIMER_EVENTS_SIZE; i++) {
			if(this->eventTimersData_[timerNumber][i].isDescriptorFree) {
				this->eventTimersData_[timerNumber][i].isDescriptorFree = false;
				eventTimerDataPtr = &this->eventTimersData_[timerNumber][i];
				break;
			}
		}
		if(eventTimerDataPtr) {
			eventTimerDataPtr->outCallback = callback;
			eventTimerDataPtr->outData = data;
			this->eventTimers_[timerNumber]->addOneTimeEvent(us, this, (void*)eventTimerDataPtr);
		}
	}
}



uint16_t TimeEngine::getEventsInNrtQueue(uint8_t timerNumber) {
	if(this->eventTimers_[timerNumber])
		return this->eventTimers_[timerNumber]->getEventsInQueue();
	else
		return 0;
}



void TimeEngine::voidCallback(void* const source, void* parameter)
{
#if TIME_ENGINE_USE_RT
	if(this->rtTimer_ && (source == (void*)this->rtTimer_)) {
		uint8_t matchNumber = *((uint8_t*)parameter);
		IVoidCallback* tempCallback = NULL;
		this->rtOutputParameters_.data = NULL;
		this->rtOutputParameters_.rtMoment = 0;
		this->rtOutputParameters_.rtMatchMoment = 0;
		this->rtTimer_->deleteMatch(matchNumber);
		this->rtTimer_->deleteMatchCallback(matchNumber);

		if(this->rtCallbacks_[matchNumber]) {
			tempCallback = this->rtCallbacks_[matchNumber];
			this->rtOutputParameters_.timerNumber = TIME_ENGINE_RT_TIMER_NUM;
			this->rtOutputParameters_.data = this->rtCallbacksData_[matchNumber];
			this->rtOutputParameters_.rtMoment = this->rtEventMatchesTicks_[matchNumber];
			this->rtOutputParameters_.rtMatchMoment = this->rtTimer_->getCounter();

			this->rtCallbacks_[matchNumber] = (IVoidCallback*)NULL;
			this->rtCallbacksData_[matchNumber] = NULL;
			this->rtEventMatchesTicks_[matchNumber] = 0;

			tempCallback->voidCallback(this,(void*)&this->rtOutputParameters_);
		}
		return;
	}
#endif
	for(uint8_t i = 0; i < TIME_ENGINE_NUM_NRT_TIMERS; i++) {
		if( source == (void*)this->eventTimers_[i] ) {

			EventTimerData_t* eventTimerDataPtr = (EventTimerData_t*)parameter;
			IVoidCallback* tempCallback = eventTimerDataPtr->outCallback;

			this->nrtOutputParameters_[i].timerNumber = i;
			this->nrtOutputParameters_[i].data = eventTimerDataPtr->outData;
#if TIME_ENGINE_USE_RT
			this->nrtOutputParameters_[i].rtMoment = this->rtTimer_->getCounter();
#else
			this->nrtOutputParameters_[i].rtMoment = 0;
#endif
			for(uint8_t j = 0; j < EVENT_TIMER_EVENTS_SIZE; j++) {
				if(eventTimerDataPtr == &this->eventTimersData_[i][j]){
					this->eventTimersData_[i][j].outData = NULL;
					this->eventTimersData_[i][j].outCallback = (IVoidCallback*)NULL;
					this->eventTimersData_[i][j].isDescriptorFree = true;
					break;
				}
			}
			if(tempCallback)
				tempCallback->voidCallback(this, (void*)&this->nrtOutputParameters_[i]);
			break;
		}
	}
}

}
