#include <regx52.h>

#define Control P2

void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void main()
{	
	Control = 0;
	while(1)
	{
		while(Control != 255)
		{
			Control++;
			Sleep_ms(10);
		}
		while(Control != 0)
		{
			Control--;
			Sleep_ms(10);
		}
	}	
}