/*
 * scheduler_data_structures.c
 *
 * Created: 27-12-2014 10:07:11
 *  Author: Prabhpreet
 */ 
#include "scheduler_data_structures.h"

volatile sp scheduler_sp;

void scheduler_error(scheduler_errors e,char* str)
{
	if(e == halt)
	{
		//lcd_cursor(2,1);
		//lcd_string(str);
		abort();
		
	}
}