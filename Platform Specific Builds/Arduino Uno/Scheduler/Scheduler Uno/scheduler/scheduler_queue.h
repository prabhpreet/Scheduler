/*
 * ready_queue.h
 *
 * Created: 18-11-2014 18:02:49
 *  Author: Prabhpreet
 */ 


#ifndef READY_QUEUE_H_
#define READY_QUEUE_H_

#include "scheduler_setup.h"
#include "scheduler_data_structures.h"
#include "scheduler_queue_memory.h"
#include "scheduler_queue_library.h"
#include "scheduler_timer.h"

#include "uart_library.h"

void scheduler_queue_init();
void ready_queue_add(process*);
process* ready_queue_next();
void transfer_wait_ready();
void wait_queue_add(process*);
process* wait_queue_next();

#endif /* READY_QUEUE_H_ */

