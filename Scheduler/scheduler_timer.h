/*
 * scheduler_timer.h
 * Using 8-bit zero timer of ATMEGA 2560
 * Created: 22-11-2014 00:42:24
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_TIMER_H_
#define SCHEDULER_TIMER_H_
#include "scheduler_setup.h"
#include "scheduler_data_structures.h"
#include "scheduler_queue.h"
#include "scheduler_context_saving.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>



void scheduler_timer_init();
void scheduler_timer_stop();
void scheduler_timer_set(time_t);
void scheduler_timer_init()
{
	cli();
	TCCR0A = 0x00;
	TCCR0B = TIMER_PRESCALING_MODE;
	TIMSK0 = 0x01;
	clock = 0;
	compare = 0;
	sei();
}


void scheduler_timer_stop()
{
	cli();
	TCCR0B = 0x00;
	clock = 0;
	sei();
}

void scheduler_timer_set(time_t time)
{
	compare = time;
}
ISR(TIMER0_OVF_vect)
{
	clock++;
	
	if(clock >= compare && compare != 0) //NULL never gonna happen!
	{
		//cli();
		//lcd_cursor(2,1);
		//lcd_string("T");
		if(task != NULL)
		{
			lcd_string("V");
			ready_queue_add(task);
			task->stack_pointer = SP;	
		}
		//lcd_string("U");
		SP = scheduler_sp;
		characters++;
		if(characters == 14)
		{
			characters = 0;
			lcd_cursor(1,1);
		}
		compare = 0;
		//sei();	
	}
		
}


#endif /* SCHEDULER_TIMER_H_ */