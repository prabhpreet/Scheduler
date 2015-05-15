/*
 * scheduler_queue_memory.h
 *
 * Created: 29-11-2014 18:03:18
 *  Author: ruchika
 */ 


#ifndef SCHEDULER_QUEUE_MEMORY_H_
#define SCHEDULER_QUEUE_MEMORY_H_

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

queue_node scheduler_queue_memory[MAX_QUEUE_MEMORY];
char scheduler_queue_memory_table[MAX_QUEUE_MEMORY_TABLE];
int scheduler_recent_table;
void scheduler_queue_memory_init()
{
	int i, k;
	char j;
	for(i = 0; i < MAX_QUEUE_MEMORY_TABLE; i++)
	{
		scheduler_queue_memory_table[i] = Q_NODE_EMPTY;
		for(k = 0, j = 0x01; j; j = j << 1, k++)
		{
			scheduler_queue_memory[(i*TABLE_ENTRY_SIZE)+k].page = i;
			scheduler_queue_memory[(i*TABLE_ENTRY_SIZE)+k].offset = k;
			
		}			
		uart_println("Scheduler Memory Init!");
	}
	scheduler_recent_table = 0;
}

queue_node* scheduler_queue_memory_malloc()
{
	int i, j,m;
	char k,n;
	
	
	for(i = 0; i < MAX_QUEUE_MEMORY_TABLE; i++)
	{
		j = (scheduler_recent_table + i) % MAX_QUEUE_MEMORY_TABLE;
		if(scheduler_queue_memory_table[j])
		{
			k = scheduler_queue_memory_table[j];
			
			for(m = j*TABLE_ENTRY_SIZE, n = 0x01; n; n = n << 1, m++)
			{
				if(k & n)
				{
					
					scheduler_queue_memory_table[j] &= ~(n);
					scheduler_recent_table = m;
					return &scheduler_queue_memory[m];
				}
			}
			
			
		}
		
	}
	
	return NULL;
}

void scheduler_queue_memory_free(queue_node* q)
{
	scheduler_queue_memory_table[q->page] |= (1 << q->offset); 
}

#endif /* SCHEDULER_QUEUE_MEMORY_H_ */