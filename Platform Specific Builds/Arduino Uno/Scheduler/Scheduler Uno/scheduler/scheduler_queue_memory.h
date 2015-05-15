/*
 * scheduler_queue_memory.h
 *
 * Created: 29-11-2014 18:03:18
 *  Author: ruchika
 */ 


#ifndef SCHEDULER_QUEUE_MEMORY_H_
#define SCHEDULER_QUEUE_MEMORY_H_

#include "scheduler_setup.h"
#include "scheduler_data_structures.h"
#include "uart_library.h"

#define TABLE_ENTRY_SIZE 8
#define MAX_QUEUE_MEMORY_REQUIREMENT (MAX_READY_DEADLINE_QUEUE+MAX_READY_NO_DEADLINE_QUEUE+MAX_WAIT_QUEUE)
#define MAX_QUEUE_MEMORY_TABLE ((MAX_QUEUE_MEMORY_REQUIREMENT/TABLE_ENTRY_SIZE) + 1)
#define MAX_QUEUE_MEMORY (MAX_QUEUE_MEMORY_TABLE*TABLE_ENTRY_SIZE)
#define Q_NODE_EMPTY 0xFF
#define Q_NODE_FULL 0x00

void scheduler_queue_memory_init();
queue_node* scheduler_queue_memory_malloc();
void scheduler_queue_memory_free(queue_node* q);

#endif /* SCHEDULER_QUEUE_MEMORY_H_ */