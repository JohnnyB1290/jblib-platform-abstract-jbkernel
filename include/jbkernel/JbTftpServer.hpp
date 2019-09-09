/**
 * @file
 * @brief JbTftp Server class Description
 *
 * @author   Evgeniy Ivanov <strelok1290@gmail.com>
 *			 Logan Gunthorpe <logang@deltatee.com>
 *           Dirk Ziegelmeier <dziegel@gmx.de>
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * Copyright © Deltatee Enterprises Ltd. 2013
 * All rights reserved.
 *
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

#ifndef JBKERNEL_JBTFTPSERVER_HPP_
#define JBKERNEL_JBTFTPSERVER_HPP_

#include "jbkernel/jb_common.h"
#include "jbkernel/IVoidChannel.hpp"
#include "jbkernel/IVoidFileSystem.hpp"
#include "jbkernel/VoidChannelMsgQueue.hpp"

namespace jblib
{
namespace jbkernel
{

class JbTftpServer : public IVoidCallback
{
public:
	JbTftpServer(IVoidFileSystem* fileSystem, IVoidChannel* channel, uint8_t nrtTimerNum);
	~JbTftpServer(void);
	void initialize(void);
	void deInitialize(void);
	bool isInitialized(void);

private:
	typedef enum
	{
		JBTFTP_ERROR_NO_CODE   		   = 0,
		JBTFTP_ERROR_FILE_NOT_FOUND    = 1,
		JBTFTP_ERROR_ACCESS_VIOLATION  = 2,
		JBTFTP_ERROR_DISK_FULL         = 3,
		JBTFTP_ERROR_ILLEGAL_OPERATION = 4,
		JBTFTP_ERROR_UNKNOWN_TRFR_ID   = 5,
		JBTFTP_ERROR_FILE_EXISTS       = 6,
		JBTFTP_ERROR_NO_SUCH_USER      = 7,
		JBTFTP_ERROR_WRONG_OPTION      = 8,
	}JbTftpErrorCode_t;

	virtual void voidCallback(void* const source, void* parameter);
	void close(void);
	void resendData(void);
	void sendAck(uint16_t blockNumber);
	void sendData(void);
	void sendError(void* channelParameter, JbTftpErrorCode_t code,
			const char* description);
	void sendRefresh(void* channelParams);

	bool isInitialized_ = false;
	uint8_t nrtTimerNum_ = 0;
	IVoidFileSystem* fileSystem_ = NULL;
	IVoidChannel* channel_ = NULL;
	VoidChannelMsgQueue* msgQueue_ = NULL;

	void* file_ = NULL;
	uint32_t timerCounter_ = 0;
	uint32_t lastPacketTime_ = 0;
	uint8_t* lastData_ = NULL;
	uint32_t lastDataSize_ = 0;
	uint8_t retries_ = 0;
	void* channelParameter_ = NULL;
	uint16_t blockNumber_ = 0;
	bool writeMode_ = false;

	bool isTimerEnabled_ = false;
};

}
}

#endif /* JBKERNEL_JBTFTPSERVER_HPP_ */
