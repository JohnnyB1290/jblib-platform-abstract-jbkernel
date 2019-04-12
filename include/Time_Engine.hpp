/*
 * Time_Engine.hpp
 *
 *  Created on: 4 мая 2018 г.
 *      Author: Stalker1290
 */

#ifndef TIME_ENGINE_HPP_
#define TIME_ENGINE_HPP_

#include "chip.h"
#include "Common_interfaces.hpp"
#include "Event_timer.hpp"
#include "Kernel_Performer_TMR.hpp"
#include "stdlib.h"
#include "Defines.h"

#ifdef USE_TE_RT
#include "GPTimers.hpp"
#endif

typedef struct Time_engine_callback_param_struct
{
	uint8_t TE_module_num;
	void* data;
	uint32_t RT_Timer_moment;
	uint32_t RT_match_moment;
}Time_engine_callback_param_t;

class Time_Engine_t:public Callback_Interface_t
{
public:
	static Time_Engine_t* Get_Time_Engine(void);

#ifdef USE_TE_RT
/**************************RT Module******************************/
	uint32_t RT_getCS(void);
	void RT_setCS(uint32_t ticks);
	void RT_setEvent(uint32_t match_ticks, Callback_Interface_t* call, void* data);
	void RT_changeEvent(uint32_t match_ticks, Callback_Interface_t* call, void* data);
	void RT_clearAllEvents();
	void Add_RT_Timer(GPTimer_t* RT_Timer_ptr);
/*****************************************************************/
#endif

/*************************Delay and Performer*********************/
	void Add_NRT_Timer(uint8_t timer_num, Event_timer_t* Event_tmr_ptr, uint32_t step_us);
	void NRT_setEvent(uint8_t module, uint32_t us, Callback_Interface_t* call, void* data);
	uint16_t getEventsInQueue(uint8_t timer_num);
/*****************************************************************/
	virtual void void_callback(void* Intf_ptr, void* parameters);
private:
	Time_Engine_t(void);
	static Time_Engine_t* Time_Engine_ptr;

#ifdef USE_TE_RT
/**************************RT Module******************************/
	GPTimer_t* RT_Timer_ptr;
	Callback_Interface_t* RT_Callbacks_ptrs[Num_of_matches];
	void* RT_Call_data[Num_of_matches];
	uint32_t RT_event_match_ticks[Num_of_matches];
	Time_engine_callback_param_t output_param_RT;
/*****************************************************************/
#endif

	typedef struct TE_Even_timer_data_struct
	{
		Callback_Interface_t* Out_call_ptr;
		void* Out_data_ptr;
		bool Desc_FREE;
	}TE_Even_timer_data_t;

/**************************NRT Modules***************************/
	Time_engine_callback_param_t output_param_NRT[TE_num_of_NRT];
	Event_timer_t* Event_tmr_ptrs[TE_num_of_NRT];
	TE_Even_timer_data_t Event_timer_data_instances[TE_num_of_NRT][Event_TMR_size_of_events];
/*****************************************************************/
};




#endif /* TIME_ENGINE_HPP_ */
