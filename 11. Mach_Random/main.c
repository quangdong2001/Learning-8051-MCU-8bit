#include <regx52.h>
unsigned char code LED[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

#define LED1 P2
sbit Button = P1^0;
void main()
{
	unsigned char i = 0;
	while(1)
	{
		while(Button == 0)
		{
			i++;
		}	
		LED1 = LED[i%5+1];
	}
}