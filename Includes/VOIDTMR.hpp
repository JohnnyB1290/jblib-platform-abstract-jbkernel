/*
 * VOIDTMR.hpp
 *
 *  Created on: 23.07.2017
 *      Author: Stalker1290
 */

#ifndef VOIDTMR_HPP_
#define VOIDTMR_HPP_

#include "chip.h"
#include "IRQ_Controller.hpp"
#include "Defines.h"


class VOID_TIMER_t:public IRQ_LISTENER_t
{
public:
	VOID_TIMER_t(void):IRQ_LISTENER_t(){}
	virtual ~VOID_TIMER_t(void){}
	virtual void Initialize(uint32_t us) = 0;
	virtual void Start(void) = 0;
	virtual void Stop(void) = 0;
	virtual void Reset(void) = 0;
	virtual uint32_t GetCounter(void) = 0;
	virtual uint32_t GetUsecCounter(void){ return 0;}
	virtual void SetCounter(uint32_t count) = 0;
	virtual void AddCall(Callback_Interface_t* IntCallback) = 0;
	virtual void DeleteCall(void) = 0;
	virtual void Deinitialize(void) = 0;
};

#endif /* VOIDTMR_HPP_ */
