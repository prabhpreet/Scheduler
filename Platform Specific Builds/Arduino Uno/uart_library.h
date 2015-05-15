/*
 * uart_library.h
 *
 * Created: 04-12-2014 20:48:36
 *  Author: Prabhpreet
 */ 


#ifndef UART_LIBRARY_H_
#define UART_LIBRARY_H_
#define F_CPU 14745600
#define BAUD 115200
#include <avr/io.h>

#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)
void uart_init();
void uart_println(char*);
void uart_transmit(char);



void uart_init()
{
	//disable while setting baud rate
	UCSR2B = 0x00;
	UCSR2A = 0x00;
	UCSR2C = 0x00;
	UCSR2C|= (1<<UCSZ20)|(1<<UCSZ21);
	UBRR2H = 0x00; //set baud rate lo
	UBRR2L = 0x07; //set baud rate hi  // 8bit data format
	UCSR2B|= (1<<TXEN2);                // enable receiver and transmitter
	
}

// function to send data
void uart_transmit (char data)
{
	while (!( UCSR2A & (1<<UDRE2)));                // wait while register is free
	UDR2 = data;                              // load data in the register
}

// function to receive data

void uart_println(char* c)
{
	char *p;
	for(p = c; *p != '\0';p++)
	uart_transmit(*p);
	uart_transmit('\n');
}


#endif /* UART_LIBRARY_H_ */