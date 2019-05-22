/**
 * @file
 * @brief Options for LPC43XX JB Drivers
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
	unsigned char port = 0;
	unsigned char pin = 0;
	unsigned char gpioPort = 0;
	unsigned char gpioPin = 0;
	unsigned char scuMode = 0;
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
#define JBCONTROLLER_BOARD_GPIOS				{{2, 12, 1, 12, SCU_MODE_FUNC0},\
											 	 {2, 11, 1, 11, SCU_MODE_FUNC0},}
#endif

/**
 * JBCONTROLLER_NUM_MAIN_PROCEDURES
 */
#if !defined JBCONTROLLER_NUM_MAIN_PROCEDURES
#define JBCONTROLLER_NUM_MAIN_PROCEDURES				16
#endif

/**
 * JBCONTROLLER_NUM_NOP_DELAY_US
 */
#if !defined JBCONTROLLER_NUM_NOP_DELAY_US
#define JBCONTROLLER_NUM_NOP_DELAY_US			39  //For 204 MHz clock
#endif

/**
 * JBCONTROLLER_NUM_NOP_DELAY_MS
 */
#if !defined JBCONTROLLER_NUM_NOP_DELAY_MS
#define JBCONTROLLER_NUM_NOP_DELAY_MS 			40824  //For 204 MHz clock
#endif



/*
   ------------------------------------
   ------------- Console --------------
   ------------------------------------
*/

/**
 * CONSOLE_TX_BUF_SIZE
 */
#if !defined CONSOLE_TX_BUF_SIZE
#define CONSOLE_TX_BUF_SIZE					128
#endif

/**
 * CONSOLE_TX_MES_MAX_SIZE
 */
#if !defined CONSOLE_TX_MESAGE_MAX_SIZE
#define CONSOLE_TX_MESAGE_MAX_SIZE			64
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
   ----------- IRQ Controller ---------
   ------------------------------------
*/

/**
 * IRQ_CONTROLLER_NUM_CORTEX_LISTENERS
 */
#if !defined IRQ_CONTROLLER_NUM_CORTEX_LISTENERS
#define IRQ_CONTROLLER_NUM_CORTEX_LISTENERS			2
#endif

/**
 * IRQ_CONTROLLER_NUM_PERIPHERAL_LISTENERS
 */
#if !defined IRQ_CONTROLLER_NUM_PERIPHERAL_LISTENERS
#define IRQ_CONTROLLER_NUM_PERIPHERAL_LISTENERS		16
#endif

/*
   ------------------------------------
   ----------- Ethernet Phy -----------
   ------------------------------------
*/

/**
 * ETHERNET_PHY_USE_RESET_PIN
 */
#if !defined ETHERNET_PHY_USE_RESET_PIN
#define ETHERNET_PHY_USE_RESET_PIN			1
#endif

#if ETHERNET_PHY_USE_RESET_PIN

/**
 * ETHERNET_PHY_RESET
 */
#if !defined ETHERNET_PHY_RESET_PORT
#define ETHERNET_PHY_RESET_PORT					1
#endif
#if !defined ETHERNET_PHY_RESET_PIN
#define ETHERNET_PHY_RESET_PIN					0
#endif
#if !defined ETHERNET_PHY_RESET_GPIO_PORT
#define ETHERNET_PHY_RESET_GPIO_PORT			0
#endif
#if !defined ETHERNET_PHY_RESET_GPIO_PIN
#define ETHERNET_PHY_RESET_GPIO_PIN				4
#endif
#if !defined ETHERNET_PHY_RESET_SCU_MODE
#define ETHERNET_PHY_RESET_SCU_MODE				SCU_MODE_FUNC0
#endif

#endif

/**
 * ETHERNET_PHY_TXD0
 */
#if !defined ETHERNET_PHY_TXD0_PORT
#define ETHERNET_PHY_TXD0_PORT					1
#endif
#if !defined ETHERNET_PHY_TXD0_PIN
#define ETHERNET_PHY_TXD0_PIN					18
#endif
#if !defined ETHERNET_PHY_TXD0_SCU_MODE
#define ETHERNET_PHY_TXD0_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_TXD1
 */
#if !defined ETHERNET_PHY_TXD1_PORT
#define ETHERNET_PHY_TXD1_PORT					1
#endif
#if !defined ETHERNET_PHY_TXD1_PIN
#define ETHERNET_PHY_TXD1_PIN					20
#endif
#if !defined ETHERNET_PHY_TXD1_SCU_MODE
#define ETHERNET_PHY_TXD1_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_TXEN
 */
#if !defined ETHERNET_PHY_TXEN_PORT
#define ETHERNET_PHY_TXEN_PORT					0
#endif
#if !defined ETHERNET_PHY_TXEN_PIN
#define ETHERNET_PHY_TXEN_PIN					1
#endif
#if !defined ETHERNET_PHY_TXEN_SCU_MODE
#define ETHERNET_PHY_TXEN_SCU_MODE				SCU_MODE_FUNC6
#endif

/**
 * ETHERNET_PHY_RXD0
 */
#if !defined ETHERNET_PHY_RXD0_PORT
#define ETHERNET_PHY_RXD0_PORT					1
#endif
#if !defined ETHERNET_PHY_RXD0_PIN
#define ETHERNET_PHY_RXD0_PIN					15
#endif
#if !defined ETHERNET_PHY_RXD0_SCU_MODE
#define ETHERNET_PHY_RXD0_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_RXD1
 */
#if !defined ETHERNET_PHY_RXD1_PORT
#define ETHERNET_PHY_RXD1_PORT					0
#endif
#if !defined ETHERNET_PHY_RXD1_PIN
#define ETHERNET_PHY_RXD1_PIN					0
#endif
#if !defined ETHERNET_PHY_RXD1_SCU_MODE
#define ETHERNET_PHY_RXD1_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * ETHERNET_PHY_CRS_DV
 */
