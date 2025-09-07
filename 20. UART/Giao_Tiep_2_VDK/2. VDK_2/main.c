#include <regx52.h>

sbit LED = P1^0;

void Uart_Init()
{
	// chon timer1 che do 2 8bit tu nap lai 
	TMOD &= 0x0F;
	TMOD |= 0x20;
	
	// chon turyen che do 1 8bit toc do baud duoc cai dat qua timer1 
	SM0 = 0;
	SM1 = 1;
	
	// cai dat toc do baud boi cac nap thanh ghi TH1 
	TH1 = 0xFD;
	
	// chon che do nhan gu lieu thong qua bit REN cua thanh ghi SCON
	REN = 1;
	
	// Khoi dong timer 1
	TR1 = 1;
}

// Ham kiem tra xem co du lieu duoc gui vao hay khong 
unsigned char Uart_Ready()
{
	return RI;
}

unsigned char Uart_Read()
{
	RI = 0;
	return SBUF;
}

 

void main()
{
	LED = 0;
	Uart_Init();
	while(1)
	{
		if(Uart_Ready() == 1)
		{
			if(Uart_Read() == 0x01)
			{
				LED = 1;
			}
			else if(Uart_Read() == 0x02)
			{
				LED = 0;
			}
			while(Uart_Ready() == 0);
		}
	}
}