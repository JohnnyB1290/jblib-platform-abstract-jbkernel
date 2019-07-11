/**
 * @file
 * @brief Options for i.MXRT JB Drivers
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

#ifndef LPC43XX_JBDRIVERS_OPTS_H_
#define LPC43XX_JBDRIVERS_OPTS_H_

typedef struct{
	unsigned int gpioBasePointer;
	unsigned char gpioPin;
}BoardGpio_t;

/*
   ------------------------------------
   ------------- JBCONTROLLER ---------
   ------------------------------------
*/

/**
 * JBCONTROLLER_BOARD_GPIOS
 */
#if !defined JBCONTROLLER_BOARD_GPIOS
#define JBCONTROLLER_BOARD_GPIOS				{{(unsigned int)GPIO1 , 9}}
#endif

/**
 * JBCONTROLLER_NUM_NOP_DELAY_US
 */
#if !defined JBCONTROLLER_NUM_NOP_DELAY_US
#define JBCONTROLLER_NUM_NOP_DELAY_US					300  //For 600 MHz clock  (for O3 optimization)
#endif

/**
 * JBCONTROLLER_NUM_NOP_DELAY_MS
 */
#if !defined JBCONTROLLER_NUM_NOP_DELAY_MS
#define JBCONTROLLER_NUM_NOP_DELAY_MS 					399000  //For 600 MHz clock  (for O3 optimization)
#endif

/*
   ------------------------------------
   ------------- Sys Tick -------------
   ------------------------------------
*/

/**
 * SYS_TICK_INTERRUPT_PRIORITY
 */
#if !defined SYS_TICK_INTERRUPT_PRIORITY
#define SYS_TICK_INTERRUPT_PRIORITY			15
#endif


#endif /* LPC43XX_JBDRIVERS_OPTS_H_ */
