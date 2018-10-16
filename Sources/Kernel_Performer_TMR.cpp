/*
 * Kernel_Performer_TMR.cpp
 *
 *  Created on: 26.10.2017
 *      Author: Stalker1290
 */

#include "Kernel_Performer_TMR.hpp"
#include "CONTROLLER.hpp"



Kernel_Performer_tmr_t::Kernel_Performer_tmr_t(VOID_TIMER_t* VOID_TMR_ptr):Event_timer_t(VOID_TMR_ptr)
{
	this->Event_br = 0;
	this->Event_bw = 0;
}
volatile Callback_Interface_t* tmpCall;
volatile void* tmpData;

void Kernel_Performer_tmr_t::void_callback(void* Intf_ptr, void* parameters)
{
	CONTROLLER_t::get_CONTROLLER()->GPIO_ON(LED4);
	//CONTROLLER_t::get_CONTROLLER()->GPIO_ON(LED5);
	uint32_t temp_bw;
	uint32_t temp_br;

	this->Stop();

	temp_bw = this->Event_bw;
	temp_br = this->Event_br;

	while(temp_bw != temp_br)
	{
		tmpCall = this->callbacks[temp_br];
		if(((Callback_Interface_t*) tmpCall) != (Callback_Interface_t*)NULL)
		{
			tmpData = (void*) this->Event_data[temp_br];
			if(this->Event_data[temp_br] != NULL) {
				((Callback_Interface_t*) tmpCall)->void_callback((void*)this, this->Event_data[temp_br]);
			}
			this->callbacks[temp_br] = (Callback_Interface_t*)NULL;
			this->Event_data[temp_br] = NULL;
		}
		temp_br++;
		temp_br = temp_br == Event_TMR_size_of_events ? 0 : temp_br;
	}
	this->Event_br = temp_br;
	//CONTROLLER_t::get_CONTROLLER()->GPIO_OFF(LED5);
CONTROLLER_t::get_CONTROLLER()->GPIO_OFF(LED4);
}

void Kernel_Performer_tmr_t::Add_OneTime_Event(uint32_t Delay_us, Callback_Interface_t* Callback, void* data)
{
	uint32_t tempBw;
	tempBw = this->Event_bw;

	this->Event_data[tempBw] = data;
	this->callbacks[tempBw] = Callback;
	tempBw++;
	tempBw = tempBw == Event_TMR_size_of_events ? 0 : tempBw;
	this->Event_bw = tempBw;
	this->Start();

//	this->Event_data[this->Event_bw] = data;
//	this->callbacks[this->Event_bw] = Callback;
//	this->Event_bw++;
//	this->Event_bw = this->Event_bw == Event_TMR_size_of_events ? 0 : this->Event_bw;
//	this->Start();
}

void Kernel_Performer_tmr_t::Add_Cyclic_Event(uint32_t Period_us, Callback_Interface_t* Callback, void* data)
{

}


void Kernel_Performer_tmr_t::DeleteEvent(Callback_Interface_t* Callback, void* data)
{

}

void Kernel_Performer_tmr_t::DeleteEvent(Callback_Interface_t* Callback)
{

}
