#include <regx52.h>

// Ham Sleep
void Sleep_ms(unsigned int _t)
{
	unsigned int i, j;
	for(i = 0; i < _t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Ham Gui 1 bit ra ngoai 
void Send_Bit(bit _bit)
{
	if(_bit)
	{
		TR2 = 1;
		Sleep_ms(1);
		TR2 = 0;
		Sleep_ms(3);
		P1_0 = 1;
	}
	
	else
	{
		TR2 = 1;
		Sleep_ms(3);
		TR2 = 0;
		Sleep_ms(1);
		P1_0 = 1;
	}
}


// Ham Gui 1 byte

void Send_Byte(unsigned char _data)
{
	unsigned char i; 
	for(i = 0; i < 8; i++)
	{
		Send_Bit(_data & 0x80);
		_data <<= 1;
	}
}

void main()
{
	T2CON = 0x00;
	T2MOD = 0x02;
	
	RCAP2H = 0xFF;
	RCAP2L = 0xB2;
	
	TH2 = 0xFF;
	TL2 = 0xB2;
	
	// TR2  = 1;
	Send_Byte(0xF0);
	while(1)
	{
		
	}
}