#if !defined ETHERNET_PHY_CRS_DV_PORT
#define ETHERNET_PHY_CRS_DV_PORT				1
#endif
#if !defined ETHERNET_PHY_CRS_DV_PIN
#define ETHERNET_PHY_CRS_DV_PIN					16
#endif
#if !defined ETHERNET_PHY_CRS_DV_SCU_MODE
#define ETHERNET_PHY_CRS_DV_SCU_MODE			SCU_MODE_FUNC7
#endif

/**
 * ETHERNET_PHY_MDIO
 */
#if !defined ETHERNET_PHY_MDIO_PORT
#define ETHERNET_PHY_MDIO_PORT					1
#endif
#if !defined ETHERNET_PHY_MDIO_PIN
#define ETHERNET_PHY_MDIO_PIN					17
#endif
#if !defined ETHERNET_PHY_MDIO_SCU_MODE
#define ETHERNET_PHY_MDIO_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_MDC
 */
#if !defined ETHERNET_PHY_MDC_PORT
#define ETHERNET_PHY_MDC_PORT					2
#endif
#if !defined ETHERNET_PHY_MDC_PIN
#define ETHERNET_PHY_MDC_PIN					0
#endif
#if !defined ETHERNET_PHY_MDC_SCU_MODE
#define ETHERNET_PHY_MDC_SCU_MODE				SCU_MODE_FUNC7
#endif

/**
 * ETHERNET_PHY_REF_CLK
 */
#if !defined ETHERNET_PHY_REF_CLK_PORT
#define ETHERNET_PHY_REF_CLK_PORT				1
#endif
#if !defined ETHERNET_PHY_REF_CLK_PIN
#define ETHERNET_PHY_REF_CLK_PIN				19
#endif
#if !defined ETHERNET_PHY_REF_CLK_SCU_MODE
#define ETHERNET_PHY_REF_CLK_SCU_MODE			SCU_MODE_FUNC0
#endif

/**
 * ETHERNET_PHY_USE_MII
 */
#if !defined ETHERNET_PHY_USE_MII
#define ETHERNET_PHY_USE_MII			1
#endif

#if ETHERNET_PHY_USE_MII

/**
 * ETHERNET_PHY_RX_ER
 */
#if !defined ETHERNET_PHY_RX_ER_PORT
#define ETHERNET_PHY_RX_ER_PORT					0x0C
#endif
#if !defined ETHERNET_PHY_RX_ER_PIN
#define ETHERNET_PHY_RX_ER_PIN					9
#endif
#if !defined ETHERNET_PHY_RX_ER_SCU_MODE
#define ETHERNET_PHY_RX_ER_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_RXDV
 */
#if !defined ETHERNET_PHY_RXDV_PORT
#define ETHERNET_PHY_RXDV_PORT					0x0C
#endif
#if !defined ETHERNET_PHY_RXDV_PIN
#define ETHERNET_PHY_RXDV_PIN					8
#endif
#if !defined ETHERNET_PHY_RXDV_SCU_MODE
#define ETHERNET_PHY_RXDV_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_RXD2
 */
#if !defined ETHERNET_PHY_RXD2_PORT
#define ETHERNET_PHY_RXD2_PORT					9
#endif
#if !defined ETHERNET_PHY_RXD2_PIN
#define ETHERNET_PHY_RXD2_PIN					3
#endif
#if !defined ETHERNET_PHY_RXD2_SCU_MODE
#define ETHERNET_PHY_RXD2_SCU_MODE				SCU_MODE_FUNC5
#endif

/**
 * ETHERNET_PHY_RXD3
 */
#if !defined ETHERNET_PHY_RXD3_PORT
#define ETHERNET_PHY_RXD3_PORT					9
#endif
#if !defined ETHERNET_PHY_RXD3_PIN
#define ETHERNET_PHY_RXD3_PIN					2
#endif
#if !defined ETHERNET_PHY_RXD3_SCU_MODE
#define ETHERNET_PHY_RXD3_SCU_MODE				SCU_MODE_FUNC5
#endif

/**
 * ETHERNET_PHY_RXCLK
 */
#if !defined ETHERNET_PHY_RXCLK_PORT
#define ETHERNET_PHY_RXCLK_PORT					0x0C
#endif
#if !defined ETHERNET_PHY_RXCLK_PIN
#define ETHERNET_PHY_RXCLK_PIN					0
#endif
#if !defined ETHERNET_PHY_RXCLK_SCU_MODE
#define ETHERNET_PHY_RXCLK_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_TXD2
 */
#if !defined ETHERNET_PHY_TXD2_PORT
#define ETHERNET_PHY_TXD2_PORT					0x0C
#endif
#if !defined ETHERNET_PHY_TXD2_PIN
#define ETHERNET_PHY_TXD2_PIN					2
#endif
#if !defined ETHERNET_PHY_TXD2_SCU_MODE
#define ETHERNET_PHY_TXD2_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_TXD3
 */
#if !defined ETHERNET_PHY_TXD3_PORT
#define ETHERNET_PHY_TXD3_PORT					0x0C
#endif
#if !defined ETHERNET_PHY_TXD3_PIN
#define ETHERNET_PHY_TXD3_PIN					3
#endif
#if !defined ETHERNET_PHY_TXD3_SCU_MODE
#define ETHERNET_PHY_TXD3_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_TX_ER
 */
#if !defined ETHERNET_PHY_TX_ER_PORT
#define ETHERNET_PHY_TX_ER_PORT					0x0C
#endif
#if !defined ETHERNET_PHY_TX_ER_PIN
#define ETHERNET_PHY_TX_ER_PIN					5
#endif
#if !defined ETHERNET_PHY_TX_ER_SCU_MODE
#define ETHERNET_PHY_TX_ER_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * ETHERNET_PHY_COL
 */
#if !defined ETHERNET_PHY_COL_PORT
#define ETHERNET_PHY_COL_PORT					9
#endif
#if !defined ETHERNET_PHY_COL_PIN
#define ETHERNET_PHY_COL_PIN					6
#endif
#if !defined ETHERNET_PHY_COL_SCU_MODE
#define ETHERNET_PHY_COL_SCU_MODE				SCU_MODE_FUNC5
#endif

