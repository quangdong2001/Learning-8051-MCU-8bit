#include <regx52.h>

void Tao_Tre_Timer(unsigned int t)
{
	do
	{
		// Nap gia tri cho thanh ghi de tao do tro 1ms
		// tan so bo dinh thoi dua vao tan so thach anh
		// trong 8051 co bo chia 12 nen tan so bo dem = 1Mhz ==>> Chu ki cua bo dinh thoi la 1us
		// Gia tri can nap = 65536 - (Thoi gian can tre / 1us)
		// 1ms ==>> Gia tri can nap se la 65536 - (1000/1) ==>> Ma Hexa la FC18H
		// == >>
		TL0 = 0x18;
		TH0 = 0xFC;
		TR0 = 1;
	
		while(TF0 == 0);
		TR0 = 0;
		TF0 = 0;
		t--;
	}while(t != 0);
}
void main()
{
	
	// chon timee0 che do tao tre va khong bang cac bit TR0, TR1;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	while(1)
	{
		P1_1 = !P1_1;
		Tao_Tre_Timer(1000);
	}
}