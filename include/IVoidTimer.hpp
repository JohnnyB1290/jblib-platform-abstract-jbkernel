/**
 * @file
 * @brief Void Timer Interface
 *
 * Description of void timer interface
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

#ifndef IVOIDTIMER_HPP_
#define IVOIDTIMER_HPP_

#include <stdint.h>
#include "callback_interfaces.hpp"

namespace jblib
{
namespace jbkernel
{

class IVoidTimer
{
public:
	IVoidTimer(void){}
	virtual ~IVoidTimer(void){}
	virtual void initialize(uint32_t us) = 0;
	virtual void start(void) = 0;
	virtual void stop(void) = 0;
	virtual void reset(void) = 0;
	virtual uint32_t getCounter(void) = 0;
	virtual uint32_t getUsecCounter(void)
	{
		return 0;
	}
	virtual void setCounter(uint32_t count) = 0;
	virtual void addCallback(IVoidCallback* const callback) = 0;
	virtual void deleteCallback(void) = 0;
	virtual void deinitialize(void) = 0;
};

}
}

#endif /* IVOIDTIMER_HPP_ */
