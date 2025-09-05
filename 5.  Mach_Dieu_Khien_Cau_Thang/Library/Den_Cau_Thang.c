#include "Den_Cau_Thang.h"

void Den_Cau_Thang()
{
	LED_RED = 0;
	while(1)
	{
		if(PORT_UP == 0)
		{
			LED_RED = !LED_RED;     
			while(PORT_UP == 0);    
		}
		if(PORT_DOWN == 0)
		{
			LED_RED = !LED_RED;
			while(PORT_DOWN == 0);
		}
	}
}


#if (FREQ_OSC == 12000000)
		void Delay(unsigned int t)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
			{
					for(j = 0; j < 123; j++);
			}
		}
#elif (FREQ_OSC == 40000000)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
					{
						for(j = 0; j < 525; j++);
					}
		}
#else
		#error "Khong Ton Tai Ham Delay nao Thoa Man"
		
#endif