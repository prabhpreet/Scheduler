/*
 * uart_library.c
 *
 * Created: 27-12-2014 09:40:06
 *  Author: Prabhpreet
 */ 
#include "uart_library.h"

void uart_init()
{
	//disable while setting baud rate
	UCSR0B = 0x00;
	UCSR0A = 0x00;
	UCSR0C = 0x00;
	UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01);
	UBRR0H = 0x00; //set baud rate lo
	UBRR0L = 0x08; //set baud rate hi  // 8bit data format
	UCSR0B|= (1<<TXEN0);                // enable receiver and transmitter
	
}

// function to send data
void uart_transmit (char data)
{
	while (!( UCSR0A & (1<<UDRE0)));                // wait while register is free
	UDR0 = data;                              // load data in the register
}

// function to receive data

void uart_println(char* c)
{
	char *p;
	for(p = c; *p != '\0';p++)
	uart_transmit(*p);
	uart_transmit('\n');
}