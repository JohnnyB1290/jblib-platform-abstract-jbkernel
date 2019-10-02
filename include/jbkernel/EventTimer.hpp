/**
 * @file
 * @brief Event Timer Description
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

#ifndef EVENTTIMER_HPP_
#define EVENTTIMER_HPP_

#include "jbkernel/jb_common.h"
#include "jbkernel/IVoidTimer.hpp"

namespace jblib
{
namespace jbkernel
{

class EventTimer : public IVoidCallback
{
public:
	EventTimer(IVoidTimer* const voidTimer);
	void initialize(uint32_t stepUs);
	void deinitialize(void);
	void start(void);
	void stop(void);
	void nativeRestart(void);
	virtual void addCyclicEvent(uint32_t periodUs, IVoidCallback* const callback, void* data);
	virtual void addOneTimeEvent(uint32_t delayUs, IVoidCallback* const callback, void* data);
	virtual void deleteEvent(IVoidCallback* const callback, void* const data);
	virtual void deleteEvent(IVoidCallback* const callback);
	virtual void voidCallback(void* const source, void* parameter);
	virtual uint16_t getEventsInQueue(void);

protected:
	IVoidTimer* voidTimer_ = NULL;
	uint32_t stepUs_ = 0;
	bool isStopped_ = true;
	bool isQueueProcessing_ = false;
	IVoidCallback* callbacks_[ EVENT_TIMER_EVENTS_SIZE ];
	void* eventsData_[ EVENT_TIMER_EVENTS_SIZE ];
	uint32_t eventsPeriod_[ EVENT_TIMER_EVENTS_SIZE ];
	uint32_t eventsCounter_[ EVENT_TIMER_EVENTS_SIZE ];
	bool isOneTimeEvents_[ EVENT_TIMER_EVENTS_SIZE ];
	#if !EVENT_TIMER_USE_CYCLIC_EVENTS
	uint16_t bw_ = 0;
	uint16_t br_ = 0;
	#endif
};

}
}

#endif /* EVENTTIMER_HPP_ */
