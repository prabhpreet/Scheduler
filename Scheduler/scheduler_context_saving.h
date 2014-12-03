/*
 * scheduler_context_saving.h
 *
 * Created: 30-11-2014 18:00:59
 *  Author: Prabhpreet
 */ 


#ifndef SCHEDULER_CONTEXT_SAVING_H_
#define SCHEDULER_CONTEXT_SAVING_H_

#define scheduler_save_context() \
asm volatile ("push r1\n\t" \
"push r0\n\t" \
"in r0,0x3f\n\t" \
"push r0\n\t" \
"in r0,0x3b\n\t" \
"push r0\n\t" \
"clr r1\n\t" \
"push r16\n\t" \
"push r17\n\t" \
"push r18\n\t" \
"push r19\n\t" \
"push r20\n\t" \
"push r21\n\t" \
"push r22\n\t" \
"push r23\n\t" \
"push r24\n\t" \
"push r25\n\t" \
"push r26\n\t" \
"push r27\n\t" \
"push r28\n\t" \
"push r29\n\t" \
"push r30\n\t" \
"push r31\n\t" \
::)


#define scheduler_restore_context() \
asm volatile( \
	"pop r31\n\t" \
	"pop r30\n\t" \
	"pop r29\n\t" \
	"pop r28\n\t" \
	"pop r27\n\t" \
	"pop r26\n\t" \
	"pop r25\n\t" \
	"pop r24\n\t" \
	"pop r23\n\t" \
	"pop r22\n\t" \
	"pop r21\n\t" \
	"pop r20\n\t" \
	"pop r19\n\t" \
	"pop r18\n\t" \
	"pop r17\n\t" \
	"pop r16\n\t" \
	"pop r0\n\t" \
	"out 0x3b,r0\n\t" \
	"pop r0\n\t" \
	"out 0x3f,r0\n\t" \
	"pop r0\n\t" \
	"pop r1\n\t" \
::)


#endif /* SCHEDULER_CONTEXT_SAVING_H_ */