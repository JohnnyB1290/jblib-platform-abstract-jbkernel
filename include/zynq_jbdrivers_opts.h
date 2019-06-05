/**
 * @file
 * @brief Options for Zynq JB Drivers
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

#ifndef ZYNQ_JBDRIVERS_OPTS_H_
#define ZYNQ_JBDRIVERS_OPTS_H_

#include "xparameters.h"

/**
 * JBDRIVERS_USE_PRIVATE_TIMER
 */
#if !defined JBDRIVERS_USE_PRIVATE_TIMER
#define JBDRIVERS_USE_PRIVATE_TIMER				1
#endif

/**
 * JBDRIVERS_USE_AXI_TIMER
 */
#if !defined JBDRIVERS_USE_AXI_TIMER
#define JBDRIVERS_USE_AXI_TIMER					0
#endif

/**
 * JBDRIVERS_USE_AXI_UART_16550
 */
#if !defined JBDRIVERS_USE_AXI_UART_16550
#define JBDRIVERS_USE_AXI_UART_16550			0
#endif

/**
 * JBDRIVERS_USE_WATCHDOG
 */
#if !defined JBDRIVERS_USE_WATCHDOG
#define JBDRIVERS_USE_WATCHDOG					0
#endif

/**
 * JBDRIVERS_USE_SD_CARD
 */
#if !defined JBDRIVERS_USE_SD_CARD
#define JBDRIVERS_USE_SD_CARD					0
#endif

/**
 * JBDRIVERS_USE_GPT
 */
#if !defined JBDRIVERS_USE_GPT
#define JBDRIVERS_USE_GPT						0
#endif

/**
 * JBDRIVERS_USE_IPC
 */
#if !defined JBDRIVERS_USE_IPC
#define JBDRIVERS_USE_IPC						0
#endif

/**
 * JBDRIVERS_USE_QSPI_FLASH
 */
#if !defined JBDRIVERS_USE_QSPI_FLASH
#define JBDRIVERS_USE_QSPI_FLASH				1
#endif

/**
 * JBDRIVERS_USE_CAN
 */
#if !defined JBDRIVERS_USE_CAN
#define JBDRIVERS_USE_CAN						0
#endif

/*
   ------------------------------------
   ----------- JB Controller ----------
   ------------------------------------
*/
/**
 * BRAM_DEVICE_ID
 */
#if !defined BRAM_DEVICE_ID
#if !defined XPAR_BRAM_0_DEVICE_ID
#define BRAM_DEVICE_ID					0
#else
#define BRAM_DEVICE_ID					XPAR_BRAM_0_DEVICE_ID
#endif
#endif

/**
 * GPIO_DEVICE_ID
 */
#if !defined GPIO_DEVICE_ID
#if !defined XPAR_XGPIOPS_0_DEVICE_ID
#define GPIO_DEVICE_ID					0
#else
#define GPIO_DEVICE_ID  				XPAR_XGPIOPS_0_DEVICE_ID
#endif
#endif

/**
 * JBCONTROLLER_NUM_MAIN_PROCEDURES
 */
#if !defined JBCONTROLLER_NUM_MAIN_PROCEDURES
#define JBCONTROLLER_NUM_MAIN_PROCEDURES				16
#endif

/**
 * JBCONTROLLER_BOARD_GPIOS
 */
#if !defined JBCONTROLLER_BOARD_GPIOS
#define JBCONTROLLER_BOARD_GPIOS				{59,60}
#endif

/**
 * JBCONTROLLER_NUM_NOP_DELAY_US
 */
#if !defined JBCONTROLLER_NUM_NOP_DELAY_US
#define JBCONTROLLER_NUM_NOP_DELAY_US			250  //For 667 MHz clock
#endif

/**
 * JBCONTROLLER_NUM_NOP_DELAY_MS
 */
#if !defined JBCONTROLLER_NUM_NOP_DELAY_MS
#define JBCONTROLLER_NUM_NOP_DELAY_MS 			250000  //For 667 MHz clock
#endif


/*
   ------------------------------------
   ----------- Ethernet Phy -----------
   ------------------------------------
*/

/**
 * ETHERNET_PHY_USE_CONSOLE
 */
#if !defined ETHERNET_PHY_USE_CONSOLE
#define ETHERNET_PHY_USE_CONSOLE			0
#endif

