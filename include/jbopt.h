/**
 * @file
 * @brief JB_Lib Options
 *
 * Possible options description
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

#ifndef JBOPT_H_
#define  JBOPT_H_

#include "jblibopts.h"

/**
 * JB_LIB_PLATFORM
 * JB_LIB_PLATFORM == 0 LPC43XX
 * JB_LIB_PLATFORM == 1 ZYNQ
 */
#if !defined JB_LIB_PLATFORM
#define JB_LIB_PLATFORM			0
#endif

/**
 * USE_THREAD_SAFE_MALLOC
 * USE_THREAD_SAFE_MALLOC == 0 use standart malloc
 * USE_THREAD_SAFE_MALLOC == 1 use disable/enable irq if malloc used
 */
#if !defined USE_THREAD_SAFE_MALLOC
#define USE_THREAD_SAFE_MALLOC			1
#endif

/**
 * USE_LWIP
 */
#if !defined USE_LWIP
#define USE_LWIP		0
#endif

/*
   ------------------------------------
   ----------- JB Kernel --------------
   ------------------------------------
*/

/**
 * EVENT_TIMER_EVENTS_SIZE
 */
#if !defined EVENT_TIMER_EVENTS_SIZE
#define EVENT_TIMER_EVENTS_SIZE             16
#endif

/**
 * TIME_ENGINE_USE_RT
 */
#if !defined TIME_ENGINE_USE_RT
#define TIME_ENGINE_USE_RT             0
#endif

/**
 * TIME_ENGINE_NUM_MATCHES
 */
#if !defined TIME_ENGINE_NUM_MATCHES
#define TIME_ENGINE_NUM_MATCHES		4
#endif

/**
 * TIME_ENGINE_NUM_NRT_TIMERS
 */
#if !defined TIME_ENGINE_NUM_NRT_TIMERS
#define TIME_ENGINE_NUM_NRT_TIMERS		3
#endif

/**
 * TIME_ENGINE_RT_TIMER_NUM
 * This number will be return in timerNumber field
 * of Time Engine callback output struct, when event
 * was from Real Time Module
 */
#if !defined TIME_ENGINE_RT_TIMER_NUM
#define TIME_ENGINE_RT_TIMER_NUM		0xFF
#endif


#endif /*  JBOPT_H_ */
