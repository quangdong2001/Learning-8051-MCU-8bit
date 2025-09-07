#include "UART_MODE_0_7Seg.h"

unsigned char code _Data[] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09};

void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0 ; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void UART_MODE_0(unsigned char _data)
{
	SM0 = 0;
	SM1 = 0;
	SBUF = _data;
	while(TI == 0);
	TI = 0;
	
	P3_2 = 0;
	P3_2 = 1;
}

void Effect()
{
	unsigned char i;
	for(i = 0; i <= 9; i++)
	{
		UART_MODE_0(_Data[i]);
		Sleep_ms(1000);
	}
	
}