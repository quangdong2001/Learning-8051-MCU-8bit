#include <regx52.h>
#include <stdio.h>

// Ham dung chuong trinh
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Ham cau hinh chong 
void Uart_Init()
{
	// Chon timer1 che do 2 8bit tu nap lai 
	TMOD &= 0x0F;
	TMOD |= 0x20;
	
	// Con che do truyen thong 1 8bit toc do baud duoc cai boi timer1
	SM0 = 0;
	SM1 = 1;
	
	// Cai dat toc do baud 9600
	TH1 = 0xFD;
	
	// Cho phep nhan du lieu 
  REN = 1;
	
	// Gan TI = 1 de biet rang da san sang gui du lieu tiep theo
	TI = 1;

	// Khoi dong timer 1;
	TR1 = 1;
}

// Gui du lieu tu vi dieu khien ra cho thiet bi ngoai
void Uart_Write(unsigned char _data)
{
	while(TI == 0);
	TI = 0;
	SBUF = _data;
}

// Ham kiem tra xem co du lieu duoc gui tu ben ngoai khong 
unsigned char Uart_Ready()
{
	return RI;
}

// Ham gui du lieu tu thiet bi ngoai vao vi dieu khien 
unsigned char Uart_Read()
{
	RI = 0;
	return SBUF;
}




void main()
{

	Uart_Init();
	while(1)
	{
		printf("Em Chao Anh Dong");
		Sleep_ms(1000);
		putchar(13);
	}
}