#endif

/**
 * ETHERNET_PHY_INTERRUPT_PRIORITY
 */
#if !defined ETHERNET_PHY_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define ETHERNET_PHY_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define ETHERNET_PHY_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 * ETHERNET_PHY_USE_DMA_ERRORS_CONTROL
 */
#if !defined ETHERNET_PHY_USE_DMA_ERRORS_CONTROL
#define ETHERNET_PHY_USE_DMA_ERRORS_CONTROL			1
#endif

#if ETHERNET_PHY_USE_DMA_ERRORS_CONTROL
/**
 * ETHERNET_PHY_DMA_ERRORS_CONTROL_TRESHOLD
 */
#if !defined ETHERNET_PHY_DMA_ERRORS_CONTROL_TRESHOLD
#define ETHERNET_PHY_DMA_ERRORS_CONTROL_TRESHOLD 			32
#endif

#endif

/**
 * ETHERNET_PHY_TX_QUEUE_SIZE
 */
#if !defined ETHERNET_PHY_TX_QUEUE_SIZE
#define ETHERNET_PHY_TX_QUEUE_SIZE			4
#endif

/**
 * ETHERNET_PHY_RX_QUEUE_SIZE
 */
#if !defined ETHERNET_PHY_RX_QUEUE_SIZE
#define ETHERNET_PHY_RX_QUEUE_SIZE			16
#endif

/**
 * ETHERNET_PHY_RX_DESCRIPTOR_BUFFER_SIZE
 */
#if !defined ETHERNET_PHY_RX_DESCRIPTOR_BUFFER_SIZE
#define ETHERNET_PHY_RX_DESCRIPTOR_BUFFER_SIZE			200
#endif

/**
 * ETHERNET_PHY_SPEED
 * ETHERNET_PHY_SPEED == SPEED_10_M		10Mbit
 * ETHERNET_PHY_SPEED == SPEED_100_M 	100Mbit
 * ETHERNET_PHY_SPEED == SPEED_AUTONEG	Autonegotiation
 * ETHERNET_PHY_SPEED == SPEED_1000_M 	1000Mbit
 *
 */
#if !defined ETHERNET_PHY_SPEED
#define ETHERNET_PHY_SPEED			SPEED_AUTONEG
#endif

/**
 * ETHERNET_PHY_USE_CONSOLE
 */
#if !defined ETHERNET_PHY_USE_CONSOLE
#define ETHERNET_PHY_USE_CONSOLE		1
#endif

/*
   ------------------------------------
   ----------- Event router -----------
   ------------------------------------
*/

/**
 * EVENT_ROUTER_INTERRUPT_PRIORITY
 */
#if !defined EVENT_ROUTER_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define EVENT_ROUTER_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define EVENT_ROUTER_INTERRUPT_PRIORITY			3
#endif

#endif

/*
   ------------------------------------
   ----------- Pin interrupt ----------
   ------------------------------------
*/

/**
 * PIN_INTERRUPT_0_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_0_INTERRUPT_PRIORITY
#define PIN_INTERRUPT_0_INTERRUPT_PRIORITY			7
#endif

/**
 * PIN_INTERRUPT_1_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_1_INTERRUPT_PRIORITY
#define PIN_INTERRUPT_1_INTERRUPT_PRIORITY			7
#endif

/**
 * PIN_INTERRUPT_2_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_2_INTERRUPT_PRIORITY
#define PIN_INTERRUPT_2_INTERRUPT_PRIORITY			7
#endif

/**
 * PIN_INTERRUPT_3_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_3_INTERRUPT_PRIORITY
#define PIN_INTERRUPT_3_INTERRUPT_PRIORITY			7
#endif

/**
 * PIN_INTERRUPT_4_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_4_INTERRUPT_PRIORITY
#ifdef CORE_M4
#define PIN_INTERRUPT_4_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define PIN_INTERRUPT_4_INTERRUPT_PRIORITY			3
#endif
#endif

/**
 * PIN_INTERRUPT_5_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_5_INTERRUPT_PRIORITY
#ifdef CORE_M4
#define PIN_INTERRUPT_5_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define PIN_INTERRUPT_5_INTERRUPT_PRIORITY			3
#endif
#endif

/**
 * PIN_INTERRUPT_6_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_6_INTERRUPT_PRIORITY
#define PIN_INTERRUPT_6_INTERRUPT_PRIORITY			7
#endif

/**
 * PIN_INTERRUPT_7_INTERRUPT_PRIORITY
 */
#if !defined PIN_INTERRUPT_7_INTERRUPT_PRIORITY
#define PIN_INTERRUPT_7_INTERRUPT_PRIORITY			7
#endif

/*
   ------------------------------------
   --------------- SSP ----------------
   ------------------------------------
*/

/**
 * SSP_0_SSEL
 */
#if !defined SSP_0_SSEL_PORT
#define SSP_0_SSEL_PORT					0
#endif
#if !defined SSP_0_SSEL_PIN
#define SSP_0_SSEL_PIN					0
#endif
#if !defined SSP_0_SSEL_GPIO_PORT
#define SSP_0_SSEL_GPIO_PORT			0
#endif
#if !defined SSP_0_SSEL_GPIO_PIN
#define SSP_0_SSEL_GPIO_PIN				6
#endif
#if !defined SSP_0_SSEL_SCU_MODE
#define SSP_0_SSEL_SCU_MODE				SCU_MODE_FUNC0
#endif

/**
 * SSP_0_CLK  as alternative you can define SSP_0_CLK_NUM
 */
#if !defined SSP_0_CLK_PORT
#define SSP_0_CLK_PORT					0
#endif
#if !defined SSP_0_CLK_PIN
#define SSP_0_CLK_PIN					0
#endif
#if !defined SSP_0_CLK_SCU_MODE
#define SSP_0_CLK_SCU_MODE				SCU_MODE_FUNC0
#endif

/**
 * SSP_0_MOSI
 */
