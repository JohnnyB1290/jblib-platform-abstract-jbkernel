/**
 * @file
 * @brief IVoidMemory Interface Description
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

#ifndef JBKERNEL_IVOIDMEMORY_HPP_
#define JBKERNEL_IVOIDMEMORY_HPP_

#include "jbkernel/jb_common.h"
#if USE_FAT_FS
#include "jbfatfs/IStorageDevice.hpp"
#endif

namespace jblib
{
namespace jbkernel
{

#if USE_FAT_FS
using namespace jbfatfs;
#endif



#if USE_FAT_FS
class IVoidMemory : public IStorageDevice
#else
class IVoidMemory
#endif
{
public:
	IVoidMemory(void);
	virtual ~IVoidMemory(void);
	void read(uint32_t address, uint8_t* data, uint32_t size);
	void write(uint32_t address, uint8_t* data, uint32_t size);
	void erase(uint32_t address, uint32_t size);
	void enableCache(uint32_t cacheCellSize, uint8_t cacheSizeCells);
	void disableCache(void);
	void flushCache(void);
	void invalidateCache(void);
	uint32_t getBaseAddess(void);
	bool isCacheEnabled(void);
	virtual void initialize(void) = 0;
	virtual bool isEmpty(uint32_t address, uint32_t size) = 0;

	#if USE_FAT_FS
	uint32_t getDiskBaseAddress(void) const;
	uint32_t getDiskSize(void) const;
	void setDiskBaseAddress(uint32_t diskBaseAddress);
	void setDiskSize(uint32_t diskSize);
	virtual DSTATUS diskInitialize(void);
	virtual DSTATUS diskStatus(void);
	virtual DRESULT diskRead(BYTE* buff, DWORD sector, UINT count);
	virtual DRESULT diskWrite(const BYTE* buff, DWORD sector, UINT count);
	virtual DRESULT diskIoctl(BYTE cmd, void* buff);
	#endif

protected:
	virtual void readMemory(uint32_t address, uint8_t* data, uint32_t size) = 0;
	virtual void writeMemory(uint32_t address, uint8_t* data, uint32_t size) = 0;
	virtual void eraseMemory(uint32_t address, uint32_t size) = 0;

	uint32_t baseAddress_ = 0;
	bool isInitialized_ = false;
	#if USE_FAT_FS
	DSTATUS diskStatus_ = STA_NOINIT;
	uint32_t diskBaseAddress_ = 0;
	uint32_t diskSize_ = 0;
	uint32_t diskBlockSize_ = 0;
	#endif

private:
	int isRangeInCache(uint32_t address, uint32_t size);
	int isAddressInCache(uint32_t address);
	int findCacheCell(void);
	void flushCacheCell(int cellNumber);
	void invalidateCacheCell(int cellNumber);

	typedef struct
	{
		uint32_t address = 0;
		uint8_t* cache = NULL;
		uint16_t useCounter = 0;
		bool isUsing = false;
	}CacheCell_t;
	uint32_t cacheCellSize_ = 0;
	uint8_t cacheSizeCells_ = 0;
	CacheCell_t* cache_ = NULL;
	bool isCacheEnabled_ = false;
};

}
}

#endif /* JBKERNEL_IVOIDMEMORY_HPP_ */
