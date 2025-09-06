#include "Ma_Tran_Phim.h"

unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};


void Sleep_ms(unsigned int t)
{
	unsigned int a,b;
	for(a = 0; a <t; a++)
	{
		for(b = 0; b < 123; b++);	
	}
}

unsigned char Key_Board()
{
	unsigned char key = 0;
	
	// Kiem Tra Cot 1 
	Col1 = 0;
	if( Row1 == 0) key = 1;
	if( Row2 == 0) key = 2;
	if( Row3 == 0) key = 3;
	if( Row4 == 0) key = 4;
	Col1 = 1;
	
	// Kiem Tra Cot 2 
	Col2 = 0;
	if( Row1 == 0) key = 5;
	if( Row2 == 0) key = 6;
	if( Row3 == 0) key = 7;
	if( Row4 == 0) key = 8; 
	Col2 = 1;
		
	// Kiem Tra Cot 3
	Col3 = 0;
	if( Row1 == 0) key = 9;
	if( Row2 == 0) key = 10;
	if( Row3 == 0) key = 11;
	if( Row4 == 0) key = 12;
	Col3 = 1;
	
	// Kiem Tra Cot 4
	Col4 = 0;
	if( Row1 == 0) key = 13;
	if( Row2 == 0) key = 14;
	if( Row3 == 0) key = 15;
	if( Row4 == 0) key = 16;
	Col4 = 1;
	
	return key;
}



void Board()
{
	unsigned char key,tmp;
	while(1)
	{
		key = Key_Board();
		if( key != 0)
		{
			tmp = key;
		}
		
		LED_PORT = LED[tmp/10];
		LED1 = 0;
		Sleep_ms(1);
		LED1 = 1;
			
		LED_PORT = LED[tmp%10];
		LED2 = 0;
		Sleep_ms(1);
		LED2 = 1;
	}
}