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
 * JB_LIB_PLATFORM == 2 i.MXRT
 */
#if !defined JB_LIB_PLATFORM
#error "JB_Lib: Please define platform!"
#endif

#if JB_LIB_PLATFORM == 0
#include "jbkernel/lpc43xx_jbdrivers_opts.h"
#elif JB_LIB_PLATFORM == 1
#include "jbkernel/zynq_jbdrivers_opts.h"
#elif JB_LIB_PLATFORM == 2
#include "jbkernel/imxrt_jbdrivers_opt.h"
#endif

/**
 * USE_THREAD_SAFE_MALLOC
 * USE_THREAD_SAFE_MALLOC == 0 use standart malloc
 * USE_THREAD_SAFE_MALLOC == 1 use disable/enable irq if malloc used
 */
#if !defined USE_THREAD_SAFE_MALLOC
#define USE_THREAD_SAFE_MALLOC			0
#endif

/**
 * USE_LWIP
 */
#if !defined USE_LWIP
#define USE_LWIP		0
#endif

/*
   ------------------------------------
   ------------- Console --------------
   ------------------------------------
*/

/**
 * USE_CONSOLE
 */
#if !defined USE_CONSOLE
#define USE_CONSOLE							0
#endif

/**
 * CONSOLE_TX_BUF_SIZE
 */
#if !defined CONSOLE_TX_BUF_SIZE
#define CONSOLE_TX_BUF_SIZE					128
#endif

/**
 * CONSOLE_TX_MES_MAX_SIZE
 */
#if !defined CONSOLE_TX_MESSAGE_MAX_SIZE
#define CONSOLE_TX_MESSAGE_MAX_SIZE			64
#endif

/**
 * CONSOLE_RX_BUF_SIZE >= CONSOLE_COMMAND_BUF_SIZE
 */
#if !defined CONSOLE_RX_BUF_SIZE
#define CONSOLE_RX_BUF_SIZE					64
#endif

/**
 * CONSOLE_COMMAND_BUF_SIZE
 */
#if !defined CONSOLE_COMMAND_BUF_SIZE
#define CONSOLE_COMMAND_BUF_SIZE			64
#endif

/**
 * CONSOLE_NUM_LISTENERS
 */
#if !defined CONSOLE_NUM_LISTENERS
#define CONSOLE_NUM_LISTENERS				2
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
#define EVENT_TIMER_EVENTS_SIZE             	16
#endif

/**
 * EVENT_TIMER_USE_CYCLIC_EVENTS
 */
#if !defined EVENT_TIMER_LONG_DELAY_EVENTS_ENABLE
#define EVENT_TIMER_LONG_DELAY_EVENTS_ENABLE	1
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
#define TIME_ENGINE_USE_RT             	0
#endif

/**
 * TIME_ENGINE_NUM_MATCHES
 */
#if !defined TIME_ENGINE_NUM_MATCHES
#define TIME_ENGINE_NUM_MATCHES			4
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
#define INTERFACE_CHECKER_NUM_CHANNELS			3
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

/*
   ------------------------------------
   -------------- FAT FS --------------
   ------------------------------------
*/

/**
 *  STORAGE_CONTROLLER_NUM_DEVICES
 */
#if !defined STORAGE_CONTROLLER_NUM_DEVICES
#define STORAGE_CONTROLLER_NUM_DEVICES					1
#endif

/**
 * FAT_FS_USE_CONSOLE
 */
#if !defined FAT_FS_USE_CONSOLE
#define FAT_FS_USE_CONSOLE								0
#endif

/**
 * LOGGER_NUM_LOGGERS
 */
#if !defined LOGGER_NUM_LOGGERS
#define LOGGER_NUM_LOGGERS								1
#endif

/**
 * LOGGER_MAX_PATH_LENGTH
 */
#if !defined LOGGER_MAX_PATH_LENGTH
#define LOGGER_MAX_PATH_LENGTH							128
#endif

/**
 * LOGGER_DEFAULT_DIR_NAME
 */
#if !defined LOGGER_DEFAULT_DIR_NAME
#define LOGGER_DEFAULT_DIR_NAME							"log"
#endif

/*
   ------------------------------------
   ------ TCP Server Channel ----------
   ------------------------------------
*/

/**
 * TCP_SERVER_USE_CONSOLE
 */
