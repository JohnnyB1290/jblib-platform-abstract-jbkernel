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
    static xSemaphoreHandle deleteListAccessMutex = xSemaphoreCreateMutex();
    ProceduresListItem* procedureItem = (ProceduresListItem*)listItem;
    while(1){
        bool needToDelete = false;
        xSemaphoreTake(deleteListAccessMutex, portMAX_DELAY);
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
        xSemaphoreGive(deleteListAccessMutex);
        if(needToDelete){
            free_s(listItem);
            vTaskDelete(NULL);
        }

        if(procedureItem->procedure){
            procedureItem->procedure->voidCallback(NULL, procedureItem->parameter);
        }
    }
}



void JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter,
        uint32_t stackSize, uint32_t priority)
{
    ProceduresListItem* newItem = new ProceduresListItem;
    newItem->procedure = callback;
    newItem->parameter = parameter;
    xTaskCreate(&mainTaskHandler, "doMain_task",
                stackSize, newItem,
                priority,NULL);
}



void JbKernel::deleteMainProcedure(IVoidCallback* callback, void* parameter)
{
	ProceduresListItem newItem;
	newItem.procedure = callback;
	newItem.parameter = parameter;
	mainProceduresDeleteList_.push_front(newItem);
}



void JbKernel::deleteMainProcedure(IVoidCallback* callback)
{
	deleteMainProcedure(callback, NULL);
}



void JbKernel::addMainProcedure(IVoidCallback* callback)
{
	addMainProcedure(callback, NULL, JBKERNEL_MAIN_TASKS_STACK_SIZE);
}



void JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter)
{
    addMainProcedure(callback, parameter, JBKERNEL_MAIN_TASKS_STACK_SIZE);
}



void JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter, uint32_t stackSize)
{
    addMainProcedure(callback, parameter, stackSize, JBKERNEL_MAIN_TASKS_PRIORITY);
}



uint32_t JbKernel::getHeapFree(void)
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