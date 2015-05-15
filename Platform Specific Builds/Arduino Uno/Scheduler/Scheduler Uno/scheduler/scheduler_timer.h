/*
 * scheduler_timer.h
 * Using 8-bit zero timer of ATMEGA 2560
 * Created: 22-11-2014 00:42:24
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_TIMER_H_
#define SCHEDULER_TIMER_H_
#include "scheduler_setup.h"
#include "scheduler_data_structures.h"
#include "scheduler_queue.h"
#include "scheduler_context_saving.h"
#include "scheduler.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

extern volatile time_t clock;
extern volatile time_t compare;

void scheduler_timer_init();
void scheduler_timer_stop();
void scheduler_timer_set(time_t);




#endif /* SCHEDULER_TIMER_H_ */