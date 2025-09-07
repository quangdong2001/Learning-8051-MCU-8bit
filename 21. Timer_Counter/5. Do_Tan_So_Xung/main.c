#include <regx52.h>

#define Data P0
sbit RS = P2^0;
sbit E = P2^1;

// Ham dung chuong trinh trong ? milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


// Ham gui lenh ra LCD
void Send_Cmd(unsigned char _code)
{
	RS = 0;
	Data = _code;
	E = 1;
	E = 0;
	if(_code <= 0x02)
		Sleep_ms(2);
	else
		Sleep_ms(1);
}


// Ham khoi tao LCD
void LCD_Init()
{
	Sleep_ms(100); // De cho dien ap tang len toi 5v
	Send_Cmd(0x30);
	Sleep_ms(5);
	Send_Cmd(0x30);
	Sleep_ms(1);
	Send_Cmd(0x30);
	Sleep_ms(1);
	// hien thi 2 dong co chu 5x7
	Send_Cmd(0x38);
	// Xoa du lieu trong DDRAM
	Send_Cmd(0x01);
	// Bat hien thi tat con tro
	Send_Cmd(0x0C);
}



// Ham gui ki tu ra cho LCD 
void Send_Text(unsigned char _text)
{
	RS = 1;
	Data = _text;
	E = 1;
	E = 0;
	Sleep_ms(1);
}

// Ham gui chuoi ki tu ra ban phim 
void Send_Text_Block(unsigned char *_text)
{
	unsigned char i = 0;
	while(_text[i] != 0)
	{
		Send_Text(_text[i]);
		i++;
	}
}

// Gui ki tu ra vi tri xac dinh trong bo nho DDRAM
void Send_Data_Local(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char _local;
	_local = ((row == 1)?0x80 : 0xC0) + col - 1;
	Send_Cmd(_local);
	Send_Text(_data);
}

// Gui chuoi ki tu ra vi tri xac dinh trong LCD 
void Send_Data_Local_Block(unsigned char row, unsigned char col, unsigned char *_data)
{
	unsigned char _local;
	_local = ((row == 1)?0x80 : 0xC0) + col - 1;
	Send_Cmd(_local);
	Send_Text_Block(_data);
}
void main()
{
	unsigned int _data, T, F;
	// thiet lap timer 0 che de 16bit 
	LCD_Init();
	TMOD &= 0xF0;
	TMOD |= 0x09;
	
	Send_Data_Local_Block(1, 1, "T = ");
	Send_Data_Local_Block(2, 1, "F = ");
	
		
	while(1)
	{
		TL0 = 0x00;
		TH0 = 0x00;
		
		while(INT0);
		while(!INT0);
		TR0 = 1;
		while(INT0);
		TR0 = 0;
		
		_data = TH0;
		_data <<= 8;
		_data |= TL0;
		
		T = _data * 2;
		Send_Data_Local(1, 5, T / 10000 + 0x30);
		Send_Text((T % 10000) / 1000 + 0x30);
		Send_Text((T % 1000) / 100 + 0x30);
		Send_Text((T % 100) / 10 + 0x30);
		Send_Text((T % 10) + 0x30);
		
		F = 1000000 / T;
		Send_Data_Local(2, 5, F / 10000 + 0x30);
		Send_Text((F % 10000) / 1000 + 0x30);
		Send_Text((F % 1000) / 100 + 0x30);
		Send_Text((F % 100) / 10 + 0x30);
		Send_Text((F % 10) + 0x30);
	}
	
}