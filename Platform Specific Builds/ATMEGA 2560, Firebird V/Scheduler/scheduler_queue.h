/*
 * ready_queue.h
 *
 * Created: 18-11-2014 18:02:49
 *  Author: Prabhpreet
 */ 


#ifndef READY_QUEUE_H_
#define READY_QUEUE_H_

#include "uart_library.h"
#include "scheduler_setup.h"
#include "scheduler_data_structures.h"
#include "scheduler_queue_memory.h"
#include "scheduler_queue_library.h"

queue ready_deadline, ready_no_deadline, wait;

void scheduler_queue_init();
void ready_queue_add(process*);
void transfer_wait_ready();
process* wait_queue_next();
void ready_queue_sort();
void wait_queue_add(process*);

process* wait_queue_ready();

void scheduler_queue_init()
{
	scheduler_queue_memory_init();
	scheduler_queue_library_init(&ready_deadline);
	scheduler_queue_library_init(&ready_no_deadline);
	scheduler_queue_library_init(&wait);
	
}

void ready_queue_add(process* t)
{
	queue_node *n;
	if(t==NULL) return;
	n = scheduler_queue_memory_malloc();
	if(n == NULL)
	{
		scheduler_error(halt, "Ready queue no space");
	}
	n->data=t;
	
	if(check(t->state, NO_DEADLINE) && !check(t->state, PERIODIC))
	{
		scheduler_queue_library_add_end(&ready_no_deadline, n);//TODO: FIFO starvation of deadline queues- solution circular queues
	}
	else
	{
		if(t->deadline <= clock)
		{
			t->deadline = t->deadline + t->period;
			uart_println("Ready queue add: Deadline has passed");
		}			
		scheduler_queue_library_add_deadline(&ready_deadline, n);	
	}	
	
}
//check
process* ready_queue_next()
{
	queue_node *i;
	process *p;
	if(ready_deadline.start == NULL)
	{
		if(ready_no_deadline.start == NULL)
			return NULL;
		else
		{
			i = scheduler_queue_library_remove(&ready_no_deadline);
		}
	}
	else
	{
		i = scheduler_queue_library_remove(&ready_deadline);
	}
	p=i->data;
	scheduler_queue_memory_free(i);
	return p;
}

void transfer_wait_ready()
{
	queue_node *i;
	process *r;
	if(wait.start==NULL) return;
	for(i = wait.start; i != NULL; i = i->next)
	{
		if(clock >= i->data->deadline)
		{
			i= scheduler_queue_library_remove(&wait);
			r=i->data;
			if(check(r->state,PERIODIC))
			{
				r->deadline= r->deadline + r->period;
			}
			scheduler_queue_library_add_deadline(&ready_deadline, i);
		}
		else
			return;
	}

}



void wait_queue_add(process* q)
{
	queue_node *n;
	if(!check(q->state,PERIODIC)) return;	 
	n = scheduler_queue_memory_malloc();
	if(n == NULL)
	{
		scheduler_error(halt, "Wait queue no space");
	}
	scheduler_queue_library_add_deadline(&wait, n);
}

process* wait_queue_next()
{
	return (wait.start == NULL)?NULL:wait.start->data;
}	

#endif /* READY_QUEUE_H_ */

