/*
 * 7segment.c
 *
 * Created: 2023-11-03 오후 5:36:31
 * Author : Yoon
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define BYPASS 500

volatile unsigned int segmentCycle=0;
static unsigned int isSwOnOff  = 0x02;
static unsigned int count, isInput, blinkPeriod = 0;
static unsigned int segmentPeriod = 0;
unsigned char FND[10]={0x60, 0x3D, 0x79, 0x63, 0x5B, 0x5F, 0x72, 0x7F, 0x7B, 0x77};


void LedBlinking(unsigned int i_blinkPeriod)
{
	if (isInput == 1)
	{
		//if (blinkPeriod <= i_blinkPeriod)
		if(blinkPeriod <= 50)
		{
			isSwOnOff = isSwOnOff ^ 0x02;
			PORTD = isSwOnOff;
			//
		}else if(blinkPeriod <= i_blinkPeriod)
		{
			PORTD = 0x0;	
		}else{
			PORTD = 0x0;
			blinkPeriod = 0;
		}
		
	}
	else {
		PORTD = 0x0;
		blinkPeriod = 0;
	}
	
	blinkPeriod++;
	
}

void DigitalInput()
{
	isInput = PIND & 0x01 ? 1:0;
}

void segment_cnt(unsigned int i_segmentPeriod)
{
	if (isInput == 1){
		if(segmentPeriod>=i_segmentPeriod){
			segmentCycle = segmentCycle % 10;
			PORTE = FND[segmentCycle];
			segmentCycle++;
			segmentPeriod = 0;
		}
	} else {
		segmentPeriod = 0;
		segmentCycle = 0;
		PORTE = 0x7E;
		
	}
	segmentPeriod++;
}

void Task10ms()
{
	/* Replace with your application function */
	
	DigitalInput();
	LedBlinking(BYPASS);
	segment_cnt(BYPASS*10);
	
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
	DDRE = 0xFF;
	DDRD = 0x02;
	PORTE = 0x7E;
	
	
	TCCR0 |= (1 << CS02);
	TIMSK |= (1 << TOIE0);
	TIMSK = 0x01;
	TCNT0 = 0x06;
	sei();
	
	
	while (1) {}
}
