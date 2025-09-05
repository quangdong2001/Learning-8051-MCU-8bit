#include "IC_7447.h"


void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


void IC_7447()
{
	if(Button == 0)
	{
		unsigned int dem = 0;
		while(1)
		{
			unsigned char tram,chuc,don_vi;
			tram = dem / 100;
			chuc = (dem % 100) / 10;
			don_vi = (dem % 100) % 10;
			TRAM = tram;
			CHUC = chuc;
			DON_VI = don_vi;
			dem++;
			dem = dem % 1000;
			Sleep_ms(900);
		}
	}
}