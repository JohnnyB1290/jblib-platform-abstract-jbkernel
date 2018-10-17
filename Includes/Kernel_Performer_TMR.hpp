/*
 * Kernel_Performer_TMR.hpp
 *
 *  Created on: 26.10.2017
 *      Author: Stalker1290
 */

#include "Event_timer.hpp"

#ifndef KERNEL_PERFORMER_TMR_HPP_
#define KERNEL_PERFORMER_TMR_HPP_

class Kernel_Performer_tmr_t:public Event_timer_t
{
public:
	Kernel_Performer_tmr_t(VOID_TIMER_t* VOID_TMR_ptr);
	virtual void Add_Cyclic_Event(uint32_t Period_us, Callback_Interface_t* Callback, void* data);
	virtual void Add_OneTime_Event(uint32_t Delay_us, Callback_Interface_t* Callback, void* data);
	virtual void DeleteEvent(Callback_Interface_t* Callback, void* data);
	virtual void DeleteEvent(Callback_Interface_t* Callback);
	virtual void void_callback(void* Intf_ptr, void* parameters);
private:
	uint32_t Event_bw;
	uint32_t Event_br;
	bool Event_ready[Event_TMR_size_of_events];
};

#endif /* KERNEL_PERFORMER_TMR_HPP_ */
