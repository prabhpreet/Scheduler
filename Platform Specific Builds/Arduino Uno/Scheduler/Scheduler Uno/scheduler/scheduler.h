/*
 * scheduler.h
 * Includes scheduler function
 * Created: 18-11-2014 18:56:57
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "scheduler_setup.h"
#include "scheduler_data_structures.h"
#include "scheduler_queue.h"
#include "scheduler_timer.h"
#include "scheduler_context_saving.h"
#include <avr/interrupt.h>

extern process* task, *next_wait;
extern volatile sp scheduler_sp;

void scheduler_init(process*, int);
void scheduler();
void scheduler_transition();
void scheduler_nothing();



#endif /* SCHEDULER_H_ */