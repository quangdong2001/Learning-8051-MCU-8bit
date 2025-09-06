#include "D:\8051\20. UART\3. Uart_Virtual_Com\Uart_Virtual_Com.h"
#include <stdio.h>
void main()
{
	Uart_Init();
	
	while(1)
	{
		Uart_Write_Text("Em Chao Anh Dong");
		Uart_Write(13);
		Sleep_ms(1000);
		
	}
}