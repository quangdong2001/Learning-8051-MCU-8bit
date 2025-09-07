#include <regx52.h>

void Sleep_ms_Timer2()
{
	unsigned char i;
	for(i = 0; i < 20; i++)
	{
		TR2 = 1;
		while(TF2 == 0);
		TF2 = 0;
		TR2 = 0;
	}
}


void main()
{
	
	T2MOD = 0x00;
	T2CON = 0x00;
	
	
	RCAP2H = 0x3C;
	RCAP2L = 0xB0;
	
	TH2 = 0x3C;
	TL2 = 0xB0;
	
	P2 = 0x00;
	while(1)
	{
		P2 = 0xFF;
		Sleep_ms_Timer2();
		P2 = 0x00;
		Sleep_ms_Timer2();
	}
}