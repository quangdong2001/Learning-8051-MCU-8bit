#include <regx52.h>

// Ham dung chuong trinh trong ? milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i , j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

//........................................Cac Function cho LCD...........................................//

sbit RS = P2^4;
sbit E =  P2^5;
#define Data P0

// Ham gui lenh
void Send_Cmp(unsigned char _struction)
{
	RS = 0;
	Data = _struction;
	E = 0;
	E = 1;
	if(_struction <= 0x03)
	{
		Sleep_ms(2);
	}
	else
		Sleep_ms(1);
}

// Ham gui du lieu
void Send_Data(unsigned char _data)
{
	RS = 1;
	Data = _data;
	E = 0;
	E = 1;
	Sleep_ms(1);
}

// Ham gui chuoi ra LCD
void Send_Data_Block(unsigned char *p)
{
	unsigned char i = 0;
	while(p[i] != 0)
	{
    Send_Data(p[i]);
		i++;
	}
}

// Ham gui ki tu ra vi tri xac dinh trong lCD;
void Send_Data_Locate(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data(_data);
}

// Ham gui chuoi ki tu ra vi tri xac dinh trong LCD;
void Send_Data_Block_Locate(unsigned char row, unsigned char col, unsigned char *_data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data_Block(_data);
}

// Ham khoi tao LCD 
void LCD_Init()
{
	Sleep_ms(100); // cho cho den khi dien ap LCD tang toi 4,5v
	Send_Cmp(0x30);
	Sleep_ms(5);
	Send_Cmp(0x30);  // Lenh yeu cau tu nha san xuat;
	Sleep_ms(1);
	Send_Cmp(0x30);
	
	Send_Cmp(0x00); // Xoa toan bo noi dung trong thanh ghi DDRAM
	Send_Cmp(0x0C); // Hien thi LCD tat hien thi con tro
	Send_Cmp(0x38); // Chon che do 8bit hien thi 2 hang co chu 5x7
}


//................................................CAC FUNCTION CUA DS1307........................................//

sbit SCL = P1^1;
sbit SDA = P1^0;

#define Second 0x00
#define Minute 0x01
#define Hour   0x02
#define Day    0x03
#define Date   0x04
#define Month  0x05
#define Year   0x06

// DS1307 giao tiep voi vi dieu khien at89s52 bang chuan giao tiep I2C //

// Ham bat dau giao tiêp I2C
void Start_I2C()
{
	SCL = 1;
	SDA = 1;
	SDA = 0;
	SCL = 0;
}

// Ham dung giao tiep I2C
void Stop_I2C()
{
	SCL = 1;
	SDA = 0;
	SDA = 1;
}

// Gui du lieu vao dia chi
void Write_I2C(unsigned char _data)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SDA = _data & (0x80 >> i);
		SCL = 1;
		SCL = 0;
	}
	SCL = 1;
	SCL = 0;
}

// Doc du lieu
unsigned char Read_I2C()
{
	bit _flag;
	unsigned char _data = 0x00;
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		SCL = 1;
		_flag = SDA;
		_data <<= 1;
		_data |= _flag;
		SCL = 0;
	}
	return _data;
}


// Ham gui du lieu vao dia chi cua DS1307

void Write_DS1307(unsigned char _address, unsigned char _data)
{
	unsigned char data_convert;
	data_convert = (_data / 10) * 16 + (_data % 10);
	Start_I2C();
	Write_I2C(0xD0);
	Write_I2C(_address);
	Write_I2C(data_convert);
	Stop_I2C();
}

// Ham doc du lieu tu DS1307
unsigned char Read_DS1307(unsigned char _address)
{
	unsigned char _data, data_convert;
	Start_I2C();
	Write_I2C(0xD0);
	Write_I2C(_address);
	Start_I2C();
	Write_I2C(0xD1);
	_data = Read_I2C();
	Stop_I2C();
	data_convert = (_data / 16) * 10 + (_data % 16);
	return data_convert;
}


//.....................................................CAC FUNCTION CUA ADC0804..................................................................//

sbit ADC0804_CS = P2^0;
sbit ADC0804_RD = P2^1;
sbit ADC0804_WR = P2^2;
sbit ADC0804_INTR = P2^3;

unsigned char Read_ADC0804()
{
	
	unsigned int _data;
	// Chon chip
	ADC0804_CS = 0;
	// Tao xung convert
	ADC0804_WR = 0;
	ADC0804_WR = 1;
	// Cho cho den khi convert xong
	while(ADC0804_INTR);
	
	ADC0804_RD = 0;
	_data = P3;
	ADC0804_RD = 1;
	return _data;
	
}





void main()
{
	unsigned char _second, _minute, _hour;
	unsigned int flag;
	unsigned char _temperature;
	LCD_Init();
	Send_Data_Block_Locate(1,1,"TIME : ");
	Send_Data_Block_Locate(2,1,"TEMPERATURE : ");
	while(1)
	{
		_second = Read_DS1307(Second);
		_minute = Read_DS1307(Minute);
		_hour   = Read_DS1307(Hour);
		Send_Data_Locate(1,8,_hour / 10 + 0x30);
		Send_Data(_hour % 10 + 0x30);
		Send_Data(':');
		Send_Data(_minute / 10 + 0x30);
		Send_Data(_minute % 10 + 0x30);
		Send_Data(':');
		Send_Data(_second / 10 + 0x30);
		Send_Data(_second % 10 + 0x30);
		
		flag = Read_ADC0804();
		_temperature = (flag * 1.961) + 0.5;
		Send_Data_Locate(2,15,_temperature / 10 + 0x30);
		Send_Data(_temperature % 10 + 0x30);
	}
	
}