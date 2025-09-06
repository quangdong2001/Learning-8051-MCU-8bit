#include <regx52.h>

sbit RS = P0^0;
sbit E = P0^1;

#define _Data P2
#define SECOND 0x00
#define MINUTE 0x01
#define HOUR   0x02
#define DAY    0x03
#define DATE   0x04
#define MONTH  0x05
#define YEAR   0x06

sbit SDA = P1^0;
sbit SCL = P1^1;

unsigned char *code Data[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

// Sleep function 
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


// ___________________LCD function__________________ //
// CMD funciton 
void Send_Cmd(unsigned char a)
{
	RS = 0;
	_Data = a;
	E = 1; 
	E = 0;
	if(a <= 0x02)
	{
		Sleep_ms(2);
	}
	else
		Sleep_ms(1);
}

// Data function 
void Send_Data(unsigned char a)
{
	RS = 1;
	_Data = a;
	E = 1;
	E = 0;
	Sleep_ms(1);
}

// Send string data function 
void Send_String(unsigned char *p)
{
	unsigned char i = 0;
	while(p[i] != 0)
	{
		Send_Data(p[i]);
		i++;
	}
}

// Send _data ra vi tri bat ki
void Send_Data_Locate(unsigned char Row, unsigned char Col, unsigned char _data)
{
	unsigned char _locate;
	_locate = (Row == 1 ? 0x80 : 0xC0) + Col - 1;
	Send_Cmd(_locate);
	Send_Data(_data);
}

// Send string _data ra vi tri bat ki 
void Send_String_Locate(unsigned char Row, unsigned char Col, unsigned char *_data)
{
	unsigned char _locate;
	_locate = (Row == 1 ? 0x80 : 0xC0 ) + Col - 1;
	Send_Cmd(_locate);
	Send_String(_data);
}

// LCD initialize
void LCD_Initialize()
{
	// Dung khoang 100 ms de dien ap rise toi 4,5V 
	Sleep_ms(100);
	Send_Cmd(0x30);
	Sleep_ms(5);
	Send_Cmd(0x30);
	Sleep_ms(1);
	Send_Cmd(0x30);
	// Chon hien thi man hinh 2 dong co chu 5*7
	Send_Cmd(0x38);
	// Xoa man hinh 
	Send_Cmd(0x01);
	// Bat hien thi va tat con tro 
	Send_Cmd(0x0C);
}


/// ______________________DS1307 Function__________________________///


// Start function 

void DS1307_Start()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}


// Stop function 
void DS1307_Stop()
{
	SCL = 1;
	SDA = 0;
	SDA = 1;
}

// Write function
void Write(unsigned char a)
{
	unsigned char i = 0;
	for(i = 0; i < 8; i++)
	{
		SDA = a &( 0x80 >> i );
		SCL = 1;
		SCL = 0;
	}
	SCL = 1;
	SCL = 0;
}

// Read function 
unsigned char Read(void)
{
	bit _rdata;
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

// DS1307 Write function 
void DS1307_Write(unsigned char _address, unsigned char _data)
{
	unsigned char __data;
	__data = (_data / 10) * 16 + (_data % 10);
	DS1307_Start();
	Write(0xD0);
	Write(_address);
	Write(__data);
	DS1307_Stop();
}

// DS1307 READ function 
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

// Main function 

void LCD_LichVanNien_Interrupt()
{
	unsigned char _second, _minute, _hour, _day, _date, _month, _year;
	LCD_Initialize();
	DS1307_Write(0x07, 0x10);
	
	// Ngat theo canh xuong
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
		_day    = DS1307_Read(DAY);
		_date   = DS1307_Read(DATE);
		_month  = DS1307_Read(MONTH);
		_year  = DS1307_Read(YEAR);
		
		// show clock time
		Send_Data_Locate(1, 5, _hour / 10 + 0x30);
		Send_Data(_hour % 10 + 0x30);
		Send_Data(':');
		Send_Data(_minute / 10 + 0x30);
		Send_Data(_minute % 10 + 0x30);
		Send_Data(':');
		Send_Data(_second / 10 + 0x30);
		Send_Data(_second % 10 + 0x30);
		// show day date time
		
		Send_String_Locate(2,2,Data[_day - 1]);
		Send_Data(' ');
		Send_Data(_date / 10 + 0x30);
		Send_Data(_date % 10 + 0x30);
		Send_Data('/');
		Send_Data(_month / 10 + 0x30);
		Send_Data(_month % 10 + 0x30);
		Send_Data('/');
		Send_String("20");
		Send_Data(_year / 10 + 0x30);
		Send_Data(_year % 10 + 0x30);
		
		PCON |= 0x01;
		
	}
}

void EX1_ISR(void) interrupt 2
{
}

void main()
{
	LCD_LichVanNien_Interrupt();
}