#if !defined SSP_0_MOSI_PORT
#define SSP_0_MOSI_PORT					0
#endif
#if !defined SSP_0_MOSI_PIN
#define SSP_0_MOSI_PIN					0
#endif
#if !defined SSP_0_MOSI_SCU_MODE
#define SSP_0_MOSI_SCU_MODE				SCU_MODE_FUNC0
#endif

/**
 * SSP_0_MISO
 */
#if !defined SSP_0_MISO_PORT
#define SSP_0_MISO_PORT				0
#endif
#if !defined SSP_0_MISO_PIN
#define SSP_0_MISO_PIN					0
#endif
#if !defined SSP_0_MISO_SCU_MODE
#define SSP_0_MISO_SCU_MODE			SCU_MODE_FUNC0
#endif

/**
 * SSP_0_BITS_PER_FRAME
 */
#if !defined SSP_0_BITS_PER_FRAME
#define SSP_0_BITS_PER_FRAME			SSP_BITS_8
#endif

/**
 * SSP_0_FRAMEFORMAT
 */
#if !defined SSP_0_FRAMEFORMAT
#define SSP_0_FRAMEFORMAT				SSP_FRAMEFORMAT_SPI
#endif

/**
 * SSP_0_FRAMEFORMAT
 */
#if !defined SSP_0_CLOCKMODE
#define SSP_0_CLOCKMODE					SSP_CLOCK_CPHA0_CPOL0
#endif


/**
 * SSP_1_SSEL
 */
#if !defined SSP_1_SSEL_PORT
#define SSP_1_SSEL_PORT					1
#endif
#if !defined SSP_1_SSEL_PIN
#define SSP_1_SSEL_PIN					5
#endif
#if !defined SSP_1_SSEL_GPIO_PORT
#define SSP_1_SSEL_GPIO_PORT			1
#endif
#if !defined SSP_1_SSEL_GPIO_PIN
#define SSP_1_SSEL_GPIO_PIN				8
#endif
#if !defined SSP_1_SSEL_SCU_MODE
#define SSP_1_SSEL_SCU_MODE				SCU_MODE_FUNC0
#endif

/**
 * SSP_1_CLK  as alternative you can define SSP_1_CLK_NUM
 */
#if !defined SSP_1_CLK_PORT
#define SSP_1_CLK_PORT					0
#endif
#if !defined SSP_1_CLK_PIN
#define SSP_1_CLK_PIN					0
#endif
#if !defined SSP_1_CLK_SCU_MODE
#define SSP_1_CLK_SCU_MODE				SCU_MODE_FUNC0
#endif

/**
 * SSP_1_MOSI
 */
#if !defined SSP_1_MOSI_PORT
#define SSP_1_MOSI_PORT					1
#endif
#if !defined SSP_1_MOSI_PIN
#define SSP_1_MOSI_PIN					4
#endif
#if !defined SSP_1_MOSI_SCU_MODE
#define SSP_1_MOSI_SCU_MODE				SCU_MODE_FUNC5
#endif

/**
 * SSP_1_MISO
 */
#if !defined SSP_1_MISO_PORT
#define SSP_1_MISO_PORT				1
#endif
#if !defined SSP_1_MISO_PIN
#define SSP_1_MISO_PIN					3
#endif
#if !defined SSP_1_MISO_SCU_MODE
#define SSP_1_MISO_SCU_MODE			SCU_MODE_FUNC5
#endif

/**
 * SSP_1_BITS_PER_FRAME
 */
#if !defined SSP_1_BITS_PER_FRAME
#define SSP_1_BITS_PER_FRAME			SSP_BITS_8
#endif

/**
 * SSP_0_FRAMEFORMAT
 */
#if !defined SSP_1_FRAMEFORMAT
#define SSP_1_FRAMEFORMAT				SSP_FRAMEFORMAT_SPI
#endif

/**
 * SSP_0_FRAMEFORMAT
 */
#if !defined SSP_1_CLOCKMODE
#define SSP_1_CLOCKMODE					SSP_CLOCK_CPHA0_CPOL0
#endif

/*
   ------------------------------------
   ------------ SGPIO SPI -------------
   ------------------------------------
*/

/**
 * SGPIO_SPI_MOSI
 */
#if !defined SGPIO_SPI_MOSI_PORT
#define SGPIO_SPI_MOSI_PORT					0
#endif
#if !defined SGPIO_SPI_MOSI_PIN
#define SGPIO_SPI_MOSI_PIN					0
#endif
#if !defined SGPIO_SPI_MOSI_SCU_MODE
#define SGPIO_SPI_MOSI_SCU_MODE				SCU_MODE_FUNC0
#endif
#if !defined SGPIO_SPI_MOSI_SLICE_ID
#define SGPIO_SPI_MOSI_SLICE_ID				N
#endif
#if !defined SGPIO_SPI_MOSI_PIN_ID
#define SGPIO_SPI_MOSI_PIN_ID				SGPIO_11
#endif

/**
 * SGPIO_SPI_MISO
 */
#if !defined SGPIO_SPI_MISO_PORT
#define SGPIO_SPI_MISO_PORT					0
#endif
#if !defined SGPIO_SPI_MISO_PIN
#define SGPIO_SPI_MISO_PIN					0
#endif
#if !defined SGPIO_SPI_MISO_SCU_MODE
#define SGPIO_SPI_MISO_SCU_MODE				SCU_MODE_FUNC0
#endif
#if !defined SGPIO_SPI_MISO_SLICE_ID
#define SGPIO_SPI_MISO_SLICE_ID				G
#endif
#if !defined SGPIO_SPI_MISO_PIN_ID
#define SGPIO_SPI_MISO_PIN_ID				SGPIO_10
#endif

/**
 * SGPIO_SPI_SCK
 */
