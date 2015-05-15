#ifndef LCD_H_
#define LCD_H_

#define RS 0
#define RW 2
#define EN 3
#define lcd_port_direction DDRD
#define lcd_port PORTD

#define sbit(reg,bit)	reg |= (1<<bit)			// Macro defined for Setting a bit of any register.
#define cbit(reg,bit)	reg &= ~(1<<bit)		// Macro defined for Clearing a bit of any register.

#include "scheduler/scheduler_setup.h"
#include <avr/io.h>
#include <util/delay.h>

void lcd_port_config();
void lcd_reset();
void lcd_init();
void lcd_wr_command(unsigned char);
void lcd_wr_char(char);
void lcd_line1();
void lcd_line2();
void lcd_string(char*);
void lcd_cursor(char, char);


#endif