/*
 * scheduler_queue_library.h
 *
 * Created: 02-12-2014 11:05:31
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_QUEUE_LIBRARY_H_
#define SCHEDULER_QUEUE_LIBRARY_H_
#include "scheduler_data_structures.h"
#include "uart_library.h"
//FIFO queue
void scheduler_queue_library_init(queue*);
void scheduler_queue_library_add_end(queue*,queue_node*); //adds to end of queue
void scheduler_queue_library_add_deadline(queue*, queue_node*); //adds to queue according to deadline
void scheduler_queue_library_insert_after(queue*, queue_node*, queue_node*);
void scheduler_queue_library_insert_before(queue*, queue_node*, queue_node*); //inserts queue node before a given queue node
queue_node* scheduler_queue_library_remove(queue*);//removes node at start

void scheduler_queue_library_init(queue* q)
{
	q->start = q->end = NULL;
}

void scheduler_queue_library_add_start(queue* q,queue_node* n)
{
	if(q->end == NULL)
	{
		q->end = n;
		n->next = NULL;
	}
	else
	{
		n->next = q->start;
		n->next->prev = n;
	}
	q->start = n;
	n->prev = NULL;
}

void scheduler_queue_library_add_end(queue* q,queue_node* n)
{
	if(q->start == NULL)
	{
		q->start = n;
		n->prev = NULL;
	}
	else
	{
		n->prev = q->end;
		n->prev->next = n;
	}
	q->end = n;
	n->next = NULL;
}



void scheduler_queue_library_add_deadline(queue* q, queue_node* n)
{
	queue_node* i;
	if(q->start == NULL) //Empty queue
	{
		scheduler_queue_library_add_end(q,n);
		return;
	}		
	
	for(i = q->end; i != NULL; i = i->prev)
	{
		if(i->data->deadline < n->data->deadline)
		{
			scheduler_queue_library_insert_after(q,n,i);
			return;
		}
	}
	scheduler_queue_library_insert_before(q,n,q->start);
	/*
	for(i = q->start; i != NULL; i = i->next)
	{
		if(i->data->deadline > n->data->deadline)
		{
			scheduler_queue_library_insert_before(q,n,i);
			return;
		}
	}
	scheduler_queue_library_insert_after(q,n,q->end);
*/
	//uart_println("E");
	//characters++;
	//if(characters == 14)
	//{
		//characters = 0;
		//lcd_cursor(1,1);
	//}
}
void scheduler_queue_library_insert_after(queue* q, queue_node* n, queue_node* a)
{
	if(a == NULL) return;
	
	n->next = a->next;
	n->prev = a;
	a->next = n;
	
	if(a == q->end)
	{
		q->end = n;
	}	
}

void scheduler_queue_library_insert_before(queue* q, queue_node* n, queue_node* b)
{
	if(b == NULL) return;
	
	n->prev = b->prev;
	n->next = b;
	b->prev = n;
	
	if(b == q->start)
	{
		q->start = n;
	}	
}

queue_node* scheduler_queue_library_remove(queue* q)
{
	queue_node *i;
	if(q->start == NULL) return NULL;
	
	i = q->start;
	
	q->start =q->start->next;
	if(q->start != NULL)
		q->start->prev = NULL;
	return i;
}
#endif /* SCHEDULER_QUEUE_LIBRARY_H_ */