#if !defined SGPIO_SPI_SCK_PORT
#define SGPIO_SPI_SCK_PORT					0
#endif
#if !defined SGPIO_SPI_SCK_PIN
#define SGPIO_SPI_SCK_PIN					0
#endif
#if !defined SGPIO_SPI_SCK_SCU_MODE
#define SGPIO_SPI_SCK_SCU_MODE				SCU_MODE_FUNC0
#endif
#if !defined SGPIO_SPI_SCK_SLICE_ID
#define SGPIO_SPI_SCK_SLICE_ID				D
#endif
#if !defined SGPIO_SPI_SCK_PIN_ID
#define SGPIO_SPI_SCK_PIN_ID				SGPIO_12
#endif

/**
 * SGPIO_SPI_SSEL
 */
#if !defined SGPIO_SPI_SSEL_PORT
#define SGPIO_SPI_SSEL_PORT					0
#endif
#if !defined SGPIO_SPI_SSEL_PIN
#define SGPIO_SPI_SSEL_PIN					0
#endif
#if !defined SGPIO_SPI_SSEL_SCU_MODE
#define SGPIO_SPI_SSEL_SCU_MODE				SCU_MODE_FUNC0
#endif
#if !defined SGPIO_SPI_SSEL_SLICE_ID
#define SGPIO_SPI_SSEL_SLICE_ID				P
#endif
#if !defined SGPIO_SPI_SSEL_PIN_ID
#define SGPIO_SPI_SSEL_PIN_ID				SGPIO_15
#endif

/*
   ------------------------------------
   --------------- UART ---------------
   ------------------------------------
*/

/**
 * UART_0_INTERRUPT_PRIORITY
 */
#if !defined UART_0_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define UART_0_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define UART_0_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 * UART_0_TX
 */
#if !defined UART_0_TX_PORT
#define UART_0_TX_PORT					6
#endif
#if !defined UART_0_TX_PIN
#define UART_0_TX_PIN					4
#endif
#if !defined UART_0_TX_SCU_MODE
#define UART_0_TX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_0_RX
 */
#if !defined UART_0_RX_PORT
#define UART_0_RX_PORT					6
#endif
#if !defined UART_0_RX_PIN
#define UART_0_RX_PIN					5
#endif
#if !defined UART_0_RX_SCU_MODE
#define UART_0_RX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_1_INTERRUPT_PRIORITY
 */
#if !defined UART_1_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define UART_1_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define UART_1_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 * UART_1_TX
 */
#if !defined UART_1_TX_PORT
#define UART_1_TX_PORT					6
#endif
#if !defined UART_1_TX_PIN
#define UART_1_TX_PIN					4
#endif
#if !defined UART_1_TX_SCU_MODE
#define UART_1_TX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_1_RX
 */
#if !defined UART_1_RX_PORT
#define UART_1_RX_PORT					6
#endif
#if !defined UART_1_RX_PIN
#define UART_1_RX_PIN					5
#endif
#if !defined UART_1_RX_SCU_MODE
#define UART_1_RX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_2_INTERRUPT_PRIORITY
 */
#if !defined UART_2_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define UART_2_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define UART_2_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 * UART_2_TX
 */
#if !defined UART_2_TX_PORT
#define UART_2_TX_PORT					6
#endif
#if !defined UART_2_TX_PIN
#define UART_2_TX_PIN					4
#endif
#if !defined UART_2_TX_SCU_MODE
#define UART_2_TX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_2_RX
 */
#if !defined UART_2_RX_PORT
#define UART_2_RX_PORT					6
#endif
#if !defined UART_2_RX_PIN
#define UART_2_RX_PIN					5
#endif
#if !defined UART_2_RX_SCU_MODE
#define UART_2_RX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_3_INTERRUPT_PRIORITY
 */
#if !defined UART_3_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define UART_3_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define UART_3_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 * UART_3_TX
 */
#if !defined UART_3_TX_PORT
#define UART_3_TX_PORT					6
#endif
#if !defined UART_3_TX_PIN
#define UART_3_TX_PIN					4
#endif
#if !defined UART_3_TX_SCU_MODE
#define UART_3_TX_SCU_MODE				SCU_MODE_FUNC2
#endif

/**
 * UART_2_RX
 */
#if !defined UART_3_RX_PORT
#define UART_3_RX_PORT					6
#endif
#if !defined UART_3_RX_PIN
#define UART_3_RX_PIN					5
#endif
#if !defined UART_3_RX_SCU_MODE
#define UART_3_RX_SCU_MODE				SCU_MODE_FUNC2
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
#define SYS_TICK_INTERRUPT_PRIORITY			7
#endif

/*
   ------------------------------------
   ------------- PWM Timer ------------
   ------------------------------------
*/

/**
 * PWM_TIMER_INTERRUPT_PRIORITY
 */
#if !defined PWM_TIMER_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define PWM_TIMER_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define PWM_TIMER_INTERRUPT_PRIORITY			3
#endif

#endif

/*
   ------------------------------------
   ------------- RI Timer -------------
   ------------------------------------
*/

/**
 * RI_TIMER_INTERRUPT_PRIORITY
 */
#if !defined RI_TIMER_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define RI_TIMER_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define RI_TIMER_INTERRUPT_PRIORITY			3
#endif

#endif

/*
   ------------------------------------
   ------------- SCT Timer ------------
   ------------------------------------
*/

/**
 * SCT_TIMER_INTERRUPT_PRIORITY
 */
#if !defined SCT_TIMER_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define SCT_TIMER_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define SCT_TIMER_INTERRUPT_PRIORITY			3
#endif

#endif

/*
   ------------------------------------
   ------------- SPIFI ----------------
   ------------------------------------
*/
/**
 * SPIFI_USE_CONSOLE
 */
#if !defined SPIFI_USE_CONSOLE
#define SPIFI_USE_CONSOLE		1
#endif

/**
 * SPIFI_CLK
 */
#if !defined SPIFI_CLK_PORT
#define SPIFI_CLK_PORT					3
#endif
#if !defined SPIFI_CLK_PIN
#define SPIFI_CLK_PIN					3
#endif
#if !defined SPIFI_CLK_SCU_MODE
#define SPIFI_CLK_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * SPIFI_D3
 */
