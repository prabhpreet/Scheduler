/*
 * scheduler_data_structures.h
 * Declaration of scheduler data structures and global scheduler variables
 * Created: 22-11-2014 00:01:22
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_DATA_STRUCTURES_H_
#define SCHEDULER_DATA_STRUCTURES_H_
#include <stdlib.h>


/*States*/

#define PERIODIC 0x01
#define NO_DEADLINE 0x02
#define TIMER_TRANSITION 0x01
#define SCHEDULER_NOTHING_STACK_SPACE 200

volatile int characters;

/*Scheduler Errors*/
enum _scheduler_errors {halt, resume};
typedef enum _scheduler_errors scheduler_errors;
typedef int sp;
typedef unsigned long long time_t;
typedef struct
{
	int (*function)();
	time_t deadline;
	time_t period;
	char state;
	size_t max_stack_space;
	
	sp pcb_start;
	sp pcb_end;
	sp stack_pointer;
}process;

struct _qnode{
	process* data;
	struct _qnode *prev, *next;
	int page;
	char offset;
};

typedef struct _qnode queue_node;

typedef struct{
	queue_node* start, *end;
}queue;

typedef struct
{
	queue_node q_n;
	char state;
}queue_memory;





void scheduler_error(scheduler_errors, char*);

//TODO: Convert check, set, clear to macros
#define check(state, flag) ((state & flag) == flag)
#define set(state, flag) state | flag
#define clear(state, flag) state & ~(flag)

#endif /* SCHEDULER_DATA_STRUCTURES_H_ */