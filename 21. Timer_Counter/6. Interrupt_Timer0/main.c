#include <regx52.h>

unsigned int _count = 10;
void Sleep_ms(unsigned int t)
{
	unsigned int i , j;
	 for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void main()
{
	
	// Cau hinh cho timer 0 che do 1 16bit 
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	// Nap gia tri cho TL0, TH0
	
	TH0 = 0x3C;
	TL0 = 0xB0;
	
  ET0 = 1;
	EA = 1;
	TR0 = 1;
	
	while(1)
	{
		P1 = ~P1;
	}
}

void Ngat_Timer0(void) interrupt 1
{
	TR0 = 0;
	TH0 = 0x3C;
	TL0 = 0xB0;
	_count--;
	if(_count == 0)
	{
		_count = 10;
		P2 = ~P2;
	}
	TR0 = 1;
}