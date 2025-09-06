#include <regx52.h>


unsigned char Read(unsigned char a)
{
	bit _rbit;
	unsigned char i;
	unsigned char data = 0x00;
	for(i = 0; i < 8; i++)
	{
		_rbit = a;
		data <<= 1;
		data = data | _rbit;
	}
	return data;
}

//#define RS P0_0
//#define E P0_1
//#define Data P2


//void Sleep_ms(unsigned int t)
//{
//	unsigned int i,j;
//	for(i = 0; i < t; i++)
//	{
//		for(j = 0; j < 123; j++);
//	}
//}

//void Send_cmd(unsigned char a)
//{
//	RS = 0;
//	Data = a;
//	E = 0;
//	E = 1;
//	if(a <= 0x02)
//		Sleep_ms(2);
//	else
//		Sleep_ms(1);
//}

//void Send_Data(unsigned char b)
//{
//	RS = 1;
//	Data = b;
//	E = 0;
//	E = 1;
//	Sleep_ms(1);
//}

//void Send_String(unsigned char *p)
//{
//	unsigned char i = 0;
//	while(p[i] != 0)
//	{
//		Send_Data(p[i]);
//		i++;
//	}
//}

//void Initialize()
//{
//	Sleep_ms(100);
//	Send_cmd(0x30);
//	Sleep_ms(5);
//	Send_cmd(0x30);
//	Sleep_ms(1);
//	Send_cmd(0x30);
//	Send_cmd(0x38);
//	Send_cmd(0x01);
//	Sleep_ms(2);
//	Send_cmd(0x0C);
//	Sleep_ms(1);
//}


//void Send_Any(unsigned char Row, unsigned char Col, unsigned char Data)
//{
//	unsigned char a;
//	a = (Row == 1 ? 0x80:0xC0) + Col - 1;
//	Send_cmd(a);
//	Send_Data(Data);
//}

//void Count()
//{
//	unsigned char i;
//	for(i = 0; i <= 100; i++)
//	{
//		Send_Data(i);
//		Sleep_ms(200);
//	}
//}

void main()
{
//	Initialize();
//	Send_Data(100);
//	Sleep_ms(1000);
//	while(1)
//	{
//		Count();
//	}
	
	unsigned char a = Read(0x12);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}