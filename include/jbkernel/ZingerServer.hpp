/**
 * @file
 * @brief Zinger server class description
 *
 *
 * @note
 * Copyright © 2019 Evgeniy Ivanov. Contacts: <strelok1290@gmail.com>
 * Copyright © 2019 Nikolai Pavlov. Contacts: <pawlow_nic@mail.ru>
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

#ifndef JBKERNEL_ZINGERSERVER_HPP_
#define JBKERNEL_ZINGERSERVER_HPP_

#include "jbkernel/jb_common.h"
#include "jbkernel/callback_interfaces.hpp"
#include "jbkernel/IVoidMemory.hpp"
#include "jbkernel/IVoidChannel.hpp"
#include "jbutilities/RingBuffer.hpp"
#include <queue>
#include <vector>


namespace jblib
{
namespace jbkernel
{

using namespace jbutilities;

class ZingerServer : public IVoidCallback, IChannelCallback
{
public:
	typedef struct
	{
		uint32_t beginAddress = 0;
		uint32_t endAddress = 0;
		uint32_t hashAddress = 0;
		int32_t recievedAddressOffset = 0;
		bool eraseBlock = true;
		bool checkHeader = true;
	}MemoryBlock_t;

	typedef struct
	{
		IVoidChannel* channel = NULL;
		uint32_t waitingTimeoutMs = 0;
		std::vector<MemoryBlock_t> memoryBlocks;
	}StartParameters_t;

	typedef enum{
		ZINGER_SERVER_STATUS_RECIEVE_EXIT = 		0,
		ZINGER_SERVER_STATUS_RECIEVE_ERASE = 		1,
		ZINGER_SERVER_STATUS_WAITING_TIMEOUT = 		2,
		ZINGER_SERVER_STATUS_WRONG_ADDR_RECIEVED = 	3,
	}StatusMsgType_t;

	typedef struct
	{
		StatusMsgType_t type;
		uint32_t data;
	}StatusMsg_t;
	std::queue<StatusMsg_t>* getStatusQueue(void);

	ZingerServer(void);
	~ZingerServer(void);
	void setMemory(IVoidMemory* memory);
	IVoidMemory* getMemory(void) const;
	bool checkImageHeader(uint32_t imageAddress);
	bool checkMd5Hash(MemoryBlock_t* block);
	uint8_t* calculateMd5Hash(MemoryBlock_t* block);
	bool writeMd5Hash(MemoryBlock_t* block);
	void enableCrypt(uint8_t* baseKey, uint16_t baseKeySize,
			uint8_t* baseGamma, uint16_t baseGammaSize);
	void disableCrypt(void);
	StartParameters_t* getStartParameters(void);
	void start(void);
	void stop(void);
	void reset(void);

private:
	virtual void voidCallback(void* const source, void* parameter);
	virtual void channelCallback(uint8_t* const buffer, const uint16_t size,
				void* const source, void* parameter);
	void startTimeout(uint32_t timeout);
	bool checkTimeout(void);
	void sendCommand(uint16_t stringNumber, uint8_t count);
	bool parseInput(void);
	__inline uint16_t getAddressFromCommand(void);
	__inline uint8_t getLengthFromCommand(void);
	void sendGetString(void);
	int getBlockNumber(uint32_t address, uint32_t size);
	void handleWriteRequests(void);

	constexpr static uint32_t RX_COMMAND_MAX_SIZE = 256 + 10;
	constexpr static uint32_t TX_COMMAND_MAX_SIZE = 64;
	enum{
		INTEL_HEX_TYPE_DATA = 				0x00,
		INTEL_HEX_TYPE_EOF = 				0x01,
		INTEL_HEX_TYPE_SEGMENT_ADR = 		0x02,
		INTEL_HEX_TYPE_LINE_ADR = 			0x04,
		INTEL_HEX_START_LINEAR_ADDRESS = 	0x05,
	};

	IVoidMemory* memory_ = NULL;

	struct{
		uint8_t* baseKey = NULL;
		uint16_t baseKeySize = 0;
		uint8_t* baseGamma = NULL;
		uint16_t baseGammaSize = 0;
		uint8_t* lineKey = NULL;
		uint8_t* lineGamma = NULL;
	}cryptParameters_;
	bool isCryptEnabled_ = false;

	uint32_t timerCounter_ = 0;
	uint32_t timeout_ = 0;
	uint32_t startWaitingCounter_ = 0;
	bool isStarted = false;
	StartParameters_t startParameters_;
	RingBuffer* rxRingBuffer_ = NULL;
	std::queue<StatusMsg_t> statusQueue_;

	typedef struct
	{
		uint32_t address = 0;
		uint8_t* data = NULL;
		uint32_t dataSize = 0;
	}WriteRequest_t;

	struct
	{
		enum{
			PARSER_STATE_START_WAITING = 0xCC,
			PARSER_STATE_WRITE_FLASH = 0xCD
		};
		enum{
			INPUT_COMMAND_TYPE_STRINGS_IN_FILE = 		-1,
			INPUT_COMMAND_TYPE_EXIT = 					-2,
			INPUT_COMMAND_TYPE_STRINGS_IN_ONE_GET = 	-3,
			INPUT_COMMAND_TYPE_ERASE = 					-4,
		};
		struct
		{
			int16_t type = 0;
			uint8_t data[RX_COMMAND_MAX_SIZE];
		}inputCommand;
		uint8_t blockNumber = 0;
		bool isFwValid = false;
		uint8_t state = PARSER_STATE_START_WAITING;
		uint8_t stringsForOneGet = 0;
		uint16_t fileSizeStrings = 0;
		uint16_t getStringNumber = 0;
		uint32_t addressOffset = 0;
		bool eofFlag = false;
		uint16_t getStringNumberMax = 0;
		std::vector<WriteRequest_t> writeRequests;
	}protoParameters_;
};

}
}

#endif /* JBKERNEL_ZINGERSERVER_HPP_ */
