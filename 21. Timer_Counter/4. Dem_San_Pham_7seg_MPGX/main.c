#include <regx52.h>

unsigned char code Data[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};
unsigned char code Cot[]  = {0x01, 0x02, 0x04, 0x8, 0x10};


void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void Display(unsigned int _data)
{
	unsigned char _chuc_nghin, _nghin, _tram, _chuc, _don_vi;
	_chuc_nghin = _data / 10000;
	_nghin = (_data % 10000) / 1000;
	_tram = (_data % 1000) / 100;
	_chuc = (_data % 100) / 10;
	_don_vi = _data % 10;
	
	P0 = Data[_chuc_nghin];
	P2 = Cot[0];
	Sleep_ms(1);
	P2 = 0x00;
	
	P0 = Data[_nghin];
	P2 = Cot[1];
	Sleep_ms(1);
	P2 = 0x00;
	
	P0 = Data[_tram];
	P2 = Cot[2];
	Sleep_ms(1);
	P2 = 0x00;
	
	P0 = Data[_chuc];
	P2 = Cot[3];
	Sleep_ms(1);
	P2 = 0x00;
	
	P0 = Data[_don_vi];
	P2 = Cot[4];
	Sleep_ms(1);
	P2 = 0x00;
	
}



	
void main()
{
	unsigned int _data;
	unsigned char _low, _high;
	
	// Cau hinh cho Timer;
	TMOD &= 0xF0;
	TMOD |= 0x05;
	TL0 = 0x00;
	TH0 = 0x00;
	
	TR0 = 1;
	while(1)
	{
			do
			{
				_high = TH0;
				_low = TL0;
			} while(_high != TH0);
			_data = _high;
			_data <<= 8;
			_data |= _low;
			Display(_data);
	}
	
	
	
	
}