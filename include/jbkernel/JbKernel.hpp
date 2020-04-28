/**
 * @file
 * @brief JbKernel class description
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


#ifndef JBKERNEL_JBKERNEL_HPP_
#define JBKERNEL_JBKERNEL_HPP_

#include <forward_list>
#include "jbkernel/jb_common.h"
#include "jbkernel/callback_interfaces.hpp"
#if USE_CONSOLE
#include <stdio.h>
#include "jbkernel/Console.hpp"
#endif


namespace jblib
{
namespace jbkernel
{

#if !JB_LIB_OS
class JbKernel
{
public:
	static void delayMs(uint32_t ms);
	static void delayUs(uint32_t us);
	static void doMain(void);
	static void addMainProcedure(IVoidCallback* callback);
	static void addMainProcedure(IVoidCallback* callback, void* parameter);
	static void deleteMainProcedure(IVoidCallback* callback);
	static void deleteMainProcedure(IVoidCallback* callback, void* parameter);
	static uint32_t getHeapFree(void);
	static uint32_t getHeapFree(uint32_t step);
	static uint32_t getHeapFreeRecursive(void);
	static uint32_t getHeapFreeRecursive(uint32_t step);
#if USE_CONSOLE
	static Console* getConsole(void)
	{
		return Console::getConsole();
	}
#endif

private:
	typedef struct
	{
		IVoidCallback* procedure = nullptr;
		void* parameter = NULL;
	}ProceduresListItem;
	static std::forward_list<ProceduresListItem> mainProceduresList_;
	static std::forward_list<ProceduresListItem> mainProceduresDeleteList_;

	static uint32_t getHeapFreeRecursiveAux(bool resetCounter, uint32_t step);
	static void deleteMainProcedure(ProceduresListItem& procedureItem);
};
#else
class JbKernel
{
public:
    typedef struct
    {
        IVoidCallback* procedure = nullptr;
        void* parameter = nullptr;
        TaskHandle_t taskHandle = nullptr;
        char* name = nullptr;
    }ProceduresListItem;

    static void delayMs(uint32_t ms);
    static void delayUs(uint32_t us);
    static ProceduresListItem* addMainProcedure(IVoidCallback* callback);
    static ProceduresListItem* addMainProcedure(IVoidCallback* callback, void* parameter);
    static ProceduresListItem* addMainProcedure(IVoidCallback* callback, void* parameter, uint32_t stackSize);
    static ProceduresListItem* addMainProcedure(IVoidCallback* callback, void* parameter,
            uint32_t stackSize, uint32_t priority);
    static ProceduresListItem* addMainProcedure(IVoidCallback* callback, void* parameter,
                                 uint32_t stackSize, uint32_t priority, char* threadName);
    static void deleteMainProcedure(IVoidCallback* callback);
    static void deleteMainProcedure(IVoidCallback* callback, void* parameter);
    static uint32_t getHeapFree(void);
    static uint32_t getHeapFree(uint32_t step);
#if USE_CONSOLE
    static Console* getConsole(void)
    {
        return Console::getConsole();
    }
#endif

private:
    static std::forward_list<ProceduresListItem> mainProceduresDeleteList_;
    static xSemaphoreHandle deleteListAccessMutex_;

    static void mainTaskHandler(void* listItem);
};
#endif
}
}

#endif /* JBKERNEL_JBKERNEL_HPP_ */
