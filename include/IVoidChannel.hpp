/**
 * @file
 * @brief Void Channel Interface
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

#ifndef IVOIDCHANNEL_HPP_
#define IVOIDCHANNEL_HPP_

#include "callback_interfaces.hpp"

namespace jblib::jbkernel
{

class IVoidChannel
{
public:
	IVoidChannel(void){}
	virtual ~IVoidChannel(void){}
	virtual void initialize(void* (* const mallocFunc)(size_t),
			const uint16_t txBufferSize, IChannelCallback* const callback) = 0;
	virtual void deinitialize(void) = 0;
	virtual void tx(uint8_t* const buffer, const uint16_t size, void* parameter) = 0;
	virtual void getParameter(const uint8_t number, void* const value) = 0;
	virtual void setParameter(const uint8_t number, void* const value) = 0;
};

}

#endif /* IVOIDCHANNEL_HPP_ */
