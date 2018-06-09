/*
 * Common_interfaces.hpp
 *
 *  Created on: 04.08.2017
 *      Author: Stalker1290
 */

#ifndef COMMON_INTERFACES_HPP_
#define COMMON_INTERFACES_HPP_

#include "stdint.h"
#include "stdlib.h"

class Callback_Interface_t
{
public:
	Callback_Interface_t(void){}
	virtual ~Callback_Interface_t(void){}
	virtual void void_callback(void* Intf_ptr, void* parameters) = 0;
};

class C_void_callback_t:public Callback_Interface_t
{
public:
	C_void_callback_t(void (*call)(void)):Callback_Interface_t(){ this->call = call; }
	virtual void void_callback(void* Intf_ptr, void* parameters){ if(this->call != NULL) this->call(); }
private:
	void (*call)(void);
};

class C_void_with_param_callback_t:public Callback_Interface_t
{
public:
	C_void_with_param_callback_t(void (*call)(void* parameters)):Callback_Interface_t(){ this->call = call; }
	virtual void void_callback(void* Intf_ptr, void* parameters){ if(this->call != NULL) this->call(parameters); }
private:
	void (*call)(void* parameters);
};

typedef void (*RX_CALLBACK_t)(uint8_t *mes,uint16_t m_size,void* channel_pointer,void* parameters);

class Channel_Call_Interface_t
{
public:
	Channel_Call_Interface_t(void){}
	virtual ~Channel_Call_Interface_t(void){}
	virtual void channel_callback(uint8_t *mes,uint16_t m_size,void* channel_pointer,void* parameters) = 0;
};

class C_channel_call_t:public Channel_Call_Interface_t
{
public:
	C_channel_call_t(RX_CALLBACK_t callback):Channel_Call_Interface_t() {this->callback = callback; }
	virtual void channel_callback(uint8_t *mes,uint16_t m_size,void* channel_pointer, void* parameters)
	{
		if(this->callback != (RX_CALLBACK_t)NULL) this->callback(mes, m_size, channel_pointer, parameters);
	}
private:
	RX_CALLBACK_t callback;
};


#endif /* COMMON_INTERFACES_HPP_ */