/**
 * EMACPS_0_DEVICE_ID
 */
#if !defined EMACPS_0_DEVICE_ID
#if !defined XPAR_XEMACPS_0_DEVICE_ID
#define EMACPS_0_DEVICE_ID					0
#else
#define EMACPS_0_DEVICE_ID					XPAR_XEMACPS_0_DEVICE_ID
#endif
#endif

/**
 * EMACPS_0_INTR_ID
 */
#if !defined EMACPS_0_INTR_ID
#if !defined XPS_GEM0_INT_ID
#define EMACPS_0_INTR_ID					54
#else
#define EMACPS_0_INTR_ID					XPS_GEM0_INT_ID
#endif
#endif

/**
 * EMACPS_1_DEVICE_ID
 */
#if !defined EMACPS_1_DEVICE_ID
#if !defined XPAR_XEMACPS_1_DEVICE_ID
#define EMACPS_1_DEVICE_ID					1
#else
#define EMACPS_1_DEVICE_ID					XPAR_XEMACPS_1_DEVICE_ID
#endif
#endif

/**
 * EMACPS_1_INTR_ID
 */
#if !defined EMACPS_1_INTR_ID
#if !defined XPS_GEM1_INT_ID
#define EMACPS_1_INTR_ID					77
#else
#define EMACPS_1_INTR_ID					XPS_GEM1_INT_ID
#endif
#endif

/**
 * GMII_RGMII_ADAPTER_CONTROL_REG_ADDR
 */
#if !defined GMII_RGMII_ADAPTER_CONTROL_REG_ADDR
#define GMII_RGMII_ADAPTER_CONTROL_REG_ADDR 	0x10
#endif

/**
 * GEM_ADAPTER_RX_QUEUE_SIZE //MUST BE GRATER RXBD_CNT!
 */
#if !defined GEM_ADAPTER_RX_QUEUE_SIZE
#define GEM_ADAPTER_RX_QUEUE_SIZE 				256
#endif

/**
 * GEM_ADAPTER_TX_QUEUE_SIZE
 */
#if !defined GEM_ADAPTER_TX_QUEUE_SIZE
#define GEM_ADAPTER_TX_QUEUE_SIZE 				256
#endif

/**
 * GEM_ADAPTER_0_NUM_RX_BD
 */
#if !defined GEM_ADAPTER_0_NUM_RX_BD
#define GEM_ADAPTER_0_NUM_RX_BD 				128
#endif

/**
 * GEM_ADAPTER_1_NUM_RX_BD
 */
#if !defined GEM_ADAPTER_1_NUM_RX_BD
#define GEM_ADAPTER_1_NUM_RX_BD 				128
#endif

/**
 * GEM_ADAPTER_NUM_TX_BD
 */
#if !defined GEM_ADAPTER_NUM_TX_BD
#define GEM_ADAPTER_NUM_TX_BD 					128
#endif

/**
 * GEM_ADAPTER_0_TX_BD_FREE_LINE
 */
#if !defined GEM_ADAPTER_0_TX_BD_FREE_LINE
#define GEM_ADAPTER_0_TX_BD_FREE_LINE			(GEM_ADAPTER_NUM_TX_BD - 5)
#endif

/**
 * GEM_ADAPTER_1_TX_BD_FREE_LINE
 */
#if !defined GEM_ADAPTER_1_TX_BD_FREE_LINE
#define GEM_ADAPTER_1_TX_BD_FREE_LINE			(GEM_ADAPTER_NUM_TX_BD - 5)
#endif

/**
 * GEM_ADAPTER_0_RX_BD_LIST_START_ADDRESS
 */
#if !defined GEM_ADAPTER_0_RX_BD_LIST_START_ADDRESS
#define GEM_ADAPTER_0_RX_BD_LIST_START_ADDRESS			0x1FC00000
#endif

/**
 * GEM_ADAPTER_0_TX_BD_LIST_START_ADDRESS
 */
#if !defined GEM_ADAPTER_0_TX_BD_LIST_START_ADDRESS
#define GEM_ADAPTER_0_TX_BD_LIST_START_ADDRESS			0x1FD00000
#endif

/**
 * GEM_ADAPTER_1_RX_BD_LIST_START_ADDRESS
 */
