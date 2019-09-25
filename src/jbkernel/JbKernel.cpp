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

#include "jbkernel/JbKernel.hpp"


namespace jblib
{
namespace jbkernel
{

std::forward_list<JbKernel::ProceduresListItem> JbKernel::mainProceduresList_;
std::forward_list<JbKernel::ProceduresListItem> JbKernel::mainProceduresDeleteList_;



void JbKernel::delayMs(uint32_t ms)  //For 204MHz Clock
{
	for(uint32_t i = 0; i < ms; i++)
		for(uint32_t j = 0; j < JBKERNEL_NUM_NOP_DELAY_MS; j++)
			asm volatile ("nop");
}



void JbKernel::delayUs(uint32_t us) //For 204MHz Clock
{
	for(uint32_t i = 0; i < us * JBKERNEL_NUM_NOP_DELAY_US; i++)
		asm volatile ("nop");
}



void JbKernel::doMain(void)
{
	for(std::forward_list<JbKernel::ProceduresListItem>::iterator
			it = mainProceduresList_.begin();
			it != mainProceduresList_.end(); ++it){
		it->procedure->voidCallback(NULL,
				it->parameter);
	}
	if(!mainProceduresDeleteList_.empty()){
		for(std::forward_list<JbKernel::ProceduresListItem>::iterator
				it = mainProceduresDeleteList_.begin();
				it != mainProceduresDeleteList_.end(); ++it){
			deleteMainProcedure(*it);
		}
		mainProceduresDeleteList_.clear();
	}
}



void JbKernel::addMainProcedure(IVoidCallback* callback, void* parameter)
{
	ProceduresListItem newItem;
	newItem.procedure = callback;
	newItem.parameter = parameter;
	mainProceduresList_.push_front(newItem);
}



void JbKernel::deleteMainProcedure(ProceduresListItem& procedureItem)
{
	mainProceduresList_.remove_if([procedureItem](ProceduresListItem item){
		if((item.procedure == procedureItem.procedure) &&
				item.parameter == procedureItem.parameter)
			return true;
		else
			return false;
	});
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
	addMainProcedure(callback, NULL);
}



uint32_t JbKernel::getHeapFree(uint32_t step)
{
    uint32_t ret = step;
    disableInterrupts();
    void* ptr = malloc(ret);
    while(ptr != NULL){
        free(ptr);
        ret += step;
        ptr = malloc(ret);
    }
    enableInterrupts();
    return ret;
}



uint32_t JbKernel::getHeapFree(void)
{
	return getHeapFree(10);
}



uint32_t JbKernel::getHeapFreeRecursiveAux(bool resetCounter, uint32_t step)
{
	static uint32_t heapRecursiveSize = 0;
	if(resetCounter) {
		heapRecursiveSize = 0;
		disableInterrupts();
	}
	void* ptr = malloc(step);
	if(ptr) {
		heapRecursiveSize += step;
		getHeapFreeRecursiveAux(false, step);
		free(ptr);
	}
	if(resetCounter) {
		enableInterrupts();
	}
	return heapRecursiveSize;
}



uint32_t JbKernel::getHeapFreeRecursive(void)
{
	return getHeapFreeRecursiveAux(true, 100);
}



uint32_t JbKernel::getHeapFreeRecursive(uint32_t step)
{
	return getHeapFreeRecursiveAux(true, step);
}

}

}


