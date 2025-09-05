#include "Giao_Tiep_Voi_Relay.h"

void Delay(unsigned int t)
{
	unsigned char i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void Giao_Tiep_Voi_Relay()
{
	Relay = 0;
	while(1)
	{
		if(ON_OFF == 0)
		{
			Relay = !Relay;
			while(ON_OFF == 0);
		}
	}
}
