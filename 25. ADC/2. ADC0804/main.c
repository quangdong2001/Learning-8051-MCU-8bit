#include <regx52.h>

// Ham dung chuong trinh trong ?milisecond 
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Dinh nghia cac bit data cho LCD
#define Data P0
sbit RS = P2^4;
sbit E =  P2^5;
//..............// HAM GIA TIEP VOI LCD //....................
// Gui lenh ra cho LCD
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

// Gui du lieu ra cho LCD
void Send_Data(unsigned char _data)
{
	RS = 1;
	Data = _data;
	E = 0;
	E = 1;
	Sleep_ms(1);
}

// Gui chuoi du lieu ra LCD
void Send_Data_Block(unsigned char *p)
{
	unsigned char i = 0;
	while(p[i] != 0)
	{
		Send_Data(p[i]);
		i++;
	}
}

// Gui du lieu ra vi tri xac dinh trong LCD
void Send_Data_Locate(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char locate;
	locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(locate);
	Send_Data(_data);
}	

// Gui chuoi du lieu ra vi tri xac dinh trong LCD 
void Send_Data_Block_Locate(unsigned char row, unsigned char col, unsigned char *p)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data_Block(p);
}

// Ham khoi tao LCD

void LCD_Init()
{
	Sleep_ms(100); // Cho khoang 100ms de cho dien ap rise to 4,5;
	Send_Cmp(0x30);
	Sleep_ms(5);
	Send_Cmp(0x30);
	Sleep_ms(1);
	Send_Cmp(0x30);
	
	Send_Cmp(0x00); // Xoa toan bo du lieu trong thanh ghi DDRAM
	Send_Cmp(0x0C); // Hien thi LCD, tat con tro
	Send_Cmp(0x38); // Chon che do 8bit 2 hang co chu 5x7
}



//............Dinh nghia cac bit cho ADC0804.......................//

sbit ADC0804_CS = P2^0;
sbit ADC0804_RD = P2^1;
sbit ADC0804_WR = P2^2;
sbit ADC0804_INTR = P2^3;

unsigned char Read_ADC0804()
{
	unsigned char _data;
	// chon che do chip
	ADC0804_CS = 0;
	// Tao xung chuyen doi
	ADC0804_WR = 0;
	ADC0804_WR = 1;
	// Doi chuyen doi xong 
	while(ADC0804_INTR);
	ADC0804_RD = 0;
	_data = P3;
	ADC0804_RD = 1;
	return _data;

}



void main()
{
	unsigned int _data, _value;
	LCD_Init();
	Send_Data_Block_Locate(1,1,"Voltage = ");
	while(1)
	{
		_data = Read_ADC0804();
		_value = _data * (float)5*100/256;
		Send_Data_Locate(1,11,_value / 100 + 0x30);
		Send_Data('.');
		Send_Data((_value % 100) / 10 + 0x30);
		Send_Data(_value % 10 + 0x30);
	}	
}
