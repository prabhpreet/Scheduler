/*
 * scheduler.h
 * Includes scheduler function
 * Created: 18-11-2014 18:56:57
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_
#include <stdlib.h>
#include "scheduler_queue.h"
#include "scheduler_timer.h"
#include "scheduler_data_structures.h"
#include "scheduler_context_saving.h"


void scheduler_init(process*, int);
void scheduler();
void scheduler_transition();
void scheduler_error(scheduler_errors, char*);
void scheduler_nothing();

sp _scheduler_nothing_sp;

void scheduler_init(process *pointer, int max)
{
	int i;
	process* p;
	task = next_wait = NULL;
	scheduler_queue_init();
	
	_scheduler_nothing_sp = (sp) malloc(SCHEDULER_NOTHING_STACK_SPACE) + SCHEDULER_NOTHING_STACK_SPACE;
	
	if(_scheduler_nothing_sp == (int) NULL)
	{
		scheduler_error(halt, "Not enough allocation space");
	}
	
	//Initialize all processes here, allocate a stack to them.
	for(i = 0, p = pointer; i < max;i++, p++)
	{
		p->pcb_start = (sp) malloc(p->max_stack_space);
		
		if(p->pcb_start == (int) NULL)
		{
			scheduler_error(halt, "Not enough allocation space");
		}
		
		p->pcb_end = p->stack_pointer = p->pcb_start + p->max_stack_space;
		if(check(p->state,PERIODIC))
		{
			p->deadline=p->period;
			p->state = clear(p->state, NO_DEADLINE);
		}
		ready_queue_add(p);
	}	
	
	scheduler_timer_init();
}


void scheduler()
{
	while(1)
	{
		cli();
		transfer_wait_ready();
		next_wait = wait_queue_next();
		task = ready_queue_next();
		
		if(task == NULL && next_wait == NULL)
		{	//lcd_string("ERROR");
			break;
		}			
		if(next_wait != NULL)
			scheduler_timer_set(next_wait->deadline);
		
		
		scheduler_transition();
	
		//lcd_string("W");
	}
}

void scheduler_transition()
{
	scheduler_save_context();
	scheduler_sp = SP;
	if(task != NULL)
		SP = task->stack_pointer;
	else
		SP = _scheduler_nothing_sp;
	
	if(task == NULL)
	{
		//lcd_string("F");
		sei();
		scheduler_nothing();
	}
	else
	{
		if(task->stack_pointer == task->pcb_end)
		{
			
			//lcd_string("G");
			sei();
			task->function();
			//lcd_string("Z");
		}
		else
		{
			//cli();
			//lcd_string("Y");
			//if(characters == 14)
			//{
				//characters = 0;
				//lcd_cursor(1,1);
			//}
			//sei();
			scheduler_restore_context();
			//cli();
			//lcd_string("H");
			//if(characters == 14)
			//{
				//characters = 0;
				//lcd_cursor(1,1);
			//}		
			//sei();
			sei();	
			return;
		}
	}
	
			
	cli();
	if(task != NULL)
	{
		task->stack_pointer = task->pcb_end;
		wait_queue_add(task);
		//lcd_string("I");	
	}
	SP = scheduler_sp;
	scheduler_restore_context();
	//lcd_string("J");
	//sei();
}

void scheduler_nothing()
{
	while(1);
}

#endif /* SCHEDULER_H_ */