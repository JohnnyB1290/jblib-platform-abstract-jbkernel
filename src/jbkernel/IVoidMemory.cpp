/**
 * @file
 * @brief IVoidMemory Interface Realization
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

// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "jbkernel/IVoidMemory.hpp"
#include "string.h"
#if USE_CONSOLE
#include "stdio.h"
#endif

namespace jblib
{
namespace jbkernel
{

#if JB_LIB_PLATFORM == 3
static portMUX_TYPE criticalMux = portMUX_INITIALIZER_UNLOCKED;
#endif

#if USE_FAT_FS
using namespace jbfatfs;
#endif


#if USE_FAT_FS
IVoidMemory::IVoidMemory(void) : IStorageDevice()
#else
IVoidMemory::IVoidMemory(void)
#endif
{

}



IVoidMemory::~IVoidMemory(void)
{

}



uint32_t IVoidMemory::getBaseAddess(void)
{
	return this->baseAddress_;
}



bool IVoidMemory::isCacheEnabled(void)
{
	return this->isCacheEnabled_;
}



void IVoidMemory::enableCache(uint32_t cacheCellSize, uint8_t cacheSizeCells)
{
	if(!this->isCacheEnabled_){
		this->cacheCellSize_ = cacheCellSize;
		this->cacheSizeCells_ = cacheSizeCells;
		this->cache_ = (CacheCell_t*)malloc_s(sizeof(CacheCell_t) * this->cacheSizeCells_);
		if(!this->cache_){
			#if USE_CONSOLE
			printf("IVoid Memory Error: No heap for cache!\n");
			#endif
			return;
		}
		for(uint32_t i = 0; i < this->cacheSizeCells_; i++){
			this->cache_[i].address = 0;
			this->cache_[i].useCounter = 0;
			this->cache_[i].cache = (uint8_t*)malloc_s(cacheCellSize);
			this->cache_[i].isUsing = false;
			if(!this->cache_[i].cache){
				if(!i){
					#if USE_CONSOLE
					printf("IVoid Memory Error: No heap for cache!\n");
					#endif
					free_s(this->cache_);
					return;
				}
				else{
					#if USE_CONSOLE
					printf("IVoid Memory Error: No heap for cache! Trunc to %lu cells\n", i);
					#endif
					this->cacheSizeCells_ = i;
					break;
				}
			}
		}
		this->isCacheEnabled_ = true;
	}
}



void IVoidMemory::read(uint32_t address, uint8_t* data, uint32_t size)
{
	disableInterrupts();
	if(this->isCacheEnabled_){
		int cell = 0;
		if((cell = this->isRangeInCache(address, size)) >= 0){
			memcpy(data, &this->cache_[cell].cache[address - this->cache_[cell].address], size);
			this->cache_[cell].useCounter++;
			enableInterrupts();
			return;
		}
		else if((cell = this->isAddressInCache(address)) >= 0){
			uint32_t cachedSize =
					this->cache_[cell].address + this->cacheCellSize_ - address;
			memcpy(data,
					&this->cache_[cell].cache[address - this->cache_[cell].address], cachedSize);
			this->cache_[cell].useCounter++;
			address += cachedSize;
			data += cachedSize;
			size -= cachedSize;
		}
	}
	this->readMemory(address, data, size);
	enableInterrupts();
}



void IVoidMemory::write(uint32_t address, uint8_t* data, uint32_t size)
{
	disableInterrupts();
	if(this->isCacheEnabled_){
		int cell = 0;
		if((cell = this->isRangeInCache(address, size)) >= 0){
			memcpy(&this->cache_[cell].cache[address - this->cache_[cell].address],
					data, size);
			this->cache_[cell].useCounter++;
			enableInterrupts();
			return;
		}
		else if((cell = this->isAddressInCache(address)) >= 0){
			uint32_t cachedSize =
					this->cache_[cell].address + this->cacheCellSize_ - address;
			memcpy(&this->cache_[cell].cache[address - this->cache_[cell].address], data, cachedSize);
			this->cache_[cell].useCounter++;
			address += cachedSize;
			data += cachedSize;
			size -= cachedSize;
		}
		if(size <= this->cacheCellSize_){
			cell = findCacheCell();
			if(cell >= 0){
				this->flushCacheCell(cell);
				this->cache_[cell].address = address;
				this->readMemory(address + size,
						&this->cache_[cell].cache[size], this->cacheCellSize_ - size);
				memcpy(this->cache_[cell].cache, data, size);
				this->cache_[cell].useCounter++;
				this->cache_[cell].isUsing = true;
				enableInterrupts();
				return;
			}
		}
	}
	this->writeMemory(address, data, size);
	enableInterrupts();
}



void IVoidMemory::flushCacheCell(int cellNumber)
{
	if(this->isCacheEnabled_){
		disableInterrupts();
		this->writeMemory(this->cache_[cellNumber].address,
				this->cache_[cellNumber].cache, this->cacheCellSize_);
		this->cache_[cellNumber].useCounter = 0;
		enableInterrupts();
	}
}



void IVoidMemory::flushCache(void)
{
	if(this->isCacheEnabled_){
		for(uint32_t i = 0; i < this->cacheSizeCells_; i++){
			this->flushCacheCell(i);
		}
	}
}



int IVoidMemory::findCacheCell(void)
{
	int ret = -1;
	if(this->isCacheEnabled_){
		ret = 0;
		for(uint32_t i = 1; i < this->cacheSizeCells_; i++){
			if(this->cache_[ret].useCounter > this->cache_[i].useCounter){
				ret = i;
			}
		}
	}
	return ret;
}



void IVoidMemory::disableCache(void)
{
	if(this->isCacheEnabled_){
		this->flushCache();
		this->isCacheEnabled_ = false;
		for(uint32_t i = 0; i < this->cacheSizeCells_; i++){
			free_s(this->cache_[i].cache);
		}
		free_s(this->cache_);
	}
}



int IVoidMemory::isRangeInCache(uint32_t address, uint32_t size)
{
	int ret = -1;
	for(uint32_t i = 0; i < this->cacheSizeCells_; i++){
		if(this->cache_[i].isUsing && (address >= this->cache_[i].address) &&
				(address + size) <= (this->cache_[i].address + this->cacheCellSize_)){
			ret = i;
		}
	}
	return ret;
}



int IVoidMemory::isAddressInCache(uint32_t address)
{
	int ret = -1;
	for(uint32_t i = 0; i < this->cacheSizeCells_; i++){
		if(this->cache_[i].isUsing && (address >= this->cache_[i].address) &&
				address <= (this->cache_[i].address + this->cacheCellSize_)){
			ret = i;
		}
	}
	return ret;
}



void IVoidMemory::invalidateCacheCell(int cellNumber)
{
	if(this->isCacheEnabled_){
		disableInterrupts();
		this->readMemory(this->cache_[cellNumber].address,
				this->cache_[cellNumber].cache, this->cacheCellSize_);
		this->cache_[cellNumber].useCounter = 0;
		enableInterrupts();
	}
}



void IVoidMemory::invalidateCache(void)
{
	if(this->isCacheEnabled_){
		for(uint32_t i = 0; i < this->cacheSizeCells_; i++){
			if(this->cache_[i].isUsing) {
				this->invalidateCacheCell(i);
			}
		}
	}
}



void IVoidMemory::erase(uint32_t address, uint32_t size)
{
	disableInterrupts();
	this->eraseMemory(address, size);
	this->invalidateCache();
	enableInterrupts();
}



#if USE_FAT_FS

uint32_t IVoidMemory::getDiskBaseAddress(void) const
{
	return this->diskBaseAddress_;
}



uint32_t IVoidMemory::getDiskSize(void) const
{
	return this->diskSize_;
}



void IVoidMemory::setDiskBaseAddress(uint32_t diskBaseAddress)
{
	this->diskBaseAddress_ = diskBaseAddress;
}



void IVoidMemory::setDiskSize(uint32_t diskSize)
{
	this->diskSize_ = diskSize;
}



DSTATUS IVoidMemory::diskStatus(void)
{
	return this->diskStatus_;
}



DSTATUS IVoidMemory::diskInitialize(void)
{
	if(!this->isInitialized_)
		this->initialize();
	return this->diskStatus_;
}



DRESULT IVoidMemory::diskRead(BYTE* buff, DWORD sector, UINT count)
{
	if (this->diskStatus_ & STA_NOINIT)
		return RES_NOTRDY;
	uint32_t startAddr = this->diskBaseAddress_ + sector * FF_MAX_SS;
	uint32_t size = count * FF_MAX_SS;
	this->read(startAddr, buff, size);
	return RES_OK;
}



DRESULT IVoidMemory::diskWrite(const BYTE* buff, DWORD sector, UINT count)
{
	if (this->diskStatus_ & STA_NOINIT)
		return RES_NOTRDY;
	uint32_t startAddr = this->diskBaseAddress_ + sector * FF_MAX_SS;
	uint32_t size = count * FF_MAX_SS;
	this->write(startAddr, (uint8_t*)buff, size);
	return RES_OK;
}



DRESULT IVoidMemory::diskIoctl(BYTE cmd, void* buff)
{
	if (this->diskStatus_ & STA_NOINIT)
		return RES_NOTRDY;
	DRESULT res = RES_ERROR;
	switch (cmd)
	{
		case CTRL_SYNC:	/* Make sure that no pending write process */
			res = RES_OK;
			break;

		case GET_SECTOR_COUNT:	/* Get number of sectors on the disk (DWORD) */
			*(DWORD *) buff = this->diskSize_ / FF_MAX_SS;
			res = RES_OK;
			break;

		case GET_SECTOR_SIZE:	/* Get R/W sector size (WORD) */
			*(WORD *) buff = FF_MAX_SS;
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE:/* Get erase block size in unit of sector (DWORD) */
			*(DWORD *) buff = this->diskBlockSize_;
			res = RES_OK;
			break;

		default:
			res = RES_PARERR;
			break;
	}

	return res;
}

#endif

}
}