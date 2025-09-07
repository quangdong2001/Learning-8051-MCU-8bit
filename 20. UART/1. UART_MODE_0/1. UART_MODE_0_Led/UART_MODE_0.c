#include <UART_MODE_0.h>

// Sleep_ms function
void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// UART 

void UART_MODE_0(unsigned char _data)
{
	SM0 = 0;
	SM1 = 0;
	SBUF = _data;
	
	while(TI == 0);
	TI = 0;
	P3_2 = 0;
	P3_2 = 1;

}

void Effect()
{
	unsigned char i, _data, j;
	_data = 0x00;
	for(i = 0; i < 2; i++)
	{
		UART_MODE_0(0xFF);
		Sleep_ms(300);
		UART_MODE_0(0x00);
		Sleep_ms(300);
	}
	for(i = 0; i < 2; i++)
	{
		UART_MODE_0(0x55);
		Sleep_ms(300);
		UART_MODE_0(0xAA);
		Sleep_ms(300);
	}
	for(j = 0; j < 2; j++)
	{
		_data = 0x00;
		UART_MODE_0(_data);
		Sleep_ms(100);
		for(i = 0; i < 8; i++)
		{
			_data <<= 1;
			_data |= 0x01;
			UART_MODE_0(_data);
			Sleep_ms(100);
		}
	}
}