#if !defined TCP_SERVER_USE_CONSOLE
#define TCP_SERVER_USE_CONSOLE								0
#endif

/**
 * TCP_SERVER_NUM_BROADCAST_CONNECTIONS
 */
#if !defined TCP_SERVER_NUM_BROADCAST_CONNECTIONS
#define TCP_SERVER_NUM_BROADCAST_CONNECTIONS				4
#endif

/*
   ------------------------------------
   --------- ARP Controller -----------
   ------------------------------------
*/

/**
 * ARP_CONTROLLER_USE_CONSOLE
 */
#if !defined ARP_CONTROLLER_USE_CONSOLE
#define ARP_CONTROLLER_USE_CONSOLE					0
#endif

/**
 * ARP_CONTROLLER_MAX_NUM_IP_FOR_REPLY
 */
#if !defined ARP_CONTROLLER_MAX_NUM_IP_FOR_REPLY
#define ARP_CONTROLLER_MAX_NUM_IP_FOR_REPLY			4
#endif

/**
 * ARP_CONTROLLER_ARP_TABLE_SIZE
 */
#if !defined ARP_CONTROLLER_ARP_TABLE_SIZE
#define ARP_CONTROLLER_ARP_TABLE_SIZE				32
#endif

/**
 * ARP_CONTROLLER_REFRESH_RECORD_TIME
 */
#if !defined ARP_CONTROLLER_REFRESH_RECORD_TIME
#define ARP_CONTROLLER_REFRESH_RECORD_TIME			120
#endif

/**
 * ARP_CONTROLLER_DELETE_RECORD_TIME
 */
#if !defined ARP_CONTROLLER_DELETE_RECORD_TIME
#define ARP_CONTROLLER_DELETE_RECORD_TIME			600
#endif

/*
   ------------------------------------
   --------- Ethernet Router ----------
   ------------------------------------
*/

/**
 * ETHERNET_ROUTER_USE_CONSOLE
 */
#if !defined ETHERNET_ROUTER_USE_CONSOLE
#define ETHERNET_ROUTER_USE_CONSOLE						0
#endif

/**
 * ETHERNET_ROUTER_MAX_NUM_LISTENERS
 */
#if !defined ETHERNET_ROUTER_MAX_NUM_LISTENERS
#define ETHERNET_ROUTER_MAX_NUM_LISTENERS				4
#endif

/**
 * ETHERNET_ROUTER_DEFAULT_PARSE_PERIOD_US
 */
#if !defined ETHERNET_ROUTER_DEFAULT_PARSE_PERIOD_US
#define ETHERNET_ROUTER_DEFAULT_PARSE_PERIOD_US			100
#endif

/*
   ------------------------------------
   ----------- DHCP Server ------------
   ------------------------------------
*/

/**
 * DHCP_SERVER_DOMAIN_NAME
 */
#if !defined DHCP_SERVER_DOMAIN_NAME
#define DHCP_SERVER_DOMAIN_NAME					((char*)"JBDHCP")
#endif

/*
   ------------------------------------
   ------------ DNS Server ------------
   ------------------------------------
*/

/**
 * DNS_SERVER_HOST_NAME_MAX_SIZE
 */
#if !defined DNS_SERVER_HOST_NAME_MAX_SIZE
#define DNS_SERVER_HOST_NAME_MAX_SIZE			128
#endif

/**
 * DNS_SERVER_HOST_NAME_0
 */
#if !defined DNS_SERVER_HOST_NAME_0
#define DNS_SERVER_HOST_NAME_0					((char*)"device.johnnyb")
#endif

/**
 * DNS_SERVER_HOST_NAME_1
 */
#if !defined DNS_SERVER_HOST_NAME_1
#define DNS_SERVER_HOST_NAME_1					((char*)"www.device.johnnyb")
#endif

/*
   ------------------------------------
   ------ Web Socket Channel ----------
   ------------------------------------
*/

/**
 * WS_CHANNEL_URI_MAX_SIZE
 */
#if !defined WS_CHANNEL_URI_MAX_SIZE
#define WS_CHANNEL_URI_MAX_SIZE					128
#endif

/**
 * WS_CHANNEL_MAX_NUM_CONNECTIONS
 */
#if !defined WS_CHANNEL_MAX_NUM_CONNECTIONS
#define WS_CHANNEL_MAX_NUM_CONNECTIONS			8
#endif


#endif /*  JBOPT_H_ */
