#include "isr.h"
#define NULL 0
typedef void (*voidfun)();

//extern functions
extern void Timer0_ISR(void);
extern void UARTIrq(void);
extern void UART0_Init(void);
// �ŧi���_�V�q���
voidfun (IntHandlerTable)[IRQ_INT_NO] ;

// �M�����_���A
void ClrIntStatus(void)
{
    INTMSK_REG = 0xffffffff;  // ���F���줤�_�ӷ����~�A�����Ҧ����_�ӷ�
    INTPND_REG = 0xffffffff;  // �M���Ҧ������Ԧ줸
}
// ��l�Ƥ��_�V�q���
void creatIntHandlerTable(void)
{
    int i;

    for (i=0; i<IRQ_INT_NO; i++)
    {
        IntHandlerTable[i] = NULL;
    }
}
// �]�w���_�V�q���
void setIRQHandler(int i, voidfun isr)
{
    if ((i >= 0) && (i < IRQ_INT_NO))
    {
        IntHandlerTable[i] = isr;
    }
}
// ���_�A�ȱ`������i�J�I
void ISR_IRQ(void)
{
    int currentIRQnumber;

    currentIRQnumber = INTOFFSET_REG;
    
    if ((currentIRQnumber >= 0) && (currentIRQnumber < IRQ_INT_NO))
    {
        if (IntHandlerTable[currentIRQnumber] != NULL)
        {
             Clear_SRCPendingBit(currentIRQnumber);
		     Clear_INTPendingBit(currentIRQnumber);           
             IntHandlerTable[currentIRQnumber](); 
        }
    }
     
}

void InitIRQDevices()
{
	//initial timer0
  	Init_Timer();
  	//initial uart
  	UART0_Init();
}

void setupIRQEnv()
{
	//mask all interrupt
  	ClrIntStatus();
    //create interrupt handler table
  	creatIntHandlerTable();
    //register interrupt
  	setIRQHandler(nTIMER0_INT, Timer0_ISR); 
  	setIRQHandler(UART0_INT, UARTIrq); 
  	 //enable IRQ
  	enable_IRQ();
    //enable timer0 interrupt
  	Enable_Int(nTIMER0_INT);
  	Enable_Int(UART0_INT);
}



