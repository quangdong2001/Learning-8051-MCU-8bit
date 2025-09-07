#include <regx52.h>

void main()
{
	SM0 = SM1 = 0;
	REN = 1;
	
	while(1)
	{
		P0 = 0x0F;
		P3_2 = 0;
		P3_2 = 1;
		RI = 0;
		while(RI == 0);
		P2 = SBUF;
	}
}