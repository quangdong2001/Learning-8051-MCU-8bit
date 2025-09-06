#ifndef _LICH_VAN_NIEN_LEDMATRIX_H_
#define _LICH_VAN_NIEN_LEDMATRIX_H_

#include <regx52.h>

// Rest of programme int t second 
void Sleep_ms(unsigned int t);

// DS1307

sbit SDA = P1^0;
sbit SCL = P1^1;

void Start();
void Stop();
void Write(unsigned char _data);
unsigned char Read();
void Write_DS1307(unsigned char _address, unsigned char _data);
unsigned char Read_DS1307(unsigned char _address);

// 75Hc595

sbit SH_CP = P3^0;
sbit DS = P3^1;
sbit ST_CP = P3^3;
void Send_Data(unsigned char _data);

// Convert 
void Convert_Gio_Chuc(unsigned char a);
void Convert_Gio_Donvi(unsigned char a);
void Convert_Phut_Chuc(unsigned char a);
void Convert_Phut_Donvi(unsigned char a);
void Convert_Giay_Chuc(unsigned char a);
void Convert_Giay_Donvi(unsigned char a);

// Purpose
void Purpose();
#endif