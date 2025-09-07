#include <regx52.h>

// Ham dung chuong trinh trong ?milisecond 
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

//...............................................CAC FUNCTION OF LCD................................................//
sbit RS = P2^0;
sbit E = P2^1;
#define Data P0

// Ham gui lenh ra cho LCD
void Send_Cmp(unsigned char _struction)
{
	RS = 0;
	Data = _struction;
	E = 0;
	E = 1;
	if(_struction <= 0x03)
	{
		Sleep_ms(2);
	}
	else 
		Sleep_ms(1);
}

// Ham gui ki tu ra cho LCD 
void Send_Data(unsigned char _data)
{
	RS = 1;
	Data = _data;
	E = 0;
	E = 1;
	Sleep_ms(1);
}

// Ham gui chuoi ki tu ra cho LCD 
void Send_Data_Block(unsigned char *_data)
{
	unsigned char i = 0;
	while(_data[i] != 0)
	{
		Send_Data(_data[i]);
		i++;
	}
}

// Ham gui ki tu ra vi tri xac dinh trong LCD
void Send_Data_Locate(unsigned char row, unsigned char col, unsigned char _data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data(_data);
}

// Ham gui chuoi ki tu ra vi tri xac dinh cua LCD
void Send_Data_Block_Locate(unsigned char row, unsigned char col, unsigned char *_data)
{
	unsigned char _locate;
	_locate = ((row == 1)? 0x80:0xC0) + col - 1;
	Send_Cmp(_locate);
	Send_Data_Block(_data);
}

// Lenh khoi tao LCD
void LCD_Init()
{
	Sleep_ms(100); // Delay in order to wait voltage rise to 4,5V
	Send_Cmp(0x30);
	Sleep_ms(5);
	Send_Cmp(0x30);
	Sleep_ms(1);
	Send_Cmp(0x30);
	
	Send_Cmp(0x00); // Delete all data in DDRAM Registors
	Send_Cmp(0x0C); // Display LCD and Delete display pointer
	Send_Cmp(0x38); // Communicate 8bit, display 2 line and 5x7 font 
}


//............................................FUNCTIONS OF ADC0808...............................................//

sbit ADC0808_ADD_A = P2^4;
sbit ADC0808_ADD_B = P2^5;
sbit ADC0808_ADD_C = P2^6;
sbit ADC0808_ALE = P2^7;
sbit ADC0808_START = P1^0; 
sbit ADC0808_EOC = P1^1;
sbit ADC0808_OE = P1^2;

// Function initialize ADC0808;
void ADC0808_Init()
{
	ADC0808_START = 0;
	ADC0808_ALE = 0;
	ADC0808_OE = 0;
}

// Function converts _data into voltage from ADC0808
unsigned int ADC0808_Read(unsigned char _address)  // address is gate that need convert;
{
	unsigned int _data;
	// the first, we need choose gate to convert;
	ADC0808_ADD_A = _address & (0x01);
	ADC0808_ADD_B = _address & (0x02);
	ADC0808_ADD_C = _address & (0x04);
	
	// Initialize fisrt and Ale address
	ADC0808_ALE = 1;
	ADC0808_START = 1;
	ADC0808_ALE = 0;
	ADC0808_START = 0;
	
	// Wait in order to convert process complete
	while(ADC0808_EOC);
	while(!ADC0808_EOC);
	
	// Read data that converted from Port 3
	ADC0808_OE = 1;
	_data = P3;
	ADC0808_OE = 0;
	return _data;
}



void main()
{
	unsigned char value;
	unsigned int flag;
	LCD_Init();
	Send_Data_Block_Locate(1,1,"Temperature : ");
	while(1)
	{
		ADC0808_Init();
		flag = ADC0808_Read(0x00);
		value = (flag * 0.391) + 0,5;
		Send_Data_Locate(1,15,value / 10 + 0x30);
		Send_Data(value % 10 + 0x30);
	}
	

	
	
	
	
}