/**
 * @file
 * @brief Real Time Timer Interface
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

#ifndef IRTTIMER_HPP_
#define  IRTTIMER_HPP_

#include "jbkernel/callback_interfaces.hpp"

namespace jblib
{
namespace jbkernel
{


class IRtTimer
{
public:
	IRtTimer(void){}
	virtual ~IRtTimer(void){}
	virtual void initialize(void) = 0;
	virtual void start(void) = 0;
	virtual void stop(void) = 0;
	virtual void reset(void) = 0;
	virtual void addMatchUs(const uint8_t matchNumber, uint32_t us, bool isResetOnMatch) = 0;
	virtual void addMatchTicks(const uint8_t matchNumber, uint32_t ticks, bool isResetOnMatch) = 0;
	virtual void deleteMatch(const uint8_t matchNumber) = 0;
	virtual void deinitialize(void) = 0;
	virtual void setMatchCallback(const uint8_t matchNumber, IVoidCallback* const matchCallback) = 0;
	virtual void deleteMatchCallback(const uint8_t matchNumber) = 0;
	virtual uint32_t getCounter(void) = 0;
	virtual void setCounter(uint32_t count) = 0;
};

}
}

#endif /*  IRTTIMER_HPP_ */
