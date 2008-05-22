#include "sys.h"

void Init_Timer()
{
	rTCFG0|=249; //Prescaler0 = 249=>50000000/16/(249+1)=12500
	rTCFG1|=0x03; //Select MUX input for PWM Timer0:divider=16
	//rTCNTB0=12500; //1 secondes 12500/12500
	rTCNTB0=1;//for ucos2
	rTCON|=(1<<1); //Timer 0 manual update
	rTCON&=~(1<<1); //Timer 0 manual update off
	rTCON|=0x9;//auto reload on and start timer
}

void Timer0_ISR(void)
{
    OSTimeTick();
}