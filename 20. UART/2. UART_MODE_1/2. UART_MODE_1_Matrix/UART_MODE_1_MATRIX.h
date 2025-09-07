#ifndef _UART_MODE_1_MATRIX_H_
#define _UART_MODE_1_MATRIX_H_
#include <regx52.h>
#define FREQ_OSC 11059200
#define BAUD_RATE 9600

// Ham dung chuong trinh milisecond
void Sleep_ms(unsigned int t);

// Ham khoi tao che do truyen du lieu 
void Init_Uart();

// Ham gui _data tu vi dieu khien ra 
void Uart_Write(unsigned char _data);

// Ham gui chuoi du lieu ra tu vi dieu khien 
void Uart_Write_Text(unsigned char *p);

// Ham kiem tra xem du co duoc gui tu ngoai vao vi dieu khien khong 
unsigned char Uart_Ready();

// Ham lay du lieu tu ngoai vao vi dieu khien 
unsigned char Uart_Read();

// Khai bao cac cong de truyen _data ra 
sbit SHCP = P2^0;
sbit DS = P2^1;
sbit STCP = P2^3;

// Ham gui dulieu cho 74HC595
void Send_Data(unsigned char _data);

// Giap Tiep Che do 1 voi led matrix
void Uart_Mode_1_Matrix();
#endif