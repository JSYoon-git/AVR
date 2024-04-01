/*
 * LCD1602.c
 *
 * Created: 2023-10-30 오후 9:45:08
 * Author : Yoon
 */ 


#define __DELAY_BACKWARD_COMPATIBLE__
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "function.h"

int main(void)
{
	sei();
	twi_init();

	twi_write1(0x27,0x00);
	_delay_ms(1000);
	//twi_write_lcd_ir_init(0x27,0x20);
	//twi_write_lcd_ir(0x27,0x00,0x10);
	//twi_write_lcd_ir(0x27,0x00,0xf0);
	//twi_write_lcd_dr(0x27,0x40,0x10);
	twi_write1(0x27, 123);
	while(1)
	{
		
	}
}