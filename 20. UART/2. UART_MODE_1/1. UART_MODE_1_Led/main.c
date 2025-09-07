#include <regx52.h>

// Ham dung thoi gian 
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

// Thiet Lap Modul truyen du lieu 
void Init_Mode1()
{
	// Chon Timer 1 Che do 8 bit tu dong nap lai 
	TMOD = TMOD & 0x0F;
	TMOD = TMOD | 0x20;
	// Chon che do 1 
	SM0 = 0;
	SM1 = 1;
	// Nhap Thanh Ghi TH1
	TH1 = 0xFD; // 9600  Baud
	TI = 1;
	REN = 1;   // Cho phep nhan
	TR1 = 1;   // Khoi Dong Bo dem 
}

// Gui du lieu tu VDK ra ngoai 
void Write(unsigned char a)
{
	while(TI == 0);
	TI = 0;
	SBUF = a;
}

// Kiem tra xem du lieu co duoc gui tu ben ngoai vao khong;
unsigned char Uart_Data_Ready()
{
	return RI;
}

// Doc du lieu khi tin hieu ngoai gui vao VDK
unsigned char Read()
{
	while(RI == 0);
	RI = 0;
	return SBUF;
}


void main()
{
//  unsigned int i;
	P0 = 0x00;
	Init_Mode1();
//  Gui ki tu tu` a den z 
//	for(i = 97; i <= 122; i++)
//	{
//		Write(i);
//	}
	

	while(1)
	{
		if(Uart_Data_Ready() == 1)
		{
			P0 = Read();
		}
	}
}












