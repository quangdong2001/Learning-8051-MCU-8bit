#include "LichVanNien_LedMatrix.h"

#define SEC 0x00
#define MIN 0x01
#define HOUR 0x02
#define DAY 0x03
#define DATE 0x04
#define MONTH 0x05
#define YEAR 0x06

unsigned char code Cot[] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
unsigned char code Number [10][6] = {
															0xC1, 0x80, 0xAE, 0xB6, 0x80, 0xC1,     // 0
															0xFE, 0xEE, 0x80, 0x80, 0xFE, 0xFE,     // 1
															0xDC, 0x98, 0xBA, 0xB6, 0x86, 0xCE,     // 2
															0xDD, 0x9C, 0xB6, 0xB6, 0x80, 0xC9,     // 3
															0xF3, 0xEB, 0xDB, 0x80, 0x80, 0xFB,     // 4
															0x8D, 0x8C, 0xAE, 0xAE, 0xA0, 0xB1,     // 5
															0xC1, 0x80, 0xB6, 0xB6, 0x90, 0xD9,     // 6
															0x9F, 0x9F, 0xB8, 0xA0, 0x87, 0x9F,     // 7
															0xC9, 0x80, 0xB6, 0xB6, 0x80, 0xC9,     // 8
															0xCD, 0x84, 0xB6, 0xB6, 0x80, 0xC1,     // 9
						            };	

unsigned char Data[] = 
						 { 
							 0xFF, 0xFF, 0xFF, 
							 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
							 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 14
							 0xFF, 
							 0xEB,
							 0xFF,
							 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
							 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // 29
							 0xFF,
							 0xEB,
							 0xFF,
							 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
							 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
							 0xFF, 0xFF, 0xFF
					   };
						 
						 
void Convert_Gio_Chuc(unsigned char a)
{
	unsigned char i;
	for(i = 3; i <= 8; i++)
	{
		Data[i] = Number[a][i-3];
	}
}

void Convert_Gio_Donvi(unsigned char a)
{
	unsigned char i;
	for(i = 9; i <= 14; i++)
	{
		Data[i] = Number[a][i-9];
	}
}

void Convert_Phut_Chuc(unsigned char a)
{
	unsigned char i;
	for(i = 18; i <= 23; i++)
	{
		Data[i] = Number[a][i-18];
	}
}

void Convert_Phut_Donvi(unsigned char a)
{
	unsigned char i;
	for(i = 24; i <= 29; i++)
	{
		Data[i] = Number[a][i-24];
	}
}

void Convert_Giay_Chuc(unsigned char a)
{
	unsigned char i;
	for(i = 33; i <= 38; i++)
	{
		Data[i] = Number[a][i-33];
	}
}

void Convert_Giay_Donvi(unsigned char a)
{
	unsigned char i;
	for(i = 39; i <= 44; i++)
	{
		Data[i] = Number[a][i-39];
	}
}

// Ham Sleep_ms

void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
 for(i = 0; i < t; i++)
 {
  for(j = 0; j < 123; j++);
 }
}
// DS1307 

void Start()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}

void Stop()
{
	SCL = 1;
	SDA = 0;
	SDA = 1;
}

void Write(unsigned char _data)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SDA = _data & (0x80  >> i);
		SCL = 1;
		SCL = 0;
	}
	SCL = 1;
	SCL = 0;
}
unsigned char Read()
{
	bit _rdata;
	unsigned char i, _data;
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
void Write_DS1307(unsigned char _address, unsigned char _data)
{
	unsigned char _rdata;
	_rdata = (_data / 10) * 16 + (_data % 10);
	Start();
	Write(0xD0);
	Write(_address);
	Write(_rdata);
	Stop();
}
unsigned char Read_DS1307(unsigned char _address)
{
		unsigned char _data;
		Start();
		Write(0xD0);
		Write(_address);
		Start();
		Write(0xD1);
		_data = Read();
		Stop();
		_data = (_data / 16) * 10 + (_data % 16);
	return _data;
}	
					



// 74HC595
void Send_Data(unsigned char _data)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		DS = _data & (0x80 >> i);
		SH_CP = 0;
		SH_CP = 1;
	}
	ST_CP = 0;
	ST_CP = 1;
}


// Perpose

void Perpose()
{
	unsigned char _second, _minute, _hour, old_second;
	unsigned int i;
	_second = Read_DS1307(0x00);
	_minute = Read_DS1307(0x01);
	_hour = Read_DS1307(0x02);
	old_second = _second;
	while(1)
		{
					Convert_Gio_Chuc(_hour/10);
					Convert_Gio_Donvi(_hour%10);
					Convert_Phut_Chuc(_minute/10);
					Convert_Phut_Donvi(_minute%10);
					Convert_Giay_Chuc(_second/10);
					Convert_Giay_Donvi(_second%10);
			while(old_second == _second)
			{
					for(i = 0; i < 8; i++)
					{
						Send_Data(Data[i+0]);
						Send_Data(Data[i+8]);
						Send_Data(Data[i+16]);
						Send_Data(Data[i+24]);
						Send_Data(Data[i+32]);
						Send_Data(Data[i+40]);
						P0 = Cot[i];
						Sleep_ms(1);
						P0 = 0x00;
					}
					_second = Read_DS1307(0x00);
					_minute = Read_DS1307(0x01);
					_hour = Read_DS1307(0x02);
			}
			old_second = _second;
		}
}





















							
