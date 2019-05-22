/**
 * @file
 * @brief Non Volatile Memory Parameters Interface
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

#ifndef INVMPARAMETERS_HPP_
#define INVMPARAMETERS_HPP_

#include <stdint.h>
#include "jbopt.h"
#include "callback_interfaces.hpp"

#define NVM_PARAMETERS_CELL_TYPE_ARRAY_bm 			(1 << 7) //1 - data is array
#define NVM_PARAMETERS_CELL_TYPE_HEX_bm 			(1 << 6) //1 - show data as hex, 0 - show data in dec
#define NVM_PARAMETERS_CELL_TYPE_NOT_DISPLAY_bm 	(1 << 5) //0 - display in WebIface, 1 - not display

namespace jblib::jbkernel
{

#pragma pack(push, 1)

typedef struct
{
	uint16_t magic = NVM_PARAMETERS_MAGIC;
	uint16_t crc = 0;
	uint8_t size = 0;
	uint8_t reserved[3] = {0,0,0};
}NvmParametersHeader_t;



typedef struct
{
	uint8_t type = 0;
	uint8_t descriptionSize = 0;
	uint8_t dataSize = 0;
	uint8_t uid = 0;
	uint8_t groupId = 0;
	uint8_t reserved[3] = {0,0,0};
	char description[NVM_PARAMETERS_CELL_DESCRIPTION_SIZE];
	uint8_t data[NVM_PARAMETERS_CELL_DATA_SIZE];
}NvmParametersCell_t;

#pragma pack(pop)

typedef enum
{
	CELL_TYPE_U8 = 		0,
	CELL_TYPE_U16 = 	1,
	CELL_TYPE_U32 = 	2,
	CELL_TYPE_STRING = 	3,
	CELL_TYPE_DOUBLE = 	4,
	CELL_TYPE_I8 = 		5,
	CELL_TYPE_I16 = 	6,
	CELL_TYPE_I32 = 	7,
}NvmParametersCellType_t;



class INvmParameters
{
public:
	INvmParameters(void){}
	virtual ~INvmParameters(void){}
	virtual NvmParametersCell_t* getParameter(char* description,
			uint8_t* data, uint8_t dataSize) = 0;
	virtual NvmParametersCell_t* getParameter(char* description) = 0;
	virtual void setParameter(NvmParametersCell_t* cell) = 0;
	virtual void setParameter(uint8_t type, char* description,
			uint8_t* data, uint8_t dataSize) = 0;
	virtual void setParameter(uint8_t type, uint8_t uid,
			char* description, uint8_t* data, uint8_t dataSize) = 0;
	virtual void setParameter(uint8_t type, uint8_t uid,
			uint8_t groupId, char* description, uint8_t* data, uint8_t dataSize) = 0;
	virtual void deleteParameter(char* description) = 0;
	virtual void eraseAllParameters(void) = 0;
	virtual NvmParametersHeader_t* getHeader(void) = 0;
	virtual uint32_t getParametersSize(void) = 0;
	virtual void setAllParameters(void* ptr) = 0;
	virtual uint32_t getCompressedParametersSize(void) = 0;
	virtual uint32_t getCompressedParameters(uint8_t* data) = 0;
	virtual void setChangeCallback(IVoidCallback* callback) = 0;
	virtual NvmParametersCell_t* getLastSetCellPtr(void) = 0;
};

}

#endif /* INVMPARAMETERS_HPP_ */
