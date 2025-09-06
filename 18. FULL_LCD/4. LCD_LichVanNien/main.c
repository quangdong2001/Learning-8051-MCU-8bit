#include <regx52.h>

// define LCD 
#define Data P2
sbit RS = P0^0;
sbit E = P0^1;

// define DS1307
sbit SDA = P1^0;
sbit SCL = P1^1;

#define SEC 0x00
#define MIN 0x01
#define HOUR 0x02
#define DAY 0x03
#define DATE 0x04
#define MONTH 0x05
#define YEAR 0x06

unsigned char * code Day[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};


// FUNCTION LCD 
void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}
// Gui Lenh 
void Send_Cmd(unsigned char a)
{
	RS = 0;
	Data = a; 
	E = 1;
	E = 0;
	if(a <= 0x02)
		Sleep_ms(2);
	else
		Sleep_ms(1);
}
	
// Gui 1 ki tu 
void Send_Data(unsigned char a)
{
	RS = 1;
	Data = a;
	E = 1;
	E = 0;
	Sleep_ms(1);
}

// Gui 1 chuoi ki tu 
void Send_String(unsigned char *str)
{
	unsigned char i = 0;
	while(str[i] != 0)
	{
		Send_Data(str[i]);
		i++;
	}
}

// Gui ki tu ra hang row cot col 
void Send_1(unsigned char row, unsigned char col, unsigned char Data)
{
	unsigned char Locate;
	Locate = (row == 1? 0x80:0xC0) + col - 1;
	Send_Cmd(Locate);
	Send_Data(Data);
	
}


// Gui chuoi ki tu ra hang row cot col 
void Send_2(unsigned char row, unsigned char col, unsigned char* Data)
{
	unsigned char Locate;
	Locate = (row == 1? 0x80:0xC0) + col - 1;
	Send_Cmd(Locate);
	Send_String(Data);

}
void Initialize_LCD()
{
	Sleep_ms(100);
	Send_Cmd(0x30);
	Sleep_ms(5);
	Send_Cmd(0x30);
	Sleep_ms(1);
	Send_Cmd(0x30);
	Send_Cmd(0x38);
	Send_Cmd(0x01);
	Sleep_ms(2);
	Send_Cmd(0x0C);
	Sleep_ms(1);
}



// FUNCTION DS1307
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
	SCL = 1;
}

void Write(unsigned char Data)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SDA = Data & (0x80 >> i);
		SCL = 1;
		SCL = 0;
	}
	SCL = 1;
	SCL = 0;
}

unsigned char Read(void)
{
	bit _rdata;
	unsigned char i, Data;
	Data = 0x00; 
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		_rdata = SDA;
		Data <<= 1;
		Data |= _rdata;
		SCL = 0;
	}
	return Data;
}

void DS1307_Write(unsigned char Address, unsigned char Data)
{
	unsigned char _rdata;
	_rdata = (Data / 10)*16 + (Data % 10);
	Start();
	Write(0xD0);
	Write(Address);
	Write(_rdata);
	Stop();
}

unsigned char DS1307_Read(unsigned char Address)
{
		unsigned char Data;
		Start();
		Write(0xD0);
		Write(Address);
		Start();
		Write(0xD1);
		Data = Read();
		Stop();
		Data = (Data/16)*10 + (Data%16);
	return Data;
}



void main()
{
	
	unsigned char _Second, _Minute, _Hour, Old_Second, _Day, _Date, _Month, _Year;
	Initialize_LCD();
	DS1307_Write(0x00, 0);
	DS1307_Write(0x01, 19);
	DS1307_Write(0x02, 14);
	DS1307_Write(0x03, 1);
	DS1307_Write(0x04, 11);
	DS1307_Write(0x05, 7);
	DS1307_Write(0x06, 21);
	
	while(1)
	{
		_Second = DS1307_Read(SEC);
		_Minute = DS1307_Read(MIN);
		_Hour = DS1307_Read(HOUR);
		_Day = DS1307_Read(DAY);
		_Date = DS1307_Read(DATE);
		_Month = DS1307_Read(MONTH);
		_Year = DS1307_Read(YEAR);
		if(Old_Second != _Second)
			{
				Old_Second = _Second;
				
				Send_2(1, 1, "TIME ");
				Send_1(1, 7, _Hour / 10 + 0x30);
				Send_Data(_Hour % 10 + 0x30);
				Send_Data(':');
				Send_Data(_Minute / 10 + 0x30);
				Send_Data(_Minute % 10 + 0x30);
				Send_Data(':');
				Send_Data(_Second / 10 + 0x30);
				Send_Data(_Second % 10 + 0x30);
				Send_2(2, 1, Day[_Day - 1]);
				Send_String("  ");
				Send_Data((_Date / 10) + 0x30);
				Send_Data((_Date % 10) + 0x30);
				Send_Data('/');
				Send_Data((_Month / 10) + 0x30);
				Send_Data((_Month % 10) + 0x30);
				Send_String("/20");
				Send_Data((_Year / 10) + 0x30);
				Send_Data((_Year % 10) + 0x30);
			}
	}
}