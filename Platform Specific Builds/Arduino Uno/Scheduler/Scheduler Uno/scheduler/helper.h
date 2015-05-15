/*
 * helper.h
 * Methods for aiding setup processes. DO NOT USE WITH SCHEDULER.
 * 
 * Created: 21-11-2014 23:55:03
 *  Author: Prabhpreet
 */ 


#ifndef HELPER_H_
#define HELPER_H_
#include "scheduler_data_structures.h"
#include "scheduler_timer.h"

sp helper_global_sp;
int calculate_parameters(process* p)
/*Instructions for use: add line STORE_STACK() in the deepest function calling possible*/
{
	int status_code;
	time_t execution_time;
	sp stack_size;
	
	
	scheduler_timer_var = 0;
	execution_time = 0;//TODO: Temporary
	p->pcb_end = SP;
	helper_global_sp = NULL;
	cli();
	TCCR0B = TIMER_PRESCALING_MODE;
	sei();
	
	p->function();
	
	cli();
	TCCR0B = 0x00;
	sei();
	execution_time = scheduler_timer_var;
	p->pcb_start= helper_global_sp;
	p->max_stack_space = stack_size;
	return status_code;
}

void calculate_parameters_stack_size()
{
	helper_global_sp = SP;
}

#endif /* HELPER_H_ */