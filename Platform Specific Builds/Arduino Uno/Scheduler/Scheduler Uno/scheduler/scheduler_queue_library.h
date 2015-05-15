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
queue_node* scheduler_queue_library_remove(queue*);//removes node at start

#endif /* SCHEDULER_QUEUE_LIBRARY_H_ */