#if !defined GEM_ADAPTER_1_RX_BD_LIST_START_ADDRESS
#define GEM_ADAPTER_1_RX_BD_LIST_START_ADDRESS			0x1FE00000
#endif

/**
 * GEM_ADAPTER_1_TX_BD_LIST_START_ADDRESS
 */
#if !defined GEM_ADAPTER_1_TX_BD_LIST_START_ADDRESS
#define GEM_ADAPTER_1_TX_BD_LIST_START_ADDRESS			0x1FF00000
#endif

/**
 * GEM_ADAPTER_0_INTERRUPT_PRIORITY
 */
#if !defined GEM_ADAPTER_0_INTERRUPT_PRIORITY
#define GEM_ADAPTER_0_INTERRUPT_PRIORITY				80
#endif

/**
 * GEM_ADAPTER_1_INTERRUPT_PRIORITY
 */
#if !defined GEM_ADAPTER_1_INTERRUPT_PRIORITY
#define GEM_ADAPTER_1_INTERRUPT_PRIORITY				80
#endif

/*
   ------------------------------------
   ----------- IRQ Controller ---------
   ------------------------------------
*/

/**
 * IRQ_CONTROLLER_NUM_PERIPHERAL_LISTENERS
 */
#if !defined IRQ_CONTROLLER_NUM_PERIPHERAL_LISTENERS
#define IRQ_CONTROLLER_NUM_PERIPHERAL_LISTENERS			32
#endif

/**
 * IRQ_CONTROLLER_DEVICE_ID
 */
#if !defined IRQ_CONTROLLER_DEVICE_ID
#if !defined XPAR_SCUGIC_0_DEVICE_ID
#define IRQ_CONTROLLER_DEVICE_ID					0
#else
#define IRQ_CONTROLLER_DEVICE_ID					XPAR_SCUGIC_0_DEVICE_ID
#endif
#endif

#if JBDRIVERS_USE_AXI_TIMER
/*
   ------------------------------------
   ------------- AXI Timer ------------
   ------------------------------------
*/

/**
 * AXI_TIMER_NUM_TIMERS
 */
#if !defined AXI_TIMER_NUM_TIMERS
#define AXI_TIMER_NUM_TIMERS					XPAR_XTMRCTR_NUM_INSTANCES
#endif

/**
 * AXI_TIMER_DEVICE_IDS
 */
#if !defined AXI_TIMER_DEVICE_IDS
#define AXI_TIMER_DEVICE_IDS					{XPAR_AXI_TIMER_0_DEVICE_ID}
#endif

/**
 * AXI_TIMER_INTERRUPT_IDS
 */
#if !defined AXI_TIMER_INTERRUPT_IDS
#define AXI_TIMER_INTERRUPT_IDS					{XPS_FPGA0_INT_ID}
#endif

/**
 * AXI_TIMER_INTERRUPT_PRIORITIES
 */
#if !defined AXI_TIMER_INTERRUPT_PRIORITIES
#define AXI_TIMER_INTERRUPT_PRIORITIES			{80}
#endif

/**
 * AXI_TIMER_CLOCKS
 */
#if !defined AXI_TIMER_CLOCKS
#define AXI_TIMER_CLOCKS						{XPAR_AXI_TIMER_0_CLOCK_FREQ_HZ}
#endif

#endif

#if JBDRIVERS_USE_PRIVATE_TIMER
/*
   ------------------------------------
   ----------- Private Timer ----------
   ------------------------------------
*/

/**
 * PRIVATE_TIMER_DEVICE_ID
 */
#if !defined PRIVATE_TIMER_DEVICE_ID
#define PRIVATE_TIMER_DEVICE_ID						XPAR_XSCUTIMER_0_DEVICE_ID
#endif

/**
 * PRIVATE_TIMER_INTERRUPT_ID
 */
#if !defined PRIVATE_TIMER_INTERRUPT_ID
#define PRIVATE_TIMER_INTERRUPT_ID					XPAR_SCUTIMER_INTR
#endif

/**
 * PRIVATE_TIMER_INTERRUPT_PRIORITY
 */
#if !defined PRIVATE_TIMER_INTERRUPT_PRIORITY
#define PRIVATE_TIMER_INTERRUPT_PRIORITY			80
#endif

#endif

#if JBDRIVERS_USE_AXI_UART_16550
/*
   ------------------------------------
   ----------- AXI UART16550 ----------
   ------------------------------------
*/

