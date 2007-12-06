#include "sys.h"
void Delay(unsigned int ms)
{
	
	/*if you want to sample adc data for 1 seconds,please uncomment 
	//rTCFG0|=0xF900;
	//rTCNTB4=12500;
	*/
	/*use timer4 to generate delay interval as unit ms*/
	rTCFG0|=0x400; //Prescaler1 = 4
	//rTCFG0|=0xF900;
	rTCFG1|=0x30000; //Select MUX input for PWM Timer4:divider=16
	rTCNTB4=3125;
	//rTCNTB4=12500;
	rTCON|=(1<<21);//timer4 manual update
	rTCON&=~(1<<21);//timer4 manual updata off
	rTCON|=(1<<20);//auto reload off
	while(ms--) {
		while(rTCNTO4>0);
	}
	rTCON&=~(1<<20);
	
	/*use timer0 to generate delay interval as unit ms*/
	/*rTCFG0=0x4; //Prescaler0 = 4
	rTCFG1=0x3; //Select MUX input for PWM Timer0:divider=16
	rTCNTB0=3125;
	rTCON|=(1<<1);//reload timer0 buffer;
	rTCON&=~(1<<1);//reload timer0 buffer;
	rTCON|=0x1;
	while(ms--) {
		while(rTCNTO0>0);
	}
	rTCON&=~(0x1);*/
} 