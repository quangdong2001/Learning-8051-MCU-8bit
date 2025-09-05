#include "IC_2803.h"

void Delay(unsigned int t)
{
	unsigned char i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void IC_ULN2803()
{
	if(ON_OFF == 0)
	{
		LED = !LED;
	}
	while(ON_OFF == 0);
}