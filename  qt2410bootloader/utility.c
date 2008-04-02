#include "sys.h"
//delay for 1 milli second = 0.001 sec
void Delay(unsigned int ms)
{
	rTCFG0|=0xFF00;  //Prescaler1=255
	rTCFG1|=0x300; //Select MUX input for PWM Timer2:divider=16
	// I just compute this value by using my watch timing
	rTCNTB2=750; //50000000/16/(255+1)=81.92*10^-6 seconds
	rTCMPB2=0;   //81.92*750=0.06 but actually it runs a 1 milli seconds interval
	rTCON|=1<<13;//timer2 manual updata on
	rTCON&=~(1<<13);//timer2 manual updata off
	rTCON|=0x9<<12;//start timer2 with auto reload on and invert off
	while(ms!=0) {
		while(rTCNTO2>0);
		--ms;
	}
	rTCON&=~(0x9<<20);
} 

unsigned short ntohs(unsigned short s)
{
	return (s >> 8) | (s << 8);
}

unsigned long ntohl(unsigned long l)
{
	return  ((l >> 24) & 0x000000ff) |
		((l >>  8) & 0x0000ff00) |
		((l <<  8) & 0x00ff0000) |
		((l << 24) & 0xff000000);
}

unsigned short htons(unsigned short s)
{
	return (s >> 8) | (s << 8);
}

unsigned long htonl(unsigned long l)
{
	return ntohl(l);
}