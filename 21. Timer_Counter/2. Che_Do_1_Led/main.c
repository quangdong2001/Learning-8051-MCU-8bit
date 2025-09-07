#include <regx52.h>

void Tao_Tre(unsigned int t)
{
	do
	{
		// Nhap gia tri cho thanh ghi TL, TH de tao do tre 1ms
		// Gia tri nap = 65536 - (1000 / 1) = FC18H
		TL0 = 0x18;
		TH0 = 0xFC;
		
		// Khoi dong timer0
		TR0 = 1;
		
		// Kiem tra lien tuc co TF
		while(TF0 == 0);
		TR0 = 0;
		TF0 = 0;
		t--;
	}while(t != 0);
}

void main()
{
	unsigned char i;
	// chon timer0 che do 1 16bit tao do tre va khoi dong bang phan mem bang bit TR0, TR1;
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	P0 = 0x00;
	while(1)
	{
		for(i = 0; i < 2; i++)
		{
			P0 = 0x01;
			Tao_Tre(200);
			P0 = 0x03;
			Tao_Tre(200);
			P0 = 0x07;
			Tao_Tre(200);
			P0 = 0x0F;
			Tao_Tre(200);
			P0 = 0x1F;
			Tao_Tre(200);
			P0 = 0x3F;
			Tao_Tre(200);
			P0 = 0x7F;
			Tao_Tre(200);
			P0 = 0xFF;
			Tao_Tre(200);
		}
		P0 = 0x00;
		Tao_Tre(200);
		for(i = 0; i <= 2; i++)
		{
			P0 = 0x0F;
			Tao_Tre(200);
			P0 = 0xF0;
			Tao_Tre(200);
		}
	}
}