#include <regx52.h>
#include "D:\8051\The_Media_Lib\Media_Lib.h"

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
	Init_Uart();
	Uart_Write_Text("Em Chao Anh Dong");
	while(1)
	{
	}
}