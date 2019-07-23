/**
 * @file
 * @brief JB_Lib Common defines
 *
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

#ifndef JB_COMMON_H_
#define  JB_COMMON_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "jbkernel/jbopt.h"

#if JB_LIB_PLATFORM == 0  //LPC43XX
#include "chip.h"
#elif JB_LIB_PLATFORM == 1  //ZYNQ
#include "xil_cache.h"
#include "xemacps.h"
#include "xil_exception.h"

// S=b1(Sharable) TEX=b001 AP=b11(Access permission Full Access),
// Domain=b1111, C=b0, B=b0
#define setNonCached1Mb(address) 				Xil_SetTlbAttributes((address), NORM_NONCACHE)

#define setNonCachedBlock(address, sizeInMb) 	{ for(uint32_t i = 0; i < (sizeInMb); i++) \
												Xil_SetTlbAttributes((address) + i * 0x00100000, NORM_NONCACHE); }

#define sev() 									__asm__("sev")

#define EMAC_ETH_MAX_FLEN 						XEMACPS_MAX_VLAN_FRAME_SIZE

typedef uint8_t EthernetFrame[XEMACPS_MAX_VLAN_FRAME_SIZE] __attribute__ ((aligned(64)));

#define __disable_irq() 	Xil_ExceptionDisable()
#define __enable_irq()		Xil_ExceptionEnable()

#elif JB_LIB_PLATFORM == 2  //i.MXRT
#include "fsl_device_registers.h"
#define EMAC_ETH_MAX_FLEN 		1536
typedef uint8_t EthernetFrame[EMAC_ETH_MAX_FLEN];
#endif

#if USE_NESTED_CRITICAL_SECTIONS == 1

#include "jbkernel/CriticalSections.h"

#define disableInterrupts()		 criticalSection(1)
#define enableInterrupts()  	 criticalSection(0)

#else
#define disableInterrupts()		 __disable_irq()
#define enableInterrupts()  	 __enable_irq()
#endif

#if USE_THREAD_SAFE_MALLOC == 1

__inline void* malloc_s(size_t size)
{
	void* ret_ptr = NULL;
	disableInterrupts();
	ret_ptr = malloc(size);
	enableInterrupts();
	return ret_ptr;
}

__inline void free_s(void * ptr)
{
	disableInterrupts();
	free(ptr);
	enableInterrupts();
}

#else
#define malloc_s malloc
#define free_s free
#endif

#define IS_POWER_OF_TWO(x) ((x) && !((x) & ((x)-1)))

#define CRITICAL_SECTION(code) { disableInterrupts(); \
								code \
								__enable_irq(); }

#define LONG_TO_BIN(n) ((((n) >> 21 ) & 0x80) | \
					 (((n) >> 18 ) & 0x40)  | \
					 (((n) >> 15 ) & 0x20)  | \
					 (((n) >> 12 ) & 0x10)  | \
					 (((n) >> 9 ) & 0x08)   | \
					 (((n) >> 6 ) & 0x04)   | \
					 (((n) >> 3 ) & 0x02)   | \
					 ((n) & 0x01))

#define BIN(n) LongToBin(0x##n##l)

#if !defined(MAX)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif
#if !defined(MIN)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define D_A_MIN_B_MOD_C(a,b,c) (((a) >= (b))? \
							   (((a) - (b))):(((a) + (c)) - (b)))


#endif /*  JB_COMMON_H_ */
