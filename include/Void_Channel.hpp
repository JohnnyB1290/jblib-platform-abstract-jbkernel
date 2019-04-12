/*
 * Void_channel.h
 *
 * Created: 05.09.2017 12:59:40
 *  Author: Stalker1290
 */ 


#ifndef VOID_CHANNEL_HPP_
#define VOID_CHANNEL_HPP_

#include "chip.h"
#include "Defines.h"
#include "Common_interfaces.hpp"

class void_channel_t
{
public:
	void_channel_t(void){}
	virtual ~void_channel_t(void){}
	virtual void Initialize(void* (*mem_alloc)(size_t),uint16_t tx_buf_size, Channel_Call_Interface_t* call_interface_ptr) = 0;
	virtual void DEInitialize(void) = 0;
	virtual void Tx(uint8_t *mes,uint16_t m_size,void* param) = 0;
	virtual void GetParameter(uint8_t ParamName, void* ParamValue) = 0;
	virtual void SetParameter(uint8_t ParamName, void* ParamValue) = 0;
};

typedef enum
{
	VCOM_RTS_param = 0,
	VCOM_CONNECTED_param,
	VCOM_Tx_full_param,
	VCOM_CTS_param,
	AXI_UART16550_CTS_param,
	AXI_UART16550_TXEmpty_param,
	AXI_UART16550_RTS_clr_param,
	AXI_UART16550_RTS_set_param,
}void_channel_param_t;

#endif /* VOID_CHANNEL_HPP_ */
