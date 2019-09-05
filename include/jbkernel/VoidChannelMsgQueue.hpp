/**
 * @file
 * @brief Universal Message Queue for Void Channel Description
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


#ifndef JBKERNEL_VOIDCHANNELMSGQUEUE_HPP_
#define JBKERNEL_VOIDCHANNELMSGQUEUE_HPP_

#include "jbkernel/jb_common.h"
#include "jbkernel/callback_interfaces.hpp"
#include "jbkernel/IVoidChannel.hpp"
#include <list>


namespace jblib
{
namespace jbkernel
{


class VoidChannelMsgQueue : public IVoidCallback, public IChannelCallback
{
public:
	typedef struct
	{
		IVoidChannel::ConnectionParameter_t* connectionParam = NULL;
		uint8_t* data = NULL;
		uint16_t dataSize = 0;
		void* source = NULL;
	}ChannelMessage_t;

	VoidChannelMsgQueue(IVoidCallback* callback);
	VoidChannelMsgQueue(IVoidCallback* callback, uint8_t nrtTimerNumber,
			uint32_t timerPeriodUs);
	~VoidChannelMsgQueue(void);

private:
	void initialize(void);
	virtual void voidCallback(void* const source, void* parameter);
	virtual void channelCallback(uint8_t* const buffer, const uint16_t size,
			void* const source, void* parameter);

	IVoidCallback* callback_ = NULL;
	uint8_t nrtTimerNumber_ = 0;
	bool processMsgInTimer_ = false;
	bool stopTimer_ = false;
	uint32_t timerPeriodUs_ = 0;
	std::list<ChannelMessage_t> channelMsgList_;
};


}
}

#endif /* JBKERNEL_VOIDCHANNELMSGQUEUE_HPP_ */
