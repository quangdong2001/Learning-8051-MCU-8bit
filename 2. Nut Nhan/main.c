#include "..\Lib\Library.h"
#include "..\Nut Nhan\Button.h"

void main()
{
	LED_RED = 0;

	while(1)
	{
		if(ON == 0)
		{
			LED_RED = 1;
		}
		if(OFF == 0)
		{
			LED_RED = 0;
		}
		
	}
}