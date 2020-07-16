/**
 * @file
 * @brief JbKernel class realization
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

// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "jbkernel/jb_common.h"
#if JB_LIB_OS == 1

#include "jbkernel/JbKernel.hpp"

namespace jblib
{
namespace jbkernel
{

std::forward_list<JbKernel::ProceduresListItem> JbKernel::mainProceduresDeleteList_;
xSemaphoreHandle JbKernel::deleteListAccessMutex_ = xSemaphoreCreateMutex();

void JbKernel::delayMs(uint32_t ms)
{
	for(uint32_t i = 0; i < ms; i++) {
        for (uint32_t j = 0; j < JBKERNEL_NUM_NOP_DELAY_MS; j++) {
            asm volatile ("nop");
        }
    }
}



void JbKernel::delayUs(uint32_t us)
{
	for(uint32_t i = 0; i < us * JBKERNEL_NUM_NOP_DELAY_US; i++) {
        asm volatile ("nop");
    }
}



void JbKernel::mainTaskHandler(void* listItem)
{
    auto* procedureItem = (ProceduresListItem*)listItem;
    while(true){
        bool needToDelete = false;
        xSemaphoreTake(deleteListAccessMutex_, portMAX_DELAY);
        if(!mainProceduresDeleteList_.empty()){
            mainProceduresDeleteList_.remove_if([procedureItem, &needToDelete](ProceduresListItem item){
                if((item.procedure == procedureItem->procedure) &&
                   item.parameter == procedureItem->parameter) {
                    needToDelete = true;
                    return true;
                }
                else
                    return false;
            });
        }
        xSemaphoreGive(deleteListAccessMutex_);
        if(needToDelete){
            free_s(listItem);
            vTaskDelete(nullptr);
        }

        if(procedureItem->procedure){
            procedureItem->procedure->voidCallback(nullptr, procedureItem->parameter);
        }
    }
}



JbKernel::ProceduresListItem* JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter,
        uint32_t stackSize, uint32_t priority, const char* const threadName)
{
    auto* newItem = new ProceduresListItem;
    newItem->procedure = callback;
    newItem->parameter = parameter;
    newItem->name = threadName;
    xTaskCreate(&mainTaskHandler, threadName,
                stackSize, newItem,
                priority, &newItem->taskHandle);
    return newItem;
}



void JbKernel::deleteMainProcedure(IVoidCallback* callback, void* parameter)
{
	ProceduresListItem newItem;
	newItem.procedure = callback;
	newItem.parameter = parameter;
    xSemaphoreTake(deleteListAccessMutex_, portMAX_DELAY);
	mainProceduresDeleteList_.push_front(newItem);
    xSemaphoreGive(deleteListAccessMutex_);
}



void JbKernel::deleteMainProcedure(IVoidCallback* callback)
{
	deleteMainProcedure(callback, nullptr);
}



JbKernel::ProceduresListItem* JbKernel::addMainProcedure(IVoidCallback* callback)
{
	return addMainProcedure(callback, nullptr, JBKERNEL_MAIN_TASKS_STACK_SIZE);
}



JbKernel::ProceduresListItem* JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter)
{
    return addMainProcedure(callback, parameter, JBKERNEL_MAIN_TASKS_STACK_SIZE);
}



JbKernel::ProceduresListItem* JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter, uint32_t stackSize)
{
    return addMainProcedure(callback, parameter,
            stackSize, JBKERNEL_MAIN_TASKS_PRIORITY);
}



JbKernel::ProceduresListItem* JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter,
                                uint32_t stackSize, uint32_t priority)
{
    return addMainProcedure(callback, parameter,
            stackSize, priority, "Do Main Thread");
}



uint32_t JbKernel::getHeapFree()
{
    return xPortGetFreeHeapSize();
}



uint32_t JbKernel::getHeapFree(uint32_t step)
{
    return (xPortGetFreeHeapSize() & (~1));
}

}
}

#endif