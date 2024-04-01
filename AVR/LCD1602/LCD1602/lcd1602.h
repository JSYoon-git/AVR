#ifndef __LCD1602_H
#define __LCD1602_H

//#define LCD_ADDR 0x27
#define LCD_ADDR (0x27 << 1)

#define PIN_RS    (1 << 0)
#define PIN_EN    (1 << 2)
#define BACKLIGHT (1 << 3)

#define LCD_DELAY_MS 5

void I2C_Scan(void);
unsigned char LCD_SendInternal(unsigned char lcd_addr, unsigned char data, unsigned char flags);
unsigned char LCD_SendCommand(unsigned char lcd_addr, unsigned char cmd);
unsigned char LCD_SendData(unsigned char lcd_addr, unsigned char data);
void LCD_Init(unsigned char lcd_addr);
void LCD_SendString(unsigned char lcd_addr, char *str);

#endif
