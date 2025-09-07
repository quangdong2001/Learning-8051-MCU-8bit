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

// Khai bao cac bit cua LCD
#define Data P0
sbit RS = P2^0;
sbit E = P2^1;
//...............................................................CAC HAM CUA LCD................................................................//
// Ham gui lenh ra cho LCD
void Send_Cmp(unsigned char _struction)
{
	RS = 0;
	Data = _struction;
	E = 0;
	E = 1;
	if( _struction <= 0x03)
	{
		Sleep_ms(2);
	}
	else
		Sleep_ms(1);
}
// Ham gui ki tu ra cho LCD
void Send_Data(unsigned char _data)
{
	RS = 1;
	Data = _data;
	E = 0; 
	E = 1;
	Sleep_ms(1);
}

// Ham gui chuoi ki tu ra cho LCD
void Send_Data_Block(unsigned char *_data)
{
	unsigned char i = 0;
	while(_data[i] != 0)
	{
		Send_Data(_data[i]);
		i++;
	}
}

// Ham gui ki tu ra vi tri xac dinh trong LCD 
void Send_Data_Locate(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data(_data);
}

// Ham gui chuoi ki tu ra vi tri xac dinh trong lCD
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
	Sleep_ms(100);    // doi khoang 100ms de cho dien ap tang toi 4,5V;
	Send_Cmp(0x30);
	Sleep_ms(5);
	Send_Cmp(0x30);
	Sleep_ms(1);
	Send_Cmp(0x30);
	
	Send_Cmp(0x00); // Xoa toan bo du lieu trong bo nho DDRAM
	Send_Cmp(0x0C); // Hien thi LCD tat con tro;
	Send_Cmp(0x38); // Chon che do 8bit, hien thi 2 hang, co chu 5x7;
	
}



//..................................................................HAM XU LI CUA ADC0808........................................................//

//Khai bao pin of ADC0808
sbit ADC0808_ADD_A = P1^0;
sbit ADC0808_ADD_B = P1^1;
sbit ADC0808_ADD_C = P1^2;
sbit ADC0808_ALE   = P1^3;
sbit ADC0808_START = P1^4;
sbit ADC0808_EOC   = P1^5;
sbit ADC0808_OE    = P1^6;

// Ham khoi tao ADC0808;
void ADC0808_Init()
{
	ADC0808_START = 0;
	ADC0808_ALE   = 0;
	ADC0808_OE    = 0;
}


// Ham convert du lieu tu ADC0808

unsigned char ADC0808_Read(unsigned char _address)
{
	// khai bao bien de luu tru du lieu
	unsigned char _data;
	// Chon dia chi de convert;
	ADC0808_ADD_A = _address & 0x01;
	ADC0808_ADD_B = _address & 0x02;
	ADC0808_ADD_C = _address & 0x04;
		
	// Tao xung bat dau cung nhu chot du lieu 
	ADC0808_ALE = 1;
	ADC0808_START = 1;
	ADC0808_ALE = 0;
	ADC0808_START = 0;
	
	// doi cho den khi nao du lieu de duoc convert;
	while(ADC0808_EOC);
	while(!ADC0808_EOC);
	
	// Dua chan cho phep len muc cao, lay du lieu xong se dau xuong muc thap;
	ADC0808_OE = 1;
	_data = P3;
	ADC0808_OE = 0;
	return _data;
}



void main()
{
	
	unsigned value;
	LCD_Init();
	ADC0808_Init();
	Send_Data_Block_Locate(1,1,"Voltage = ");
	while(1)
	{
		value = ADC0808_Read(0) * (float)5*100/256;
		Send_Data_Locate(1,11,value/100 + 0x30);
		Send_Data('.');
		Send_Data((value % 100) / 10 + 0x30);
		Send_Data(value % 10 + 0x30);
	}
}