#if !defined SPIFI_D3_PORT
#define SPIFI_D3_PORT					3
#endif
#if !defined SPIFI_D3_PIN
#define SPIFI_D3_PIN					4
#endif
#if !defined SPIFI_D3_SCU_MODE
#define SPIFI_D3_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * SPIFI_D2
 */
#if !defined SPIFI_D2_PORT
#define SPIFI_D2_PORT					3
#endif
#if !defined SPIFI_D2_PIN
#define SPIFI_D2_PIN					5
#endif
#if !defined SPIFI_D2_SCU_MODE
#define SPIFI_D2_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * SPIFI_D1
 */
#if !defined SPIFI_D1_PORT
#define SPIFI_D1_PORT					3
#endif
#if !defined SPIFI_D1_PIN
#define SPIFI_D1_PIN					6
#endif
#if !defined SPIFI_D1_SCU_MODE
#define SPIFI_D1_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * SPIFI_D0
 */
#if !defined SPIFI_D0_PORT
#define SPIFI_D0_PORT					3
#endif
#if !defined SPIFI_D0_PIN
#define SPIFI_D0_PIN					7
#endif
#if !defined SPIFI_D0_SCU_MODE
#define SPIFI_D0_SCU_MODE				SCU_MODE_FUNC3
#endif

/**
 * SPIFI_CS
 */
#if !defined SPIFI_CS_PORT
#define SPIFI_CS_PORT					3
#endif
#if !defined SPIFI_CS_PIN
#define SPIFI_CS_PIN					8
#endif
#if !defined SPIFI_CS_SCU_MODE
#define SPIFI_CS_SCU_MODE				SCU_MODE_FUNC3
#endif

/*
   ------------------------------------
   ------- FRAM CY15B104Q -------------
   ------------------------------------
*/
/**
 * FRAM_CY15B104Q_USE_CONSOLE
 */
#if !defined FRAM_CY15B104Q_USE_CONSOLE
#define FRAM_CY15B104Q_USE_CONSOLE		1
#endif

/*
   ------------------------------------
   ------- Group Pin Interrupt --------
   ------------------------------------
*/

/**
 *  GROUP_PIN_INTERRUPT_0_INTERRUPT_PRIORITY
 */
#if !defined GROUP_PIN_INTERRUPT_0_INTERRUPT_PRIORITY
#define GROUP_PIN_INTERRUPT_0_INTERRUPT_PRIORITY			7
#endif

/**
 *  GROUP_PIN_INTERRUPT_1_INTERRUPT_PRIORITY
 */
#if !defined GROUP_PIN_INTERRUPT_1_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define GROUP_PIN_INTERRUPT_1_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define GROUP_PIN_INTERRUPT_1_INTERRUPT_PRIORITY			3
#endif

#endif

/*
   ------------------------------------
   --------------- I2C ----------------
   ------------------------------------
*/

/**
 * I2C_1_SDA
 */
#if !defined I2C_1_SDA_PORT
#define I2C_1_SDA_PORT					0
#endif
#if !defined I2C_1_SDA_PIN
#define I2C_1_SDA_PIN					0
#endif
#if !defined I2C_1_SDA_SCU_MODE
#define I2C_1_SDA_SCU_MODE				SCU_MODE_FUNC0
#endif

/**
 * I2C_1_SCL
 */
#if !defined I2C_1_SCL_PORT
#define I2C_1_SCL_PORT					0
#endif
#if !defined I2C_1_SCL_PIN
#define I2C_1_SCL_PIN					0
#endif
#if !defined I2C_1_SCL_SCU_MODE
#define I2C_1_SCL_SCU_MODE				SCU_MODE_FUNC0
#endif

/*
   ------------------------------------
   -------------- IPC -----------------
   ------------------------------------
*/
/**
 * IPC_SHARED_MEMORY_M4_GATE_M0APP
 */
#if !IPC_SHARED_MEMORY_M4_GATE_M0APP
#define IPC_SHARED_MEMORY_M4_GATE_M0APP			0x10007F40
#endif

/**
 * IPC_SHARED_MEMORY_M4_GATE_M0SUB
 */
#if !IPC_SHARED_MEMORY_M4_GATE_M0SUB
#define IPC_SHARED_MEMORY_M4_GATE_M0SUB			0x10007F60
#endif

/**
 * IPC_SHARED_MEMORY_M0APP_GATE_M4
 */
#if !IPC_SHARED_MEMORY_M0APP_GATE_M4
#define IPC_SHARED_MEMORY_M0APP_GATE_M4			0x10007F80
#endif

/**
 * IPC_SHARED_MEMORY_M0APP_GATE_M0SUB
 */
#if !IPC_SHARED_MEMORY_M0APP_GATE_M0SUB
#define IPC_SHARED_MEMORY_M0APP_GATE_M0SUB		0x10007FA0
#endif

/**
 * IPC_SHARED_MEMORY_M0SUB_GATE_M4
 */
#if !IPC_SHARED_MEMORY_M0SUB_GATE_M4
#define IPC_SHARED_MEMORY_M0SUB_GATE_M4			0x10007FC0
#endif

/**
 * IPC_SHARED_MEMORY_M0SUB_GATE_M0APP
 */
#if !IPC_SHARED_MEMORY_M0SUB_GATE_M0APP
#define IPC_SHARED_MEMORY_M0SUB_GATE_M0APP		0x10007FE0
#endif

/**
 * IPC_M4_INTERRUPT_PRIORITY
 */
#if !defined IPC_M4_INTERRUPT_PRIORITY
#define IPC_M4_INTERRUPT_PRIORITY				3
#endif

/**
 *  IPC_M0APP_INTERRUPT_PRIORITY
 */
#if !defined IPC_M0APP_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define IPC_M0APP_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define IPC_M0APP_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 *  IPC_M0SUB_INTERRUPT_PRIORITY
 */
#if !defined IPC_M0SUB_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define IPC_M0SUB_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define IPC_M0SUB_INTERRUPT_PRIORITY			3
#endif

#endif

/*
   ------------------------------------
   ------------ GP Timers -------------
   ------------------------------------
*/

