#include <avr/io.h>

#include "myI2C.h"

void TWIInit(void)
{
    /*
    SCL_frequency = CPU_Clock_frequency / ( 16 + 2(TWBR) * 4^TWPS_PrescalerValue )

    TWBR = (CPU_Clock_frequency / SCL_frequency - 16) / 2

    TWBR = 0x0C => 16MHz / (16 + 2 * 12 * 4^0) = 400KHz

    TWBR = 0x48 => 16MHz / (16 + 2 * 72 * 4^0) = 160MHz / 160 = 100KHz
    */

    //set SCL to 400kHz
    //TWSR = 0x00;
    //TWBR = 0x0C;

    //set SCL to 100kHz
    TWSR = 0x00;
    TWBR = 0x48;

    //enable TWI
    TWCR = (1<<TWEN);
}

void TWIStart(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

void TWIStop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

void TWIWrite(unsigned char u8data)
{
    TWDR = u8data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);
}

unsigned char TWIReadACK(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
    while ((TWCR & (1<<TWINT)) == 0);

    return TWDR;
}

unsigned char TWIReadNACK(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0);

    return TWDR;
}

unsigned char TWIGetStatus(void)
{
    unsigned char status;

    //mask status
    status = TWSR & 0xF8;

    return status;
}

unsigned char WriteData(unsigned char u8addr, unsigned char *u8data, unsigned char len)
{
    unsigned char i;

    TWIStart();
    if (TWIGetStatus() != 0x08)
        return 0;

    TWIWrite(u8addr);
    if (TWIGetStatus() != 0x18)
        return 0;

    for (i=0; i<len; i++)
    {
        TWIWrite(u8data[i]);
        if (TWIGetStatus() != 0x28)
            return 0;
    }

    TWIStop();

    return 1;
}

unsigned char ReadData(unsigned char u8addr, unsigned char u8reg, unsigned char *u8data)
{
    TWIStart();
    if (TWIGetStatus() != 0x08)
        return 0;

    TWIWrite(u8addr);
    if (TWIGetStatus() != 0x18)
        return 0;

    TWIWrite(u8reg);
    if (TWIGetStatus() != 0x28)
        return 0;

    TWIStart();
    if (TWIGetStatus() != 0x10)
        return 0;

    TWIWrite(u8addr|0x01);
    if (TWIGetStatus() != 0x40)
        return 0;
                  
    *u8data = TWIReadACK();
    if (TWIGetStatus() != 0x50)
        return 0; 

    TWIReadNACK();
    if (TWIGetStatus() != 0x58)
        return 0;

    TWIStop();
    
    delay_us(1);
    
    return 1;
}

