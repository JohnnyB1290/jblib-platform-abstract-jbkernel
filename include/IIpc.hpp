/**
 * @file
 * @brief Inter-Processor Communication Interface Description
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

#ifndef IIPC_HPP_
#define IIPC_HPP_

#include <stdint.h>
#include "jbopt.h"

#if ((IPC_QUEUE_SIZE & (IPC_QUEUE_SIZE - 1))|| IPC_QUEUE_SIZE == 0)
#error "IPC Queue Size must always be power of 2"
#endif

#define IPC_QUEUE_INSERT     	(0)
#define IPC_QUEUE_FULL      	(-1)
#define IPC_QUEUE_ERROR     	(-2)
#define IPC_QUEUE_MAGIC_VALID   (0xCAB51053)

#define IPC_QUEUE_DATA_COUNT(q) ((uint32_t)((q)->head - (q)->tail))
#define IPC_QUEUE_IS_FULL(q)    (IPC_QUEUE_DATA_COUNT(q) >= (q)->size)
#define IPC_QUEUE_IS_EMPTY(q)   ((q)->head == (q)->tail)
#define IPC_QUEUE_IS_VALID(q)   ((q)->valid == IPC_QUEUE_MAGIC_VALID)

namespace jblib::jbkernel
{

typedef struct
{
	int32_t itemSize = 0;			/*!< Size of a single item in queue */
	uint32_t size = 0;				/*!< Toal number of elements that can be stored in the queue */
	volatile uint32_t head = 0;		/*!< Head index of the queue */
	volatile uint32_t tail = 0;		/*!< Tail index of the queue */
	uint8_t* data = NULL;			/*!< Pointer to the data */
	uint32_t valid = 0;             /*!< Queue is valid only if this is #QUEUE_MAGIC_VALID */
	uint32_t reserved[2] = {0,0};	/*!< Reserved entry to keep the structure aligned */
}IpcQueue_t;

#pragma pack(push, 1)

typedef struct
{
	uint8_t sender = 0;
	uint32_t id = 0;
	uint32_t data = 0;
}IpcMsg_t;

#pragma pack(pop)

class IIpcListener
{
public:
	IIpcListener(void) { }
    virtual ~IIpcListener(void) { }
    uint64_t getCode(void) const
    {
    	return this->code_;
    }
    void setCode(uint64_t code)
    {
    	this->code_ = code;
    }
    virtual void handleIpcMsg(IpcMsg_t* msg) = 0;

private:
    uint64_t code_ = 0;
};

class IIPC
{
public:
	IIPC(void) { }
	virtual ~IIPC(void) { }
	virtual void addIpcListener(IIpcListener* listener) = 0;
    virtual void deleteIpcListener(IIpcListener* listener) = 0;
    virtual int pushMsg(uint32_t id, uint32_t data) = 0;
    virtual int getWriteQueueMsgCount(void) = 0;
    virtual int setGlobalValue(uint32_t index, uint32_t value) = 0;
    virtual uint32_t getGlobalValue(uint32_t index) = 0;
};

}

#endif /* IIPC_HPP_ */