/**
 *  GP_TIMER_0_INTERRUPT_PRIORITY
 */
#if !defined GP_TIMER_0_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define GP_TIMER_0_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define GP_TIMER_0_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 *  GP_TIMER_1_INTERRUPT_PRIORITY
 */
#if !defined GP_TIMER_1_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define GP_TIMER_1_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define GP_TIMER_1_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 *  GP_TIMER_2_INTERRUPT_PRIORITY
 */
#if !defined GP_TIMER_2_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define GP_TIMER_2_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define GP_TIMER_2_INTERRUPT_PRIORITY			3
#endif

#endif

/**
 *  GP_TIMER_3_INTERRUPT_PRIORITY
 */
#if !defined GP_TIMER_3_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define GP_TIMER_3_INTERRUPT_PRIORITY			7
#endif

#ifdef CORE_M0
#define GP_TIMER_3_INTERRUPT_PRIORITY			3
#endif

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
#define NVM_PARAMETERS_BASE_ADDRESS				(0x20040000)
#endif

/*
   ------------------------------------
   ---------------- USB ---------------
   ------------------------------------
*/
/**
 * USB_DEVICE_ROM_USE_CUSTOM_DESCRIPTORS
 */
#if !defined USB_DEVICE_ROM_USE_CUSTOM_DESCRIPTORS
#define USB_DEVICE_ROM_USE_CUSTOM_DESCRIPTORS			0
#endif

/**
 * USB_DEVICE_ROM_USE_CONSOLE
 */
#if !defined USB_DEVICE_ROM_USE_CONSOLE
#define USB_DEVICE_ROM_USE_CONSOLE						1
#endif

/* On LPC18xx/43xx the USB controller requires endpoint queue heads to start on
   a 4KB aligned memory. Hence the mem_base value passed to USB stack init should
   be 4KB aligned.
 */
/**
 * USB_DEVICE_ROM_USB0_STACK_MEM_BASE
 */
#if !defined USB_DEVICE_ROM_USB0_STACK_MEM_BASE
#define USB_DEVICE_ROM_USB0_STACK_MEM_BASE				0x20008000
#endif

/**
 * USB_DEVICE_ROM_USB0_STACK_MEM_SIZE
 */
#if !defined USB_DEVICE_ROM_USB0_STACK_MEM_SIZE
#define USB_DEVICE_ROM_USB0_STACK_MEM_SIZE				0x00004000
#endif

/**
 * USB_DEVICE_ROM_USB1_STACK_MEM_BASE
 */
#if !defined USB_DEVICE_ROM_USB1_STACK_MEM_BASE
#define USB_DEVICE_ROM_USB1_STACK_MEM_BASE				0x2000C000
#endif

/**
 * USB_DEVICE_ROM_USB1_STACK_MEM_SIZE
 */
#if !defined USB_DEVICE_ROM_USB1_STACK_MEM_SIZE
#define USB_DEVICE_ROM_USB1_STACK_MEM_SIZE				0x00004000
#endif

/**
 * USB_MAX_IF_NUM
 * Max interface number used for building USBD ROM.
 */
#if !defined USB_MAX_IF_NUM
#define USB_MAX_IF_NUM									8
#endif

/**
 * USB_MAX_EP_NUM
 *  Max number of EP used for building USBD ROM.
 */
#if !defined USB_MAX_EP_NUM
#define USB_MAX_EP_NUM									6
#endif

/**
 * USB_MAX_PACKET_EP0
 * Max EP0 packet size used for building USBD ROM.
 */
#if !defined USB_MAX_PACKET_EP0
#define USB_MAX_PACKET_EP0								64
#endif

/**
 * USB_FS_MAX_BULK_PACKET
 * MAXP for FS bulk EPs used for building USBD ROM.
 */
#if !defined USB_FS_MAX_BULK_PACKET
#define USB_FS_MAX_BULK_PACKET							64
#endif

/**
 * USB_HS_MAX_BULK_PACKET
 * MAXP for HS bulk EPs used for building USBD ROM.
 */
#if !defined USB_HS_MAX_BULK_PACKET
#define USB_HS_MAX_BULK_PACKET							512
#endif

/**
 *  USB_0_INTERRUPT_PRIORITY
 */
#if !defined USB_0_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define USB_0_INTERRUPT_PRIORITY						7
#endif

#ifdef CORE_M0
#define USB_0_INTERRUPT_PRIORITY						3
#endif

#endif

/**
 *  USB_1_INTERRUPT_PRIORITY
 */
#if !defined USB_1_INTERRUPT_PRIORITY

#ifdef CORE_M4
#define USB_1_INTERRUPT_PRIORITY						7
#endif

#ifdef CORE_M0
#define USB_1_INTERRUPT_PRIORITY						3
#endif

#endif

/*
   ------------------------------------
   -------- COM USB DEVICE ROM --------
   ------------------------------------
*/

/**
 * COM_USB_DEVICE_ROM_NUM_DEVICES
 */
#if !defined COM_USB_DEVICE_ROM_NUM_DEVICES
#define COM_USB_DEVICE_ROM_NUM_DEVICES					2
#endif

/**
 * COM_USB_DEVICE_ROM_CIF_NUM_USB_0
 */
#if !defined COM_USB_DEVICE_ROM_CIF_NUM_USB_0
#define COM_USB_DEVICE_ROM_CIF_NUM_USB_0				2
#endif

/**
 * COM_USB_DEVICE_ROM_DIF_NUM_USB_0
 */
#if !defined COM_USB_DEVICE_ROM_DIF_NUM_USB_0
#define COM_USB_DEVICE_ROM_DIF_NUM_USB_0				3
#endif

/**
 * COM_USB_DEVICE_ROM_IN_EP_USB_0
 */
#if !defined COM_USB_DEVICE_ROM_IN_EP_USB_0
#define COM_USB_DEVICE_ROM_IN_EP_USB_0					0x83
#endif

/**
 * COM_USB_DEVICE_ROM_OUT_EP_USB_0
 */
