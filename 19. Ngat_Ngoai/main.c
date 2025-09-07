#include <regx51.h>

void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

sbit BTN1 = P1^0;
sbit BTN2 = P1^1;
sbit BTN3 = P1^2;
sbit BTN4 = P1^3;

sbit LED1 = P2^0;
sbit LED2 = P2^1;
sbit LED3 = P2^2;
sbit LED4 = P2^3;


void main()
{
	IT1 = 1;
	EX1 = 1;
	EA = 1;
	
	LED1 = LED2 = LED3 = LED4 = 0;
	while(1)
	{
		PCON = PCON | 0x01;
	}
}

void EX1_ISR(void) interrupt 2
{
	Sleep_ms(2);
	if(BTN1 == 0)
	{
		LED1 = !LED1;
		while(BTN1 == 0);
	}
	if(BTN2 == 0)
	{
		LED2 = !LED2;
		while(BTN2 == 0);
	}
	if(BTN3 == 0)
	{
		LED3 = !LED3;
		while(BTN3 == 0);
	}
	if(BTN4 == 0)
	{
		LED4 = !LED4;
		while(BTN4 == 0);
	}
}