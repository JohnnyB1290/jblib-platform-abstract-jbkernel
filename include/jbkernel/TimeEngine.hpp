/**
 * @file
 * @brief Time Engine Description
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

#ifndef TIMEENGINE_HPP_
#define TIMEENGINE_HPP_

#include <stdlib.h>
#include "jbkernel/EventTimer.hpp"
#include "jbkernel/KernelPerformer.hpp"

#if TIME_ENGINE_USE_RT
#include "jbkernel/IRtTimer.hpp"
#endif

namespace jblib
{
namespace jbkernel
{


typedef struct
{
	uint8_t timerNumber = 0;
	void* data = NULL;
	uint32_t rtMoment = 0;
	uint32_t rtMatchMoment = 0;
}TimeEngineCallbackParameters_t;

class TimeEngine : public IVoidCallback
{
public:
	static TimeEngine* getTimeEngine(void);
#if TIME_ENGINE_USE_RT
	uint32_t getRtCounter(void);
	void setRtCounter(uint32_t ticks);
	void setRtEvent(uint32_t matchTicks, IVoidCallback* const callback, void* data);
	void changeRtEventMoment(uint32_t matchTicks, IVoidCallback* const callback, void* data);
	void clearAllRtEvents(void);
	void addRtTimer(IRtTimer* const rtTimer);
#endif
	void addNrtTimer(const uint8_t timerNumber, EventTimer* const eventTimer, uint32_t stepUs);
	void setNrtEvent(const uint8_t timerNumber, uint32_t us, IVoidCallback* const callback, void* data);
	uint16_t getEventsInNrtQueue(uint8_t timerNumber);
	virtual void voidCallback(void* const source, void* parameter);

private:
	TimeEngine(void);

	static TimeEngine* timeEngine_;
#if TIME_ENGINE_USE_RT
	IRtTimer* rtTimer_ = NULL;
	IVoidCallback* rtCallbacks_[ TIME_ENGINE_NUM_MATCHES ];
	void* rtCallbacksData_[ TIME_ENGINE_NUM_MATCHES ];
	uint32_t rtEventMatchesTicks_[TIME_ENGINE_NUM_MATCHES];
	TimeEngineCallbackParameters_t rtOutputParameters_;
#endif
	typedef struct
	{
		IVoidCallback* outCallback = NULL;
		void* outData = NULL;
		bool isDescriptorFree = true;
	}EventTimerData_t;
	TimeEngineCallbackParameters_t nrtOutputParameters_[ TIME_ENGINE_NUM_NRT_TIMERS ];
	EventTimer* eventTimers_[TIME_ENGINE_NUM_NRT_TIMERS];
	EventTimerData_t eventTimersData_[TIME_ENGINE_NUM_NRT_TIMERS][ EVENT_TIMER_EVENTS_SIZE ];
};

}
}

#endif /* TIMEENGINE_HPP_ */
