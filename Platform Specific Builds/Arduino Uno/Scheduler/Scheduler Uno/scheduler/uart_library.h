/*
 * uart_library.h
 *
 * Created: 04-12-2014 20:48:36
 *  Author: Prabhpreet
 */ 


#ifndef UART_LIBRARY_H_
#define UART_LIBRARY_H_
#define BAUD 115200
#include <avr/io.h>

void uart_init();
void uart_println(char*);
void uart_transmit(char);






#endif /* UART_LIBRARY_H_ */