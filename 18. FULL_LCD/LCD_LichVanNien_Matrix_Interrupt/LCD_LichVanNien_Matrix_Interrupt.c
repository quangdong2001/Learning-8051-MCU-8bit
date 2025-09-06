#include "LCD_LichVanNien_Matrix_Interrupt.h"

unsigned char code Number[10][6]= {
																		0xC1, 0x80, 0xAE, 0xB6, 0x80, 0xC1,      // 0
																		0xFE, 0xEE, 0x80, 0x80, 0xFE, 0xFE,      // 1
																		0xDC, 0x98, 0xBA, 0xB6, 0x86, 0xCE,      // 2
																		0xDD, 0x9C, 0xB6, 0xB6, 0x80, 0xC9,      // 3
																		0xF3, 0xEB, 0xDB, 0x80, 0x80, 0xFB,      // 4
																		0x8D, 0x8C, 0xAE, 0xAE, 0xA0, 0xB1,      // 5
																		0xC1, 0x80, 0xB6, 0xB6, 0x90, 0xD9,      // 6
																		0x9F, 0x9F, 0xB8, 0xA0, 0x87, 0x9F,      // 7
																		0xC9, 0x80, 0xB6, 0xB6, 0x80, 0xC9,      // 8
																		0xCD, 0x84, 0xB6, 0xB6, 0x80, 0xC1,      // 9
																	};

unsigned char _DATA[48] = {
															0xFF, // 0
															0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 6
	                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 12
															0xFF, 0xFF, // 14 
															0xEB,       // 15
															0xFF, 0xFF, // 17
															0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 23
															0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 29
															0xFF, 0xFF, // 31
															0xEB,       // 32
															0xFF, 0xFF, // 34
	                            0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 40
															0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 46
															0xFF // 47
													};

unsigned char code Cot[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void Set_hour(unsigned char _hour)
{
	unsigned char _Hour, _HOUR, i, j;
	_Hour = _hour / 10;
	for(i = 1; i <= 6; i++)
	{
		_DATA[i] = Number[_Hour][i - 1];
	}
	_HOUR = _hour % 10;
	for(j = 7; j <=12; j++)
	{
		_DATA[j] = Number[_HOUR][j - 7];
	}
}

void Set_minute(unsigned char _minute)
{
	unsigned char _Minute, _MINUTE, i, j;
	_Minute = _minute / 10;
	for(i = 18; i <= 23; i++)
	{
		_DATA[i] = Number[_Minute][i - 18];
	}
	_MINUTE = _minute % 10;
	for(j = 24; j <= 29; j++)
	{
		_DATA[j] = Number[_MINUTE][j - 24];
	}
}

void Set_second(unsigned char _second)
{
	unsigned char _Second, _SECOND, i, j;
	_Second = _second / 10;
	for(i = 35; i <= 40; i++)
	{
		_DATA[i] = Number[_Second][i - 35];
	}
	_SECOND = _second % 10;
	for(j = 41; j <= 46; j++)
	{
		_DATA[j] = Number[_SECOND][j - 41];
	}
}
												
// Sleep function 
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


// 74HC595
void Send_Data(unsigned char a)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		DS = a & (0x80 >> i);
		SH_CP = 0;
		SH_CP = 1;
	}
	ST_CP = 0;
	ST_CP = 1;
}


// DS1307

void DS1307_Start()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}

void DS1307_Stop()
{
	SCL = 1;
	SDA = 0;
	SDA = 1;
}

void Write(unsigned char a)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SDA = a & (0x80 >> i);
		SCL = 1;
		SCL = 0;
	}
	SCL = 1;
	SCL = 0;
}

unsigned char Read()
{
	unsigned char _rdata;
	unsigned char _data, i;
	_data = 0x00;
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		_rdata = SDA;
		_data <<= 1;
		_data |= _rdata;
		SCL = 0;
	}
	return _data;
}
void DS1307_Write(unsigned char _address, unsigned char _data)
{
	unsigned char __data; 
	__data = (_data / 10) *16 + (_data % 10);
	DS1307_Start();
	Write(0xD0);
	Write(_address);
	Write(__data);
	DS1307_Stop();
}

unsigned char DS1307_Read(unsigned char _address)
{
		unsigned char _data;
		DS1307_Start();
		Write(0xD0);
		Write(_address);
		DS1307_Start();
		Write(0xD1);
		_data = Read();
		DS1307_Stop();
		_data = (_data / 16) * 10 + (_data % 16);
	return _data;
}



void LED_MATRIX()
{
	unsigned char _second, _minute, _hour;
	unsigned char i;
	// Tao xung o chan INT1 = 1Hz
	DS1307_Write(0x07, 0x10);
	
	// Cho phep ngat theo suon
	IT1 = 1;
	// Cho phep ngat ngoai 1 
	EX1 = 1;
	// Cho phep ngat
	EA = 1;
	
	while(1)
	{
		_second = DS1307_Read(SECOND);
		_minute = DS1307_Read(MINUTE);
		_hour   = DS1307_Read(HOUR);
		Set_hour(_hour);
		Set_minute(_minute);
		Set_second(_second);
		for(i = 0; i < 8; i++)
		{
			Send_Data(_DATA[i]);
			Send_Data(_DATA[i + 8]);
			Send_Data(_DATA[i + 16]);
			Send_Data(_DATA[i + 24]);
			Send_Data(_DATA[i + 32]);
			Send_Data(_DATA[i + 40]);
			LED = Cot[i];
			Sleep_ms(1);
			LED = 0x00;
		}
		PCON |= 0x01;
	}
}

void EX1_ISR(void) interrupt 2
{
}















































