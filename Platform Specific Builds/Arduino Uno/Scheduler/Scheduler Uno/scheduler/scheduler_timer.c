/*
 * scheduler_timer.c
 *
 * Created: 27-12-2014 10:41:21
 *  Author: Prabhpreet
 */ 
#include "scheduler_timer.h"
volatile time_t clock;
volatile time_t compare;

char str[10];

//ISR(TIMER_INTERRUPT) __attribute__ ( ( signal, naked ) );

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

ISR(TIMER_INTERRUPT, ISR_NAKED)
{
	cli();
	scheduler_save_context();
	clock++;
	if(clock >= compare && compare != 0) //NULL never gonna happen!
	{
		if(task != NULL)
		{
			ready_queue_add(task);
			task->stack_pointer = SP;
			uart_println("R");
		}
		SP = scheduler_sp;
		compare = 0;
		uart_println("Save.");
		scheduler_restore_context();
		uart_println("Wow.");
		reti(); //Required since ISR is naked!
	}
	scheduler_restore_context();
	reti(); //Required since ISR is naked!
}