/*
 * main.c
 *
 * Created: 26-12-2014 23:35:58
 *  Author: Prabhpreet
 */ 
#include "scheduler/scheduler_setup.h"
#include "scheduler/scheduler_data_structures.h"
#include "scheduler/uart_library.h"
#include "scheduler/scheduler.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd.h"

void led_ports_config();
int main(void);
int p1();
int p2();
int p3();

process run[4];

int main()
{
	led_ports_config();
	lcd_port_config();
	lcd_init();
	
	uart_init();
	
	run[0].function = p1;
	run[0].state = set(run[0].state, PERIODIC);
	run[0].period = 61;
	run[0].max_stack_space = (size_t) 50;
	
	run[1].function = p2;
	run[1].state = set(run[1].state, PERIODIC);
	run[1].period = 121;
	run[1].max_stack_space = (size_t) 50;
	
	
	scheduler_init(run, 2);
	
	
	
	return 0;
}

void led_ports_config()
{
	DDRB = DDRB | 0x07;
	PORTB = PORTB & 0xF8;
}

int p1()
{
	PORTB ^= 0x01;
	uart_println("1");
	return 0;
}

int p2()
{
	PORTB ^= 0x02;
	uart_println("2");
	return 0;
}

int p3()
{
	PORTB ^= 0x04;
	uart_println("3");
	return 0;
}

