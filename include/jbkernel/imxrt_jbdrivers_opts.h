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

#ifndef IMXRT_JBDRIVERS_OPTS_H_
#define IMXRT_JBDRIVERS_OPTS_H_

typedef struct{
	unsigned int gpioBasePointer;
	unsigned char gpioPin;
}BoardGpio_t;

/*
   ------------------------------------
   ------------- JBKERNEL -------------
   ------------------------------------
*/

/**
 * JBKERNEL_NUM_NOP_DELAY_US
 */
#if !defined JBKERNEL_NUM_NOP_DELAY_US
#define JBKERNEL_NUM_NOP_DELAY_US			300  //For 600 MHz clock  (for O3 optimization)
#endif

/**
 * JBKERNEL_NUM_NOP_DELAY_MS
 */
#if !defined JBKERNEL_NUM_NOP_DELAY_MS
#define JBKERNEL_NUM_NOP_DELAY_MS 			399000  //For 600 MHz clock  (for O3 optimization)
#endif

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

#if JBDRIVERS_USE_LPUART
/*
   ------------------------------------
   --------------- UART ---------------
   ------------------------------------
*/

/**
 * UART_1_INTERRUPT_PRIORITY
 */
#if !defined UART_1_INTERRUPT_PRIORITY
#define UART_1_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_2_INTERRUPT_PRIORITY
 */
#if !defined UART_2_INTERRUPT_PRIORITY
#define UART_2_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_3_INTERRUPT_PRIORITY
 */
#if !defined UART_3_INTERRUPT_PRIORITY
#define UART_3_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_4_INTERRUPT_PRIORITY
 */
#if !defined UART_4_INTERRUPT_PRIORITY
#define UART_4_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_5_INTERRUPT_PRIORITY
 */
#if !defined UART_5_INTERRUPT_PRIORITY
#define UART_5_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_6_INTERRUPT_PRIORITY
 */
#if !defined UART_6_INTERRUPT_PRIORITY
#define UART_6_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_7_INTERRUPT_PRIORITY
 */
#if !defined UART_7_INTERRUPT_PRIORITY
#define UART_7_INTERRUPT_PRIORITY			15
#endif

/**
 * UART_8_INTERRUPT_PRIORITY
 */
#if !defined UART_8_INTERRUPT_PRIORITY
#define UART_8_INTERRUPT_PRIORITY			15
#endif

#endif


#endif /* IMXRT_JBDRIVERS_OPTS_H_ */
