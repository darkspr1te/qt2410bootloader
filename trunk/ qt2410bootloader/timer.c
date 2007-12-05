#include "sys.h"
extern void led_on();
extern void led_off();

unsigned int dispaly0=1;

void Init_Timer()
{
	rTCFG0=119; //Prescaler0 = 119
	rTCFG1=0x03; //Select MUX input for PWM Timer0:divider=16
	rTCNTB0=3125; //0.5秒钟触发一次中断
	rTCON|=(1<<1); //Timer 0 manual update
	rTCON=0x09; /*Timer 0 auto reload on
 	                 Timer 0 output inverter off
清                "Timer 0 manual update"
                   Timer 0 start */
}

void Timer0_ISR(void)
{
   // static int int_dispaly0=1;

    if(dispaly0 & 0x1)
        led_on(); 
     else
        led_off(); 

    dispaly0++; 
}