/**
 * AXI_UART_16550_NUM_INSTANCES
 */
#if !defined AXI_UART_16550_NUM_INSTANCES
#define AXI_UART_16550_NUM_INSTANCES				XPAR_XUARTNS550_NUM_INSTANCES
#endif

/**
 * AXI_UART_16550_BASE_ADDRESSES
 */
#if !defined AXI_UART_16550_BASE_ADDRESSES
#define AXI_UART_16550_BASE_ADDRESSES				{XPAR_AXI_UART16550_0_BASEADDR}
#endif

/**
 * AXI_UART_16550_CLOCKS
 */
#if !defined AXI_UART_16550_CLOCKS
#define AXI_UART_16550_CLOCKS						{XPAR_XUARTNS550_CLOCK_HZ}
#endif

/**
 * AXI_UART_16550_INTERRUPT_IDS
 */
#if !defined AXI_UART_16550_INTERRUPT_IDS
#define AXI_UART_16550_INTERRUPT_IDS				{XPS_FPGA6_INT_ID}
#endif

/**
 * AXI_UART_16550_INTERRUPT_PRIORITIES
 */
#if !defined AXI_UART_16550_INTERRUPT_PRIORITIES
#define AXI_UART_16550_INTERRUPT_PRIORITIES			{80}
#endif

#endif

#if JBDRIVERS_USE_WATCHDOG
/*
   ------------------------------------
   ------------- Watchdog -------------
   ------------------------------------
*/

/**
 * WDT_DEVICE_ID
 */
#if !defined WDT_DEVICE_ID
#define WDT_DEVICE_ID							XPAR_SCUWDT_0_DEVICE_ID
#endif

/**
 * WDT_RESET_ADDRESS
 */
#if !defined WDT_RESET_ADDRESS
#define WDT_RESET_ADDRESS						0
#endif

/**
 * WDT_INTERRUPT_ID
 */
#if !defined WDT_INTERRUPT_ID
#define WDT_INTERRUPT_ID						XPS_SCU_WDT_INT_ID
#endif

/**
 * WDT_INTERRUPT_PRIORITY
 */
#if !defined WDT_INTERRUPT_PRIORITY
#define WDT_INTERRUPT_PRIORITY					80
#endif

#endif

#if JBDRIVERS_USE_GPT

/*
   ------------------------------------
   --------------- GPT ----------------
   ------------------------------------
*/

/**
 * GPT_NUM_INSTANCES
 */
#if !defined GPT_NUM_INSTANCES
#define GPT_NUM_INSTANCES					XPAR_AXI_TIMER_TDD_NUM_INSTANCES
#endif

/**
 * GPT_BASE_ADDRESSES
 */
#if !defined GPT_BASE_ADDRESSES
#define GPT_BASE_ADDRESSES					{XPAR_AXI_TIMER_TDD_0_S00_AXI_BASEADDR}
#endif

/**
 * GPT_INTERRUPT_IDS
 */
#if !defined GPT_INTERRUPT_IDS
#define GPT_INTERRUPT_IDS					{XPS_FPGA11_INT_ID}
#endif

/**
 * GPT_INTERRUPT_PRIORITIES
 */
#if !defined GPT_INTERRUPT_PRIORITIES
#define GPT_INTERRUPT_PRIORITIES			{80}
#endif

/**
 * GPT_CLOCKS
 */
#if !defined GPT_CLOCKS
#define GPT_CLOCKS							{100000000U}
#endif

#endif


#if JBDRIVERS_USE_IPC
/*
   ------------------------------------
   -------------- IPC -----------------
   ------------------------------------
*/
/**
 * IPC_SHARED_MEMORY_A9_0_GATE
 */
#if !IPC_SHARED_MEMORY_A9_0_GATE
#define IPC_SHARED_MEMORY_A9_0_GATE				0x1FA00000
#endif

/**
 * IPC_SHARED_MEMORY_A9_1_GATE
 */
#if !IPC_SHARED_MEMORY_A9_1_GATE
#define IPC_SHARED_MEMORY_A9_1_GATE				0x1FB00000
#endif

/**
 * IPC_INTERRUPT_PRIORITY
 */
#if !defined IPC_INTERRUPT_PRIORITY
#define IPC_INTERRUPT_PRIORITY					80
#endif

