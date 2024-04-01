#ifndef __MYI2C_H
#define __MYI2C_H

void TWIInit(void);
unsigned char WriteData(unsigned char u8addr, unsigned char *u8data, unsigned char len);
unsigned char ReadData(unsigned char u8addr, unsigned char u8reg, unsigned char *u8data);

#endif
