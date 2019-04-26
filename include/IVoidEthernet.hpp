/**
 * @file
 * @brief Void Ethernet Interface
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

#ifndef IVOIDETHERNET_HPP_
#define IVOIDETHERNET_HPP_

#include "jb_common.h"
#if USE_LWIP
#include "lwip/pbuf.h"
#endif

namespace jblib::jbkernel
{

typedef enum
{
	PARAMETER_MAC = 0,
	PARAMETER_TX_UNLOCK,
	PARAMETER_LINK,
	PARAMETER_SPEED,
	PARAMETER_NAME,
} IVoidEthernetParameters_t;

typedef enum
{
	SPEED_10_M =    0,
	SPEED_100_M =   1,
	SPEED_AUTONEG = 2,
	SPEED_1000_M =  3,
}IVoidEthernetSpeed_t;

class IVoidEthernet
{
public:
	IVoidEthernet(void){}
	virtual ~IVoidEthernet(void){}
	virtual void initialize(void) = 0;
	virtual void start(void) = 0;
	virtual void resetDevice(void) = 0;
	virtual void getParameter(const uint8_t number, void* const value) = 0;
	virtual void setParameter(const uint8_t number, void* const value) = 0;
	virtual bool isTxQueueFull(void) = 0;
	virtual void addToTxQueue(EthernetFrame* const frame, uint16_t frameSize) = 0;
#if USE_LWIP
	virtual void addToTxQueue(struct pbuf* p) = 0;
#endif
	virtual uint16_t pullOutRxFrame(EthernetFrame* const frame) = 0;
	uint32_t getErrorsCounter() const { return errorsCounter_; }
	void setErrorsCounter(uint32_t errorsCounter = 0) { errorsCounter_ = errorsCounter; }
	uint32_t getRxBytesCounter() const { return rxBytesCounter_; }
	void setRxBytesCounter(uint32_t rxBytesCounter = 0) { rxBytesCounter_ = rxBytesCounter; }
	uint32_t getRxFramesCounter() const { return rxFramesCounter_; }
	void setRxFramesCounter(uint32_t rxFramesCounter = 0) { rxFramesCounter_ = rxFramesCounter; }
	uint32_t getTxBytesCounter() const { return txBytesCounter_; }
	void setTxBytesCounter(uint32_t txBytesCounter = 0) { txBytesCounter_ = txBytesCounter; }
	uint32_t getTxFramesCounter() const { return txFramesCounter_; }
	void setTxFramesCounter(uint32_t txFramesCounter = 0) { txFramesCounter_ = txFramesCounter; }
protected:
	uint32_t txFramesCounter_ = 0;
	uint32_t txBytesCounter_  = 0;
	uint32_t rxFramesCounter_ = 0;
	uint32_t rxBytesCounter_  = 0;
	uint32_t errorsCounter_   = 0;
};

class IEthernetListener
{
public:
	IEthernetListener(void){ }
	virtual ~IEthernetListener(void){ }
	virtual void parseFrame(EthernetFrame* const frame,
			uint16_t frameSize, IVoidEthernet* const source, void* parameter) = 0;
};

}

#endif /* IVOIDETHERNET_HPP_ */
