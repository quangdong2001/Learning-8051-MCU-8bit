#include "Kiem_Tra_Delay.h"

#if(FREQ_OSC == 12000000)

	void Delay(unsigned int t)
	{
		unsigned int i,j;
		for(i = 0;i < t ;i++)
		{
				for(j = 0;j < 123 ;j++);
		}
	}
#else
	#error "KHONG TON TAI HAM DELAY THOA MAN !!!"
	
#endif
	

	
void Kiem_Tra_Delay()
{
	unsigned char i;
	unsigned char flag;
	LED = 0x00;
	while(1)
	{
		if(START == 0)
		{
			while(1)
			{
				flag = 0;
				LED = ~LED;
				for(i = 0;i < 100;i++)
				{
					Delay(10);
					if(STOP == 0)
					{
						LED = 0x00;
						flag = 1;
						break;
					}	
				}
				if(flag == 1)
					break;
			}
		}
	}
}