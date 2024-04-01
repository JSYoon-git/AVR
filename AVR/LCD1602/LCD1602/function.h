/*
 * IncFile1.h
 *
 * Created: 2023-10-30 오후 9:46:53
 *  Author: Yoon
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

void twi_init()
{
	PORTD |= 0x03; // SDA,SCL pull-up setting PD0: SCL, PD1: SDA
	/* SCL 100kHz */
	TWBR = 0x48;
	TWSR = 0x00;
	
	TWCR = (1<<TWINT)|(1<<TWEN);
}

unsigned char twi_write_lcd_ir_init(unsigned char add, unsigned char dat1)
{
	int i;
	_delay_ms(1);
	dat1 |= 0x08;
	/* STEP1 Start */
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN); //start

	/* STEP2 Start check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x08))
		break;
	}

	/* STEP3 Address send */
	TWDR = add<<1 | 0; // slave address, write
	TWCR = (1<<TWINT)|(1<<TWEN);

	/* STEP4 ACK Check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) ==0x18))
		break;
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x20))
		return 0;
	}
	
	for(i=0; i<3; i++)
	{
		/* STEP5 Data1 send */
		if(i==1)
		TWDR = dat1 | 0x04;
		else
		TWDR = dat1;
		TWCR = (1<<TWINT)|(1<<TWEN);
		/* STEP6 Data send check */
		while(1)
		{
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
			break;
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
			return 0;
		}
		_delay_us(100);
	}

	/* STEP9 STOP */
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	return 1;
}

unsigned char twi_write_lcd_ir(unsigned char add, unsigned char dat1, unsigned char dat2)
{
	int i;
	_delay_ms(1);
	dat1 |= 0x08;
	dat2 |= 0x08;
	/* STEP1 Start */
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN); //start

	/* STEP2 Start check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x08))
		break;
	}

	/* STEP3 Address send */
	TWDR = add<<1 | 0; // slave address, write
	TWCR = (1<<TWINT)|(1<<TWEN);

	/* STEP4 ACK Check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) ==0x18))
		break;
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x20))
		return 0;
	}
	
	for(i=0; i<3; i++)
	{
		/* STEP5 Data1 send */
		if(i==1)
		TWDR = dat1 | 0x04;
		else
		TWDR = dat1;
		TWCR = (1<<TWINT)|(1<<TWEN);
		/* STEP6 Data send check */
		while(1)
		{
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
			break;
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
			return 0;
		}
		_delay_us(100);
	}
	for(i=0; i<3; i++)
	{
		/* STEP5 Data1 send */
		if(i==1)
		TWDR = dat2 | 0x04;
		else
		TWDR = dat2;
		TWCR = (1<<TWINT)|(1<<TWEN);
		/* STEP6 Data send check */
		while(1)
		{
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
			break;
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
			return 0;
		}
		_delay_us(100);
	}

	
	
	/* STEP9 STOP */
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	return 1;
}
unsigned char twi_write_lcd_dr(unsigned char add, unsigned char dat1, unsigned char dat2)
{
	int i;
	_delay_ms(1);
	dat1 |= (0x08 | 0x01);
	dat2 |= (0x08 | 0x01);
	/* STEP1 Start */
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN); //start

	/* STEP2 Start check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x08))
		break;
	}

	/* STEP3 Address send */
	TWDR = add<<1 | 0; // slave address, write
	TWCR = (1<<TWINT)|(1<<TWEN);

	/* STEP4 ACK Check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) ==0x18))
		break;
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x20))
		return 0;
	}
	
	for(i=0; i<3; i++)
	{
		/* STEP5 Data1 send */
		if(i==1)
		TWDR = dat1 | 0x04;
		else
		TWDR = dat1;
		TWCR = (1<<TWINT)|(1<<TWEN);
		/* STEP6 Data send check */
		while(1)
		{
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
			break;
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
			return 0;
		}
		_delay_us(100);
	}
	for(i=0; i<3; i++)
	{
		/* STEP5 Data1 send */
		if(i==1)
		TWDR = dat2 | 0x04;
		else
		TWDR = dat2;
		TWCR = (1<<TWINT)|(1<<TWEN);
		/* STEP6 Data send check */
		while(1)
		{
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
			break;
			if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
			return 0;
		}
		_delay_us(100);
	}

	
	
	/* STEP9 STOP */
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	return 1;
}

unsigned char twi_write1(unsigned char add, unsigned char dat1)
{
	/* STEP1 Start */
	TWCR = (1<<TWSTA)|(1<<TWINT)|(1<<TWEN); //start

	/* STEP2 Start check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x08))
		break;
	}

	/* STEP3 Address send */
	TWDR = add<<1 | 0; // slave address, write
	TWCR = (1<<TWINT)|(1<<TWEN);

	/* STEP4 ACK Check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) ==0x18))
		break;
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x20))
		return 0;
	}
	
	/* STEP5 Data1 send */
	TWDR = dat1;
	TWCR = (1<<TWINT)|(1<<TWEN);

	/* STEP6 Data send check */
	while(1)
	{
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x28))
		break;
		if((TWCR & 0x80) && ((TWSR & 0xf8) == 0x30))
		return 0;
	}
	

	/* STEP9 STOP */
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	return 1;
}



#endif /* INCFILE1_H_ */