#if !defined COM_USB_DEVICE_ROM_OUT_EP_USB_0
#define COM_USB_DEVICE_ROM_OUT_EP_USB_0					0x03
#endif

/**
 * COM_USB_DEVICE_ROM_INT_EP_USB_0
 */
#if !defined COM_USB_DEVICE_ROM_INT_EP_USB_0
#define COM_USB_DEVICE_ROM_INT_EP_USB_0					0x84
#endif

/**
 * COM_USB_DEVICE_ROM_CIF_NUM_USB_1
 */
#if !defined COM_USB_DEVICE_ROM_CIF_NUM_USB_1
#define COM_USB_DEVICE_ROM_CIF_NUM_USB_1				2
#endif

/**
 * COM_USB_DEVICE_ROM_DIF_NUM_USB_1
 */
#if !defined COM_USB_DEVICE_ROM_DIF_NUM_USB_1
#define COM_USB_DEVICE_ROM_DIF_NUM_USB_1				3
#endif

/**
 * COM_USB_DEVICE_ROM_IN_EP_USB_1
 */
#if !defined COM_USB_DEVICE_ROM_IN_EP_USB_1
#define COM_USB_DEVICE_ROM_IN_EP_USB_1					0x83
#endif

/**
 * COM_USB_DEVICE_ROM_OUT_EP_USB_1
 */
#if !defined COM_USB_DEVICE_ROM_OUT_EP_USB_1
#define COM_USB_DEVICE_ROM_OUT_EP_USB_1					0x03
#endif

/**
 * COM_USB_DEVICE_ROM_INT_EP_USB_1
 */
#if !defined COM_USB_DEVICE_ROM_INT_EP_USB_1
#define COM_USB_DEVICE_ROM_INT_EP_USB_1					0x84
#endif

/*
   ------------------------------------
   ---------- RNDIS DEVICE ROM --------
   ------------------------------------
*/

/**
 * RNDIS_DEVICE_ROM_CIF_NUM_USB_0
 */
#if !defined RNDIS_DEVICE_ROM_CIF_NUM_USB_0
#define RNDIS_DEVICE_ROM_CIF_NUM_USB_0				0
#endif

/**
 * RNDIS_DEVICE_ROM_DIF_NUM_USB_0
 */
#if !defined RNDIS_DEVICE_ROM_DIF_NUM_USB_0
#define RNDIS_DEVICE_ROM_DIF_NUM_USB_0				1
#endif

/**
 * RNDIS_DEVICE_ROM_IN_EP_USB_0
 */
#if !defined RNDIS_DEVICE_ROM_IN_EP_USB_0
#define RNDIS_DEVICE_ROM_IN_EP_USB_0				0x81
#endif

/**
 * RNDIS_DEVICE_ROM_OUT_EP_USB_0
 */
#if !defined RNDIS_DEVICE_ROM_OUT_EP_USB_0
#define RNDIS_DEVICE_ROM_OUT_EP_USB_0				0x01
#endif

/**
 * RNDIS_DEVICE_ROM_INT_EP_USB_0
 */
#if !defined RNDIS_DEVICE_ROM_INT_EP_USB_0
#define RNDIS_DEVICE_ROM_INT_EP_USB_0				0x82
#endif

/**
 * RNDIS_DEVICE_ROM_CIF_NUM_USB_1
 */
#if !defined RNDIS_DEVICE_ROM_CIF_NUM_USB_1
#define RNDIS_DEVICE_ROM_CIF_NUM_USB_1				0
#endif

/**
 * RNDIS_DEVICE_ROM_DIF_NUM_USB_1
 */
#if !defined RNDIS_DEVICE_ROM_DIF_NUM_USB_1
#define RNDIS_DEVICE_ROM_DIF_NUM_USB_1				1
#endif

/**
 * RNDIS_DEVICE_ROM_IN_EP_USB_1
 */
#if !defined RNDIS_DEVICE_ROM_IN_EP_USB_1
#define RNDIS_DEVICE_ROM_IN_EP_USB_1				0x81
#endif

/**
 * RNDIS_DEVICE_ROM_OUT_EP_USB_1
 */
#if !defined RNDIS_DEVICE_ROM_OUT_EP_USB_1
#define RNDIS_DEVICE_ROM_OUT_EP_USB_1				0x01
#endif

/**
 * RNDIS_DEVICE_ROM_INT_EP_USB_1
 */
#if !defined RNDIS_DEVICE_ROM_INT_EP_USB_1
#define RNDIS_DEVICE_ROM_INT_EP_USB_1				0x82
#endif

/**
 * RNDIS_DEVICE_ROM_RX_QUEUE_SIZE
 */
#if !defined RNDIS_DEVICE_ROM_RX_QUEUE_SIZE
#define RNDIS_DEVICE_ROM_RX_QUEUE_SIZE				4
#endif

/**
 * RNDIS_DEVICE_ROM_TX_QUEUE_SIZE
 */
#if !defined RNDIS_DEVICE_ROM_TX_QUEUE_SIZE
#define RNDIS_DEVICE_ROM_TX_QUEUE_SIZE				4
#endif

/*
   ------------------------------------
   ----------- MSC DEVICE ROM ---------
   ------------------------------------
*/

/**
 * MSC_DEVICE_ROM_IF_NUM_USB_0
 */
#if !defined MSC_DEVICE_ROM_IF_NUM_USB_0
#define MSC_DEVICE_ROM_IF_NUM_USB_0				4
#endif

/**
 * MSC_DEVICE_ROM_IN_EP_USB_0
 */
#if !defined MSC_DEVICE_ROM_IN_EP_USB_0
#define MSC_DEVICE_ROM_IN_EP_USB_0				0x85
#endif

/**
 * MSC_DEVICE_ROM_OUT_EP_USB_0
 */
#if !defined MSC_DEVICE_ROM_OUT_EP_USB_0
#define MSC_DEVICE_ROM_OUT_EP_USB_0				0x05
#endif


#endif /* LPC43XX_JBDRIVERS_OPTS_H_ */