/**
 * IPC_INTERRUPT_ID
 */
#if !defined IPC_INTERRUPT_ID
#define IPC_INTERRUPT_ID						0
#endif

#endif

#if JBDRIVERS_USE_QSPI_FLASH
/*
   ------------------------------------
   ----------- QSPI FLASH -------------
   ------------------------------------
*/

/**
 * QSPI_FLASH_USE_FILE_SYSTEM
 */
#if !QSPI_FLASH_USE_FILE_SYSTEM
#define QSPI_FLASH_USE_FILE_SYSTEM				0
#endif

/**
 * QSPI_FLASH_USE_CONSOLE
 */
#if !QSPI_FLASH_USE_CONSOLE
#define QSPI_FLASH_USE_CONSOLE					0
#endif

/**
 * QSPI_DEVICE_ID
 */
#if !defined QSPI_DEVICE_ID
#if !defined XPAR_XQSPIPS_0_DEVICE_ID
#define QSPI_DEVICE_ID							0
#else
#define QSPI_DEVICE_ID							XPAR_XQSPIPS_0_DEVICE_ID
#endif
#endif

/**
 * QSPI_FLASH_DISK_BASE_ADDRESS
 */
#if !QSPI_FLASH_DISK_BASE_ADDRESS
#define QSPI_FLASH_DISK_BASE_ADDRESS			0x01000000
#endif

/**
 * QSPI_FLASH_DISK_SIZE
 */
#if !QSPI_FLASH_DISK_SIZE
#define QSPI_FLASH_DISK_SIZE					(1024*1024)
#endif


/*
   ------------------------------------
   --------- NVM Parameters -----------
   ------------------------------------
*/

/**
 * NVM_PARAMETERS_BASE_ADDRESS
 */
#if !defined NVM_PARAMETERS_BASE_ADDRESS
#define NVM_PARAMETERS_BASE_ADDRESS				(0x01FC0000)
#endif

/**
 * NVM_PARAMETERS_SIZE
 */
#if !defined NVM_PARAMETERS_SIZE
#define NVM_PARAMETERS_SIZE						(8*1024)
#endif

#endif


#if JBDRIVERS_USE_CAN
/*
   ------------------------------------
   -------------- CAN -----------------
   ------------------------------------
*/

/**
 * CAN_USE_UAVCAN
 */
#if !defined CAN_USE_UAVCAN
#define CAN_USE_UAVCAN				0
#endif

/**
 * CAN_USE_CONSOLE
 */
#if !defined CAN_USE_CONSOLE
#define CAN_USE_CONSOLE				0
#endif

/**
 * CAN_TX_QUEUE_SIZE //must be a power of 2
 */
#if !defined CAN_TX_QUEUE_SIZE
#define CAN_TX_QUEUE_SIZE			64
#endif

/**
 * CAN_RX_QUEUE_SIZE //must be a power of 2
 */
#if !defined CAN_RX_QUEUE_SIZE
#define CAN_RX_QUEUE_SIZE			64
#endif

/**
 * CAN_NUM_INSTANCES
 */
#if !defined CAN_NUM_INSTANCES
#define CAN_NUM_INSTANCES			XPAR_XCANPS_NUM_INSTANCES
#endif

/**
 * CAN_DEVICE_IDS
 */
#if !defined CAN_DEVICE_IDS
#define CAN_DEVICE_IDS				{XPAR_PS7_CAN_0_DEVICE_ID, XPAR_PS7_CAN_1_DEVICE_ID}
#endif

/**
 * CAN_INTERRUPT_IDS
 */
#if !defined CAN_INTERRUPT_IDS
#define CAN_INTERRUPT_IDS			{XPS_CAN0_INT_ID, XPS_CAN1_INT_ID}
#endif

/**
 * CAN_CLOCKS
 */
#if !defined CAN_CLOCKS
#define CAN_CLOCKS					{XPAR_PS7_CAN_0_CAN_CLK_FREQ_HZ, XPAR_PS7_CAN_1_CAN_CLK_FREQ_HZ}
#endif

/**
 * CAN_INTERRUPT_PRIORITIES
 */
#if !defined CAN_INTERRUPT_PRIORITIES
#define CAN_INTERRUPT_PRIORITIES	{80, 80}
#endif

#endif


#endif /* ZYNQ_JBDRIVERS_OPTS_H_ */
