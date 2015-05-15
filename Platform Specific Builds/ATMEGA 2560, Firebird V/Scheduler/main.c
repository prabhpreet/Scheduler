/*
 * Main.c
 *
 * Created: 18-11-2014 14:40:50
 *  Author: Prabhpreet
 */ 

#define F_CPU 14745600
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "scheduler_data_structures.h"
#include "scheduler_queue.h"
#include "lcd.h"
#include "uart_library.h"
#include "scheduler.h"
#include <stdio.h>


int main(void);
int p1();
int p2();
int p3();
int p4();
//void scheduler_transition();
//int test();
//void stack_height();
process run[4];


int main(void)
{
	uart_init();
	lcd_port_config();
	lcd_init();
	
	characters = 0;
	DDRJ = 0xFF;
	PORTJ = 0x00;
	
	run[0].function = p1;
	run[0].state = set(run[0].state, PERIODIC);
	run[0].period = 56;
	run[0].exc_time = 12;
	run[0].max_stack_space = (size_t) 50;
	
	run[1].function = p2;
	run[1].state = set(run[1].state, PERIODIC);
	run[1].period = 112;
	run[1].exc_time = 12;
	run[1].max_stack_space = (size_t) 50;
	
	run[2].function = p3;
	run[2].state = set(run[2].state, PERIODIC);
	run[2].period = 168;
	run[2].exc_time = 12;
	run[2].max_stack_space = (size_t) 50;
	
	run[3].function = p4;
	run[3].max_stack_space = (size_t) 50;
	run[3].state = set(run[3].state, NO_DEADLINE);
	run[3].state = clear(run[3].state, PERIODIC);
	
	/*
	queue_node b;
	queue_node* s;
	s->data = &run[0];
	
	char st[10];
	if(!check(s->data->state, PERIODIC))
	{
		sprintf(st,"%x", s->data->state);
		uart_println(st);
		
	}
	*/
	uart_println("R");
	scheduler_init(run, 3);
	
	/*clock = 0;
	
	queue_node* n;
	for(n = ready_deadline.start; n != NULL; n = n->next)
	n->data->function();
	for(n = ready_no_deadline.start; n != NULL; n = n->next)
	n->data->function();
	for(n = wait.start; n != NULL; n = n->next)
	n->data->function();
	uart_println("|");
	
	wait_queue_add(ready_queue_next());
	
	
	wait_queue_add(ready_queue_next());
	
	clock = 112;
	ready_queue_add(wait_queue_ready());
	ready_queue_add(wait_queue_ready());
	for(n = ready_deadline.start; n != NULL; n = n->next)
	n->data->function();
	for(n = ready_no_deadline.start; n != NULL; n = n->next)
	n->data->function();
	for(n = wait.start; n != NULL; n = n->next)
	n->data->function();
	uart_println("|");
	
	*/
	scheduler();
	
	
	uart_println("Q");
	while(1);
}



int p1()
{
	char a[20]="1";
	cli();
	lcd_string(a);
	uart_println(a);
	characters++;
	if(characters == 14)
	{
		characters = 0;
		lcd_cursor(1,1);
	}
	PORTJ ^= 0x01;
	sei();
	return 0;
}
int p2()
{
	char b[20]="2";
	cli();
	lcd_string(b);
	uart_println(b);
	characters++;
	if(characters == 14)
	{
		characters = 0;
		lcd_cursor(1,1);
	}
	PORTJ ^= 0x02;
	sei();
	return 0;
}

int p3()
{
	cli();
	char c[20]="3";
	lcd_string(c);
	uart_println(c);
	characters++;
	if(characters == 14)
	{
		characters = 0;
		lcd_cursor(1,1);
	}
	PORTJ ^= 0x04;
	sei();
	return 0;
}
int p4()
{
	cli();
	char c[20]="4";
	lcd_string(c);
	uart_println(c);
	characters++;
	if(characters == 14)
	{
		characters = 0;
		lcd_cursor(1,1);
	}
	sei();
	/*
	 int i,n,u;
	 char c = 1;
	 unsigned long long j;
	 for(j=0;j<1000;j++)
	 {
		 n=15;
		
		 u=n;
		 for(i=1;i<u;i++)
		 {
			 n=n*(u-i);
		 }
		 
		 PORTJ = c;
		 c = c << 1;
		 if(c == 0)
		 c = 1;
		 _delay_ms(100);
		 
	 }
	 */
	
	 return 0;
}
//int test()
//{
	//char string[10];
	//lcd_home();
	//sprintf(string, "%d.\n", SP);
	//uart_println(string);
	//stack_height();
	//return 0;
//}
//
void stack_height()
{
	char string[10];
	//lcd_cursor(2,1);
	sprintf(string, "%d", SP);
	//uart_println(string);
}


