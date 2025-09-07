#include <regx52.h>

// Chan data cua LCD
#define Data P3
sbit RS = P2^1;
sbit E = P2^2;

// Ham dung chuong trinh trong milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Cac function cua LCD // 

// Ham gui lenh ra LCD

void Send_Cmp(unsigned char _struction)
{
	RS = 0;
	Data = _struction;
	E = 0;
	E = 1;
	if(_struction <= 0x03)
		Sleep_ms(2);
	else
		Sleep_ms(1);
}

// Ham gui du lieu ra LCD 
void Send_Data(unsigned char _data)
{
	RS = 1;
	Data = _data;
	E = 0;
	E = 1;
	Sleep_ms(1);
}

// Ham gui chuoi ki tu ra LCD 
void Send_Data_Block(unsigned char *ptr)
{
	unsigned char i = 0;
	while(ptr[i] != 0)
	{
	  Send_Data(ptr[i]);
		i++;
	}
}

// ham ghi ki tu ra vi tri xac dinh 
void Send_Data_Locate(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data(_data);
}

// ham gui chuoi ki tu ra vi tri xac dinh cua LCD
void Send_Data_Block_Locate(unsigned char row, unsigned char col, unsigned char *p)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;  
	Send_Cmp(_locate);
	Send_Data_Block(p);
}


// Ham khoi tao LCD 
void LCD_Initialize()
{
	Sleep_ms(100); // Dung chuong trinh trong khoang 100ms de cho dien ap cap cho LCD rise to 2,5V;
	Send_Cmp(0x30);
	Sleep_ms(5);
	Send_Cmp(0x30);   // Lenh gui theo yeu cau cua nha san xuat
	Sleep_ms(1);
	Send_Cmp(0x30);
	Send_Cmp(0x38); // Chon che do 8bit, 2 dong co chu 5x7
	Send_Cmp(0x00); // Xoa toan bo du lieu trong thanh ghi DDRAM
	Send_Cmp(0x0C);
}

void main()
{
	unsigned int _data;
	unsigned char value;
	unsigned int flag = 255;
	LCD_Initialize();
	Send_Data_Block_Locate(1,1,"Voltage = ");
	while(1)
	{
		P0 = flag;
		if(P2_0 == 0)
		{
			_data = P0;
			value = _data * (float)5*100/255;
			Send_Data_Locate(1,11,value/100 + 0x30);
			Send_Data('.');
			Send_Data((value%100) / 10 + 0x30);
			Send_Data(value % 10 );
			// P0 = 0x00;
		}
		else
		{
			flag--;
			if(flag == 0)
			{
				flag = 255;
			}
		}
	}
}