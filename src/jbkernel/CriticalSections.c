/**
 * @file
 * @brief CriticalSections.c
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

#include "jbkernel/jb_common.h"

#if USE_NESTED_CRITICAL_SECTIONS == 1

#include "jbkernel/CriticalSections.h"

void criticalSection(int disableIrq)
{
	static int disableCounter = 0;
	if(disableIrq){
		__disable_irq();
		disableCounter++;
	}
	else{
		disableCounter--;
		if(disableCounter <= 0){
			disableCounter = 0;
			__enable_irq();
		}
	}
}

#endif



