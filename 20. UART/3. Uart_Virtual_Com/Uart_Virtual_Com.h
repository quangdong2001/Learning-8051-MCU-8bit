#ifndef _UART_VIRTUAL_COM_H_
#define _UART_VIRTUAL_COM_H_
#include <regx52.h>

void Sleep_ms(unsigned int t);
void Uart_Init();
void Uart_Write(unsigned char _data);
void Uart_Write_Text(unsigned char *_data);
unsigned char Uart_Ready();
unsigned char Uart_Read();

#endif