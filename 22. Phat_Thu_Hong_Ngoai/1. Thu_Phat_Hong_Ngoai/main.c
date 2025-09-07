#include <regx52.h>

// Lap trinh tao xung 38kHz de dieu khien phat thu hong ngoai 
void main()
{
	
	T2MOD = 0x02;
	T2CON = 0x00;
	
	RCAP2H = 0xFF;
	RCAP2L = 0xB2;
	
	TH2 = 0xFF;
	TL2 = 0xB2;
	
	TR2 = 1;
	while(1)
	{
		
	}
	
}