#include <regx52.h>

#define DATA P3

sbit RS = P2^0;
sbit E  = P2^2;

void Sleep_ms(unsigned int t)
{
	unsigned int i,j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void Send_Lenh(unsigned char a)
{
	RS = 0;
	DATA = a;
	E = 0;
	E = 1;
	if(a <= 0x02)
		Sleep_ms(2);
	else
		Sleep_ms(1);
}


void Send_Kitu_8bit(char a)
{
	RS = 1l;
	DATA = a;
	E = 0;
	E = 1;
	Sleep_ms(1);
}



void Send_8bit(char *p)
{
	unsigned char i = 0;
	while(p[i] != 0)
	{
		Send_Kitu_8bit(p[i]);
		i++;
	}
}

void Beginning()
{
	Send_Lenh(0x30);
	Sleep_ms(5);
	Send_Lenh(0x30);
	Sleep_ms(1);
	Send_Lenh(0x30);
	
	Send_Lenh(0x38);
	
	Send_Lenh(0x01);
	Send_Lenh(0x0C);
}


void main()
{
	Beginning();
	Send_8bit("Hello World");
	while(1)
	{
	}
	
}