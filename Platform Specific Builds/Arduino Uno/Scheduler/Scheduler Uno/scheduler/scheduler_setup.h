/*
 * scheduler_setup.h
 *
 * Created: 22-11-2014 00:04:03
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_SETUP_H_
#define SCHEDULER_SETUP_H_

#define F_CPU 16000000
#define DISPATCHER_LATENCY 0
#define SETUP_MODE 1

/*STACK SPACE*/
#define MAX_STACK_SPACE 400

/*QUEUES*/
#define MAX_READY_DEADLINE_QUEUE 5
#define MAX_READY_NO_DEADLINE_QUEUE 10
#define MAX_WAIT_QUEUE 10

/*TIMER*/
#define TIMER_PRESCALING_MODE 0x05 //See manual, Prescaler mode = 1024.
#define TIMER_INTERRUPT TIMER0_OVF_vect
/*UART*/
#define BAUD 115200


#endif /* SCHEDULER_SETUP_H_ */