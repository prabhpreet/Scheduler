/*
 * scheduler.c
 *
 * Created: 27-12-2014 00:43:32
 *  Author: Prabhpreet
 */ 
#include "scheduler.h"

sp _scheduler_nothing_sp;

process* task, *next_wait;
volatile sp scheduler_sp;

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
		{
			break;
		}
		if(next_wait != NULL)
			scheduler_timer_set(next_wait->deadline);
		scheduler_transition();
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
		sei();
		scheduler_nothing();
	}
	else
	{
		if(task->stack_pointer == task->pcb_end)
		{
			sei();
			task->function();
		}
		else
		{
			scheduler_restore_context();
			sei();
			return;
		}
	}
	cli();
	if(task != NULL)
	{
		task->stack_pointer = task->pcb_end;
		wait_queue_add(task);
	}
	
	SP = scheduler_sp;
	scheduler_restore_context();
	
}

void scheduler_nothing()
{
	uart_println("Nothing");
	while(1);
}

