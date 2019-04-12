/*
 * Event_timer.hpp
 *
 *  Created on: 04 Aug 2017 ã.
 *      Author: Stalker1290
 */

#ifndef EVENT_TIMER_HPP_
#define EVENT_TIMER_HPP_

#include "chip.h"
#include "VOIDTMR.hpp"
#include "Defines.h"
#include "Common_interfaces.hpp"

class Event_timer_t:public Callback_Interface_t
{
public:
	Event_timer_t(VOID_TIMER_t* VOID_TMR_ptr);
	void Initialize(uint32_t step_us);
	void DEInitialize(void);
	void Start(void);
	void Stop(void);
	virtual void Add_Cyclic_Event(uint32_t Period_us, Callback_Interface_t* Callback, void* data);
	virtual void Add_OneTime_Event(uint32_t Delay_us, Callback_Interface_t* Callback, void* data);
	virtual void DeleteEvent(Callback_Interface_t* Callback, void* data);
	virtual void DeleteEvent(Callback_Interface_t* Callback);
	virtual void void_callback(void* Intf_ptr, void* parameters);
	virtual uint16_t getEventsInQueue();
protected:
	VOID_TIMER_t* VOID_TMR_ptr;
	uint32_t step_us;
	Callback_Interface_t* callbacks[Event_TMR_size_of_events];
	void* Event_data[Event_TMR_size_of_events];
	uint32_t Event_period[Event_TMR_size_of_events];
	uint32_t Event_counter[Event_TMR_size_of_events];
	bool Event_one_time[Event_TMR_size_of_events];
//	bool added[Event_TMR_size_of_events];
	bool stopped;
  bool queueProcessing;
};



#endif /* EVENT_TIMER_HPP_ */
