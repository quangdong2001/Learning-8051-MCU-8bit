#include <regx52.h>

// Khai bai chan tao xung PWM
sbit PWM = P3^4;
// Khai bao bien duty cycle
unsigned char _duty_cycle;

// Khai bao cho ky, thoi gian o muc cao, thoi gian o muc thap.
unsigned int T, T_on, T_off;

// Khai bao gia tri nao vao cho timer0 de tao thoi gian tre cho muc cao va muc thap
unsigned int TH0_on_Reload, TL0_on_Reload, TH0_off_Reload, TL0_off_Reload;

// Khai nao bien de dieu khien do sang cua bong den 
unsigned char SET = 0, DOWN = 0, UP = 1;
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for( i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}

void PWM_Init(unsigned int ck)
{
	PWM = 1;
	// Chon timer0 che do 16 bit
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	ET0 = 1;
	EA = 1;
	
	T = ck;
	
	T_on = T/2;
	T_off = T - T_on;
	
	TH0_on_Reload = (65536 - T_on) >> 8;
	TL0_on_Reload = (65536 - T_on) & 0x00FF;
	
	TH0_off_Reload = (65536 - T_off) >> 8;
	TL0_off_Reload = (65536 - T_off) & 0x00FF;
	
	TH0 = TH0_on_Reload;
	TL0 = TL0_on_Reload;
}

void _Set_PWM(unsigned char _duty)
{
	PWM = !PWM;
	if(_duty == 0)
	{
		PWM = 0;
		ET0 = 0;
	}
	else if(_duty == 100)
	{
		PWM = 1;
		ET0 = 0;
	}
	else
	{
		T_on = (unsigned long)(T) * _duty / 100;
		T_off = T - T_on;
		
		TH0_on_Reload = (65536 - T_on) >> 8;
		TL0_on_Reload = (65536 - T_on) & 0x00FF;
		
		TH0_off_Reload = (65536 - T_off) >> 8;
		TL0_off_Reload = (65536 - T_off) & 0x00FF;
		
		TH0 = TH0_on_Reload;
		TL0 = TL0_on_Reload;
		ET0 = 1;
	}
}


void Start()
{
	TR0 = 1;
}

void Stop()
{
	TR0 = 0;
}




void main()
{
	unsigned char dur = UP, duty = 0;
	PWM_Init(1000);
	Start();
	
	while(1)
	{
		Sleep_ms(100);
		if(dur == UP)
		{
			duty += 2;
			if(duty == 100)
			{
				dur = DOWN;
			}
		}
		else
		{
			duty -= 2;
			if(duty == 0)
			{
				dur = UP;
			}
		}
		_Set_PWM(duty);
	}
}

void Ngat_Timer0(void) interrupt 1
{
	Stop();
	PWM = !PWM;
	if(PWM == 1)
	{
		TH0 = TH0_on_Reload;
		TL0 = TL0_on_Reload;
	}
	else
	{
		TH0 = TH0_off_Reload;
		TL0 = TL0_off_Reload;
	}
	Start();
}

















