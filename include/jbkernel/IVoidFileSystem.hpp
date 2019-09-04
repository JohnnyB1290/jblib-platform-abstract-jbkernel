/**
 * @file
 * @brief IVoidFileSystem Interface Description
 *
 * Event Timer for cycling/one time events.
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

#ifndef JBKERNEL_IVOIDFILESYSTEM_HPP_
#define JBKERNEL_IVOIDFILESYSTEM_HPP_

#include "jbkernel/jb_common.h"

#if !defined FA_READ
#define	FA_READ				0x01
#endif
#if !defined FA_WRITE
#define	FA_WRITE			0x02
#endif
#if !defined FA_OPEN_EXISTING
#define	FA_OPEN_EXISTING	0x00
#endif
#if !defined FA_CREATE_NEW
#define	FA_CREATE_NEW		0x04
#endif
#if !defined FA_CREATE_ALWAYS
#define	FA_CREATE_ALWAYS	0x08
#endif
#if !defined FA_OPEN_ALWAYS
#define	FA_OPEN_ALWAYS		0x10
#endif
#if !defined FA_OPEN_APPEND
#define	FA_OPEN_APPEND		0x30
#endif

namespace jblib
{
namespace jbkernel
{

class IVoidFileSystem
{
public:
	virtual void* openFile(const char* fileName, uint8_t mode) = 0;
	virtual void closeFile(void* file) = 0;
	virtual int readFile(void* file, void* data, uint32_t size) = 0;
	virtual int writeFile(void* file, void* data, uint32_t size) = 0;
};

}
}


#endif /*JBKERNEL_IVOIDFILESYSTEM_HPP_ */
