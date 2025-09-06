#include <regx52.h>
sbit SH_CP = P2^0;
sbit DS = P2^1;
sbit ST_CP = P2^3;

void Send_Data(unsigned char a)
{
	unsigned char i;
	for(i = 0; i < 8; i++)
	{
		DS = a & (0x80 >> i);
		SH_CP = 0;
		SH_CP = 1;
	}
	ST_CP = 0;
	ST_CP = 1;
}
void main()
{
	while(1)
	{
		Send_Data(0x35);
	}
}
