#include <regx52.h>

sbit ON = P1^0;
sbit OFF = P1^2;

// Ham dung chuong trinh trong ? milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void Init_Uart()
{
	// chon timer 8bit tu nap lai 
	TMOD &= 0x0F;
	TMOD |= 0x20;
	
	// chon truyen che do 1 8bit toc do baud duoc cai boi timer1
	SM0 = 0;
	SM1 = 1;
	
	// cai dat toc do baud 9600 bang cach nap cho thanh ghi TH1 
	TH1 = 0xFD;
	
	TI = 1;
	// khoi dong timer 1
	TR1 = 1;
}

void Uart_Write(unsigned char _data)
{
	while(TI == 0);
	TI = 0;
	SBUF = _data;
}


void main()
{
	Init_Uart();
	while(1)
	{
		if(ON == 0)
		{
			Sleep_ms(20);
			if(ON == 0)
			{
				Uart_Write(0x01);
				while(ON == 0);
			}
		}
		else if(OFF == 0)
		{
			Sleep_ms(20);
			{
				if(OFF == 0)
				{
					Uart_Write(0x02);
					while(OFF == 0);
				}
			}
		}
	}
}