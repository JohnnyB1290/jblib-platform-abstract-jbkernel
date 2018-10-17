/*
 * Event_timer.cpp
 *
 *  Created on: 04 Aug 2017 ã.
 *      Author: Stalker1290
 */

#include "Event_timer.hpp"
#include "string.h"

Event_timer_t::Event_timer_t(VOID_TIMER_t* VOID_TMR_ptr):Callback_Interface_t()
{
	this->VOID_TMR_ptr = VOID_TMR_ptr;
	for(int i=0; i<Event_TMR_size_of_events; i++)
	{
		this->callbacks[i] = (Callback_Interface_t*)NULL;
		this->Event_period[i] = 0;
		this->Event_counter[i] = 0;
		this->Event_data[i] = NULL;
		this->Event_one_time[i] = false;
	}
	this->stopped = true;
	this->queueProcessing = false;
}

void Event_timer_t::void_callback(void* Intf_ptr, void* parameters)
{
	Callback_Interface_t* Temp_callbacks[Event_TMR_size_of_events];
	void* Temp_Event_data[Event_TMR_size_of_events];

	this->Stop();
	this->queueProcessing = true;

	memcpy(Temp_callbacks, this->callbacks, Event_TMR_size_of_events*sizeof(Callback_Interface_t*));
	memcpy(Temp_Event_data, this->Event_data, Event_TMR_size_of_events*sizeof(void*));
	
	for(int i=0; i<Event_TMR_size_of_events;i++)
	{
		if(Temp_callbacks[i] != (Callback_Interface_t*)NULL)
		{
			this->Event_counter[i]++;
			if(this->Event_counter[i] >= this->Event_period[i])
			{
				if(this->Event_one_time[i])
				{
					this->Event_period[i] = 0;
					this->Event_data[i] = NULL;
					this->Event_one_time[i] = false;
					this->callbacks[i] = (Callback_Interface_t*)NULL;
				}
				this->Event_counter[i] = 0;
				Temp_callbacks[i]->void_callback((void*)this, Temp_Event_data[i]);
			}
		}
	}
	this->queueProcessing = false;
	for(int i=0; i<Event_TMR_size_of_events;i++)
		if(this->callbacks[i] != (Callback_Interface_t*)NULL)
			this->Start();
}



void Event_timer_t::Initialize(uint32_t step_us)
{
	if(this->VOID_TMR_ptr == (VOID_TIMER_t*) NULL) return;
	this->step_us = step_us;
	this->VOID_TMR_ptr->Initialize(step_us);
	this->VOID_TMR_ptr->AddCall(this);
}

void Event_timer_t::DEInitialize(void)
{
	if(this->VOID_TMR_ptr == (VOID_TIMER_t*) NULL) return;
	this->VOID_TMR_ptr->Deinitialize();
}

void Event_timer_t::Start(void)
{
	if(this->queueProcessing) return;	
	if(this->VOID_TMR_ptr == (VOID_TIMER_t*) NULL) return;
	this->VOID_TMR_ptr->Start();
	this->stopped = false;
}

void Event_timer_t::Stop(void)
{
	if(this->VOID_TMR_ptr == (VOID_TIMER_t*) NULL) return;
	this->VOID_TMR_ptr->Reset();
	this->VOID_TMR_ptr->Stop();
	this->stopped = true;
}


void Event_timer_t::Add_Cyclic_Event(uint32_t Period_us, Callback_Interface_t* Callback, void* data)
{
	for(int i = 0; i < Event_TMR_size_of_events; i++)
	{
		__disable_irq();
		if(this->callbacks[i] == (Callback_Interface_t*)NULL)
		{
			this->Event_data[i] = data;
			this->callbacks[i] = Callback;
			this->Event_counter[i] = 0;
			this->Event_one_time[i] = false;
			this->Event_period[i] = Period_us/this->step_us;
			if(this->Event_period[i] == 0) this->Event_period[i] = 1;
			if(this->stopped) this->Start();
			__enable_irq();
			break;
		}
		__enable_irq();
	}
}

void Event_timer_t::Add_OneTime_Event(uint32_t Delay_us, Callback_Interface_t* Callback, void* data)
{
	for(int i = 0; i < Event_TMR_size_of_events; i++)
	{
		__disable_irq();
		if(this->callbacks[i] == (Callback_Interface_t*)NULL)
		{
			this->Event_data[i] = data;
			this->callbacks[i] = Callback;
			this->Event_counter[i] = 0;
			this->Event_one_time[i] = true;
			this->Event_period[i] = Delay_us/this->step_us;
			if(this->Event_period[i] == 0) this->Event_period[i] = 1;
			if(this->stopped) this->Start();
			__enable_irq();
			break;
		}
		__enable_irq();
	}
}

void Event_timer_t::DeleteEvent(Callback_Interface_t* Callback)
{
	for(int i = 0; i < Event_TMR_size_of_events; i++)
	{
		if(this->callbacks[i] == Callback)
		{
			this->Event_period[i] = 0;
			this->callbacks[i] = (Callback_Interface_t*)NULL;
			this->Event_counter[i] = 0;
			this->Event_data[i] = NULL;
			this->Event_one_time[i] = false;
			break;
		}
	}
}

void Event_timer_t::DeleteEvent(Callback_Interface_t* Callback, void* data)
{
	for(int i = 0; i < Event_TMR_size_of_events; i++)
	{
		if((this->callbacks[i] == Callback)&&(this->Event_data[i] == data))
		{
			this->Event_period[i] = 0;
			this->callbacks[i] = (Callback_Interface_t*)NULL;
			this->Event_counter[i] = 0;
			this->Event_data[i] = NULL;
			this->Event_one_time[i] = false;
			break;
		}
	}
}
