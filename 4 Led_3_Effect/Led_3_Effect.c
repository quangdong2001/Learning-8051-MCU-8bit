#include "Led_3_Effect.h"


#if (FREQ_OST == 12000000)
		void Delay(unsigned int t)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
				{
					for(j = 0; j < 123; j++);
				}
		}
		
#elif (FREQ_OST == 40000000)
		void Delay(unsigned int t)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
			{
				for(j = 0; j < 625; j++);
			}
		}
		
#elif (FREQ_OST == 11059200)
		void Delay(unsigned int t)
		{
			unsigned int i,j;
			for(i = 0; i < t; i++)
			{
					for(j = 0; j < 95; j++);
			}
		}
		
#else
		#error " KHONG TOAN TAI HAM DELAY NAO THOA MAN FREQ_OST "
		
		
#endif
		
unsigned char Delay_Test()
{
	unsigned char i;
		for(i = 0; i < 50 ; i++)
			{
				
				Delay(10);
				if(NEXT == 0)
					return 1;
			}
	return 0;
}
		
		
void Led_3_Effect()
{
	unsigned char i,j,k;
	LED = 0x00;
	while(1)
	{
		if(START == 0)
		{
			while(1)
			{	
				while(NEXT == 0);
				LED = 0x00;
				for(i = 0; i < 5; i++)
				{
				if(Delay_Test()) break;
				LED = ~LED;
				}
				while(NEXT == 0);
				LED = 0x00;
				for(i = 0; i < 1; i++)
				{
					unsigned char flag = 0;
					for(j = 0; j < 8; j++)
					{
						LED = LED << 1;
						LED = LED | (1 << 0);
						if(Delay_Test()) 
							{
							flag = 1;
							break;
							}
					}
					if(flag) break;
					for(k = 0; k < 8; k++)
					{
						LED = LED << 1;
						if(Delay_Test())
						{
							flag = 1;
							break;
						}
					}
					if(flag) break;
				}
				while(NEXT == 0);
				LED = 0x55;
				for(i = 0; i < 5; i++)
				{
					if(Delay_Test()) break;
					LED = ~LED;
				}
			}
		}
	}
}
		