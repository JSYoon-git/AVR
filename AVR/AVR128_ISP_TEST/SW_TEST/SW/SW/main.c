/*
 * SW.c
 *
 * Created: 2023-10-25 오후 9:58:38
 * Author : Yoon
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>


static unsigned int isSwOnOff = 0x01;
static unsigned int count, blinkPeriod, isSlideInput, isPushInput = 0;

void LedBlinking(unsigned int i_blinkPeriod)
{
	//
	if (isSlideInput == 1)
	{
		if (blinkPeriod >= i_blinkPeriod)
		{
			isSwOnOff = isSwOnOff ^ 0x01;
			
			blinkPeriod = 0;
		}
		PORTC = isSwOnOff;
	}
	else {
		PORTC = 0x00;
	}
	blinkPeriod++;
}

void LedOn(){
	PORTE = (isPushInput == 0x01) ? 0x00 : 0x01;
}

void DigitalSlidingSwInput()
{
	isSlideInput = PINB & 0x01 ? 1:0;
}

void DigitalPushReturnSwInput()
{
	isPushInput = PINE & 0x02 ? 1:0;
}

void Task10ms()
{
	/* Replace with your application function */
	DigitalSlidingSwInput();
	DigitalPushReturnSwInput();
	LedBlinking(100);
	LedOn();
}


ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6;
	count ++;
	
	if(count >= 10)
	{
		Task10ms();
		count = 0;
	}
}

int main(void)
{
	DDRC = 0x01;
	DDRB = 0x00;
	DDRE = 0x01;
	
	
	TCCR0 |= (1 << CS02);
	TIMSK |= (1 << TOIE0);
	TIMSK = 0x01;
	TCNT0 = 0x06;
	sei();
	
	
	while (1) {}
}

