#include <regx52.h>

// Khoi tao xung ra tu p3_4;
sbit PWM = P3^4;

// Khoi tao bien duty_cycle
unsigned char Duty_Cycle;

// Khoi tao bien de luu gia tri cua chu ki 
unsigned int T, T_on, T_off;

// Khoi tao bien de luu gia tri nap lai cho Timer khi o muc cao va muc thap 
unsigned char TH0_on_Reload, TL0_on_Reload, TH0_off_Reload, TL0_off_Reload;

// Tao ham dung chuong trinh trong ?milisecond
void Sleep_ms(unsigned int t)
{
	unsigned int i, j;
	for(i = 0; i < t; i++)
	{
		for(j = 0; j < 123; j++);
	}
}


void _PWM_Init(unsigned int ck)
{
	PWM = 1;
	// Khoi tao timer0 16 bit (dem tu 0 - 65536);
	TMOD &= 0xF0;
	TMOD |= 0x01;
	
	// Cho phep ngat timer0;
	ET0 = 1;
	EA = 1;
	
	T = ck;
	T_on = T/2;
	T_off = T - T_on;
	
	// Khoi tao gia tri de nap cho timer khi o muc cao 
	TH0_on_Reload = (65536 - T_on) >> 8;
	TL0_on_Reload = (65536 - T_on) & 0x00FF;
	
	// Khoi tao gia tri de nap cho timer khi i muc thap
	TH0_off_Reload = (65536 - T_off) >> 8;
	TL0_off_Reload = (65536 - T_off) & 0x00FF;
	
	// Nap gia tri cho timer0
	TH0 = TH0_on_Reload;
	TL0 = TL0_on_Reload;
	
}

void _Set_Duty_Cycle(unsigned char _duty_cycle)
{
	if(_duty_cycle == 0)
	{
		PWM = 0;
		ET0 = 0;
	}
	else if(_duty_cycle == 100)
	{
		PWM = 1;
		ET0 = 0;
	}
	else
	{
		Duty_Cycle = _duty_cycle;
		T_on = (unsigned long)(T) * Duty_Cycle / 100;
		T_off = T - T_on;
		
		// Khoi tao gia tri de nap cho timer khi o muc cao 
		TH0_on_Reload = (65536 - T_on) >> 8;
		TL0_on_Reload = (65536 - T_on) & (0x00FF);
		
		// Khoi tao gia tri de nap cho timer khi i muc thap
		TH0_off_Reload = (65536 - T_off) >> 8;
		TL0_off_Reload = (65536 - T_off) & (0x00FF);
		ET0 = 1;
	}
}

void PWM_Start()
{
	TR0 = 1;
}

void PWM_Stop()
{
	TR0 = 0;
}


void main()
{
	_PWM_Init(1000);
	PWM_Start();
	_Set_Duty_Cycle(99);
	while(1)
	{
	}
	
}


void _PWM_Interrupt(void) interrupt 1
{
	PWM_Stop();
	PWM = !PWM;
	if(PWM)
	{
		TH0 = TH0_on_Reload;
		TL0 = TL0_on_Reload;
	}
	else
	{
		TH0 = TH0_off_Reload;
		TL0 = TL0_off_Reload;
	}
	PWM_Start();
}


































