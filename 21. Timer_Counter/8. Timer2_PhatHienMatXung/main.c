#include <regx52.h>

// Dat ten cho LCD 

sbit RS = P0^0;
sbit E = P0^1;

#define Data P2 

// Ham dung chuong trinh trong ? milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Gui lenh ra cho LCD
void LCD_Cmp(unsigned char _instruct)
{
	RS = 0;
	Data = _instruct;
	E = 1;
	E = 0;
	if(_instruct <= 0x03)
		Sleep_ms(2);
	else
		Sleep_ms(1);
}

void LCD_Text(unsigned char _data)
{
	RS = 1;
	Data = _data;
	E = 1;
	E = 0;
	Sleep_ms(1);
}


void LCD_Text_Block(unsigned char *_data)
{
	unsigned char i = 0;
	while(_data[i] != 0)
	{
		LCD_Text(_data[i]);
		i++;
	}
}


// Ham Khoi tao LCD
void LCD_Init()
{
	Sleep_ms(100); // De dien ap tang len 5v
	LCD_Cmp(0x30);
	Sleep_ms(5);
	LCD_Cmp(0x30);
	Sleep_ms(1);
	LCD_Cmp(0x30);
	LCD_Cmp(0x01);
	LCD_Cmp(0x0C);
	LCD_Cmp(0x38);
}

// Gui du lieu ra vi tri xac dinh 

void LCD_Locate(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	LCD_Cmp(_locate);
	LCD_Text(_data);
}

// Gui chuoi du lieu ra vi tri xac dinh 

void LCD_Locate_Block(unsigned char row, unsigned char col, unsigned char *_data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	LCD_Cmp(_locate);
	LCD_Text_Block(_data);
}


void main()
{
	
	LCD_Init();
	T2MOD = 0x00;
	T2CON = 0x08;
	
	
	RCAP2H = 0x3C;
	RCAP2L = 0xB0;
	
	ET2 = 1;
	EA = 1;
	
	
	while(1)
	{
	}
}

void Ngat_Timer2(void) interrupt 5
{
	if(TF2)
	{
		TR2 = 0;
		LCD_Locate_Block(1, 1, "Information");
		LCD_Locate_Block(2, 1, "KHONG CO XUNG ");
		TF2 = 0;
	}
	else
	{
		TR2 = 1;
		LCD_Locate_Block(1, 1, "Information");
		LCD_Locate_Block(2, 1, "XUAT HIEN XUNG");
		EXF2 = 0;
	}
}