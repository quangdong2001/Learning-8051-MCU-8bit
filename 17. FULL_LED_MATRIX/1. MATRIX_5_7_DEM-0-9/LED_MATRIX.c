#include "LED_MATRIX.h"

unsigned char code ZERO[] = {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E};
unsigned char code ONE[] = {0x1F, 0x04, 0x04, 0x04, 0x14, 0x0C, 0x04};
unsigned char code TWO[] = {0x1F, 0x18, 0x0C, 0x06, 0x03, 0x11, 0x0E};
unsigned char code THREE[] = {0x0E, 0x11, 0x01, 0x07, 0x01, 0x11, 0x0E};
unsigned char code FOUR[] = {0x02, 0x02, 0x1F, 0x12, 0x08, 0x04, 0x02};
unsigned char code FIVE[] = {0x1F, 0x01, 0x01, 0x1F, 0x10, 0x10, 0x1F};
unsigned char code SIX[] = {0x1F, 0x11, 0x11, 0x1F, 0x10, 0x10, 0x1F};
unsigned char code SEVEN[] = {0x04, 0x04, 0x02, 0x01, 0x01, 0x11, 0x0E};
unsigned char code EIGHT[] = {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E};
unsigned char code NINE[] = {0x0E, 0x11, 0x01, 0x1F, 0x11, 0x11, 0x0E};


void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void Show_Number(unsigned char arr[])
{
	Matrix = arr[0];
	P3_0 = 1;
	Sleep_ms(1);
	P3_0 = 0;
	
	Matrix = arr[1];
	P3_1 = 1;
	Sleep_ms(1);
	P3_1 = 0;
	
	Matrix = arr[2];
	P3_2 = 1;
	Sleep_ms(1);
	P3_2 = 0;
	
	Matrix = arr[3];
	P3_3 = 1;
	Sleep_ms(1);
	P3_3 = 0;
	
	Matrix = arr[4];
	P3_4 = 1;
	Sleep_ms(1);
	P3_4 = 0;
	
	Matrix = arr[5];
	P3_5 = 1;
	Sleep_ms(1);
	P3_5 = 0;
	
	Matrix = arr[6];
	P3_6 = 1;
	Sleep_ms(1);
	P3_6 = 0;
}


void Led_Matrix()
{
	while(1)
	{
		unsigned int i;
		for(i = 0; i < 142; i++)
		{
			Show_Number(ZERO);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(ONE);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(TWO);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(THREE);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(FOUR);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(FIVE);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(SIX);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(SEVEN);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(EIGHT);
		}
		for(i = 0; i < 142; i++)
		{
			Show_Number(NINE);
		}
	}
}



















































