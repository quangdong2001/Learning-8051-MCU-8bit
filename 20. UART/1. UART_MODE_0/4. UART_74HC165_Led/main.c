#include <regx52.h>
void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}
sbit ON = P1^3;
sbit OFF = P1^6;
sbit LED = P1^1;
void main()
{
	SM0 = 0;
	SM1 = 0;
	REN = 1;
	P1_1 = 0;
	while(1)
	{
		if(ON == 0)
		{
			Sleep_ms(20);
			if(ON == 0)
			{
				P0 = 0x8F;
				P3_2 = 0;
				P3_2 = 1;
				RI = 0;
				while(RI == 0);
				P2 = SBUF;
			}
		}
		if(OFF == 0)
		{
			Sleep_ms(20);
			if(OFF == 0)
			{
				P0 = 0x0F;
				P3_2 = 0;
				P3_2 = 1;
				RI = 0;
				while(RI == 0);
				P2 = SBUF;
			}
		}
		if(P2_0 == 1)
		{
			LED = 1;
		}
		else
		{
			LED = 0;
		}
	}
}