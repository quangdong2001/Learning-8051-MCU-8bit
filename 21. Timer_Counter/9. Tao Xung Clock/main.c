#include <regx52.h>

void main()
{
	
	T2CON = 0x00;
	T2MOD = 0x02;
	
	RCAP2H = 0xE8;
	RCAP2L = 0x90;
	
	TR2 = 1;
	
	while(1)
	{
	}
	
}