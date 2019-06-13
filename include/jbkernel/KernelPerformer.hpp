/**
 * @file
 * @brief Kernel Performer Timer Description
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

#ifndef KERNELPERFORMER_HPP_
#define KERNELPERFORMER_HPP_

#include "jbkernel/EventTimer.hpp"

namespace jblib
{
namespace jbkernel
{


class KernelPerformer : public EventTimer
{
public:
	KernelPerformer(IVoidTimer* const voidTimer);
	virtual void addCyclicEvent(uint32_t periodUs, IVoidCallback* const callback, void* data);
	virtual void addOneTimeEvent(uint32_t delayUs, IVoidCallback* const callback, void* data);
	virtual void deleteEvent(IVoidCallback* const callback, void* const data);
	virtual void deleteEvent(IVoidCallback* const callback);
	virtual void voidCallback(void* const source, void* parameter);
	virtual uint16_t getEventsInQueue(void);
private:
	uint32_t eventBw_ = 0;
	uint32_t eventBr_ = 0;
	bool isEventsReady_[ EVENT_TIMER_EVENTS_SIZE ];
};

}
}

#endif /* KERNELPERFORMER_HPP_ */
