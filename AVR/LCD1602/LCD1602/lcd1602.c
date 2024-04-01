

#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "myI2C.h"
#include "lcd1602.h"

void I2C_Scan(void)
{
    unsigned int i = 0x27;

	printf("Scanning I2C bus...\r\n");

	for(i = 1; i < 128; i++)
	{
		if(LCD_SendCommand(i << 1, 0x01))   
		{
			unsigned char msg[64]={0,};

			snprintf(msg, sizeof(msg), "0x%02X", i);
			printf("%s", msg);
		}
        else
		{
			printf(".");
		}
	}

	printf("\r\n");
}

unsigned char LCD_SendInternal(unsigned char lcd_addr, unsigned char data, unsigned char flags)
{
    unsigned char ret = 0;

    unsigned char tx_buffer[4];

	unsigned char up = data & 0xF0;
	unsigned char lo = (data << 4) & 0xF0;

	tx_buffer[0] = up|flags|BACKLIGHT|PIN_EN;
	tx_buffer[1] = up|flags|BACKLIGHT;
	tx_buffer[2] = lo|flags|BACKLIGHT|PIN_EN;
	tx_buffer[3] = lo|flags|BACKLIGHT;

    ret = WriteData(lcd_addr, tx_buffer, sizeof(tx_buffer));

    if (ret == 0)
        ;//printf("LCD_SendInternal Error[0x%x]\r\n", data);

	_delay_ms(LCD_DELAY_MS);
	return ret;
}

unsigned char LCD_SendCommand(unsigned char lcd_addr, unsigned char cmd)
{
	return LCD_SendInternal(lcd_addr, cmd, 0);
}

unsigned char LCD_SendData(unsigned char lcd_addr, unsigned char data)
{
	return LCD_SendInternal(lcd_addr, data, PIN_RS);
}

void LCD_Init(unsigned char lcd_addr)
{
	// 4-bit mode, 2 lines, 5x7 format
	LCD_SendCommand(lcd_addr, 0x30);
	// display & cursor home (keep this!)
	LCD_SendCommand(lcd_addr, 0x02);
	// display on, right shift, underline off, blink off
	LCD_SendCommand(lcd_addr, 0x0C);
	// clear display (optional here)
	LCD_SendCommand(lcd_addr, 0x01);
}

void LCD_SendString(unsigned char lcd_addr, char *str)
{
	while(*str)
	{
		LCD_SendData(lcd_addr, (unsigned char)(*str));
		str++;
	}
}
