/**
 * @file
 * @brief Options for ESP32 JB Drivers
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

#ifndef ESP32_JBDRIVERS_OPTS_H_
#define ESP32_JBDRIVERS_OPTS_H_

/*
   ------------------------------------
   ------------- JBKERNEL -------------
   ------------------------------------
*/

/**
 * JBKERNEL_NUM_NOP_DELAY_US
 */
#if !defined JBKERNEL_NUM_NOP_DELAY_US
#define JBKERNEL_NUM_NOP_DELAY_US			29  //For 240 MHz clock  (for Os optimization)
#endif

/**
 * JBKERNEL_NUM_NOP_DELAY_MS
 */
#if !defined JBKERNEL_NUM_NOP_DELAY_MS
#define JBKERNEL_NUM_NOP_DELAY_MS 			40500  //For 240 MHz clock  (for Os optimization)
#endif

/*
   ------------------------------------
   ------------- JBCONTROLLER ---------
   ------------------------------------
*/

/**
 * JBCONTROLLER_BOARD_OUTPUT_GPIOS
 */
#if !defined JBCONTROLLER_BOARD_GPIOS
#define JBCONTROLLER_BOARD_GPIOS			{{0,0,0}}
#endif

#endif /* ESP32_JBDRIVERS_OPTS_H_ */
