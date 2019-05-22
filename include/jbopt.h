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
#define JBOPT_H_

#include "jblibopts.h"

/**
 * JB_LIB_PLATFORM
 * JB_LIB_PLATFORM == 0 LPC43XX
 * JB_LIB_PLATFORM == 1 ZYNQ
 */
#if !defined JB_LIB_PLATFORM
#error "JB_Lib: Please define platform!"
#endif

#if JB_LIB_PLATFORM == 0
#include "lpc43xx_jbdrivers_opts.h"
#elif JB_LIB_PLATFORM == 1

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

/**
 * USE_CONSOLE
 */
#if !defined USE_CONSOLE
#define USE_CONSOLE			1
#endif



/*
   ------------------------------------
   ----------- Event Timer ------------
   ------------------------------------
*/

/**
 * EVENT_TIMER_EVENTS_SIZE
 */
#if !defined EVENT_TIMER_EVENTS_SIZE
#define EVENT_TIMER_EVENTS_SIZE             16
#endif

/*
   ------------------------------------
   ----------- Time Engine ------------
   ------------------------------------
*/
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

/*
   ------------------------------------
   -------------- IPC -----------------
   ------------------------------------
*/

/**
 * IPC_QUEUE_SIZE
 */
#if !defined IPC_QUEUE_SIZE
#define IPC_QUEUE_SIZE							16
#endif

/**
 * IPC_NUM_LISTENERS
 */
#if !defined IPC_NUM_LISTENERS
#define IPC_NUM_LISTENERS						16
#endif

/**
 * IPC_NUM_GLOBAL_VALUES
 */
#if !defined IPC_NUM_GLOBAL_VALUES
#define IPC_NUM_GLOBAL_VALUES					16
#endif

/**
 * IPC_MSG_ID_MAX
 */
#if !defined IPC_MSG_ID_MAX
#define IPC_MSG_ID_MAX							32
#endif

/**
 * IPC_MSG_ID_FREE_MEMORY
 */
#if !defined IPC_MSG_ID_FREE_MEMORY
#define IPC_MSG_ID_FREE_MEMORY					1
#endif

/**
 * IPC_MSG_ID_GLOBAL_VALUE_UPDATE
 */
#if !defined IPC_MSG_ID_GLOBAL_VALUE_UPDATE
#define IPC_MSG_ID_GLOBAL_VALUE_UPDATE			2
#endif


/*
   ------------------------------------
   ------ Interface Checker -----------
   ------------------------------------
*/

/**
 * INTERFACE_CHECKER_NUM_CHANNELS
 */
#if !defined INTERFACE_CHECKER_NUM_CHANNELS
#define INTERFACE_CHECKER_NUM_CHANNELS		3
#endif

/*
   ------------------------------------
   --------- NVM Parameters -----------
   ------------------------------------
*/

/**
 *  NVM_PARAMETERS_MAGIC
 */
#if !defined NVM_PARAMETERS_MAGIC
#define NVM_PARAMETERS_MAGIC							(0xAFDE)
#endif

/**
 *  NVM_PARAMETERS_CELL_DESCRIPTION_SIZE
 */
#if !defined NVM_PARAMETERS_CELL_DESCRIPTION_SIZE
#define NVM_PARAMETERS_CELL_DESCRIPTION_SIZE			32
#endif

/**
 *  NVM_PARAMETERS_CELL_DATA_SIZE
 */
#if !defined NVM_PARAMETERS_CELL_DATA_SIZE
#define NVM_PARAMETERS_CELL_DATA_SIZE					32
#endif


#endif /*  JBOPT_H_ */
