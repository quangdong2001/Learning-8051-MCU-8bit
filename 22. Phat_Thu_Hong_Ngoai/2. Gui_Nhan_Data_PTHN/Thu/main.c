#include <regx52.h>

void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


void Receive()
{
	while(1)
	{
		unsigned char _data, i;
		while(P3_2);
		for(i = 0; i < 8; i++)
		{
			_data <<= 1;
			Sleep_ms(2);
			if(P3_2)
			{
				_data |= 0x01;
			}
			else
			{
				while(P3_2 == 0);
			}
			if(i != 7)
			{
					while(P3_2 == 1);
			}
		}
		P2 = _data;
	}
}



void main()
{
	
	Receive();
	
	
}