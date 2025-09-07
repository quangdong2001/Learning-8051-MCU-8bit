#include "Uart_Virtual_Com.h"

// Ham dung chuong trinh trong ? milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i ,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Ham cau hinh cho che do truyen 
void Uart_Init()
{
	// Chon time1 che do 2 8bit tu nap lai 
	TMOD &= 0x0F;
	TMOD |= 0x20;
	
	// Chon che do 1 truyen 8 bit toc do baud duoc cai boi timer1	
	SM0 = 0;
	SM1 = 1;
	
	// Chon che do nhan du lieu bang cac dat bit REN thuoc thanh ghi SCON len muc 1
	REN = 1;
	// Nap gia tri cho TH1 de cai dat toc do baud 9600
	TH1 = 0xFD;
	
	// Dat co TI = 1 de thong bao rang da san sang gui du lieu 
	TI = 1;
	
	// Khoi dong bo diem time1
	TR1 = 1;
}

// ham gui du lieu tu vi dieu khien ra cho thiet bi ngoai
void Uart_Write(unsigned char _data)
{
	while(TI == 0);
	TI = 0;
	SBUF = _data;
}

// ham gui chuoi du lieu ra cho vi dieu khien 
void Uart_Write_Text(unsigned char *_data)
{
	unsigned char i = 0;
	while(_data[i] != 0)
	{
		Uart_Write(_data[i]);
		i++;
	}
}
unsigned char Uart_Ready()
{
	return RI;
}

unsigned char Uart_Read()
{
	RI = 0;
	return SBUF;
}






