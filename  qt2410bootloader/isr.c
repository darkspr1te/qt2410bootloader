#include "isr.h"
#define NULL 0
typedef void (*voidfun)();

//extern functions
extern void Timer0_ISR(void);
extern void UARTIrq(void);
extern void UART0_Init(void);
extern void Dma0Done(void);
extern void Dma1Done(void);
extern void Dma2Done(void);
extern void Dma3Done(void);
extern void IICInt(void);


// 宣告中斷向量表格
voidfun (IntHandlerTable)[IRQ_INT_NO] ;

// 清除中斷狀態
void ClrIntStatus(void)
{
    INTMSK_REG = 0xffffffff;  // 除了全域中斷來源之外，關閉所有中斷來源
    INTPND_REG = 0xffffffff;  // 清除所有的等候位元
}
// 初始化中斷向量表格
void creatIntHandlerTable(void)
{
    int i;

    for (i=0; i<IRQ_INT_NO; i++)
    {
        IntHandlerTable[i] = NULL;
    }
}
// 設定中斷向量表格
void setIRQHandler(int i, voidfun isr)
{
    if ((i >= 0) && (i < IRQ_INT_NO))
    {
        IntHandlerTable[i] = isr;
    }
}
// 中斷服務常式執行進入點
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
  	setIRQHandler(nDMA0_INT, Dma0Done);
  	setIRQHandler(nDMA1_INT, Dma1Done);
  	setIRQHandler(nDMA2_INT, Dma2Done);
  	setIRQHandler(nDMA3_INT, Dma3Done);
  	setIRQHandler(nIIC_INT, IICInt);
  	
  	
  	
  	 //enable IRQ
  	enable_IRQ();
    //enable device interrupt
  	Enable_Int(nTIMER0_INT);
  	Enable_Int(UART0_INT);
  	Enable_Int(nDMA0_INT);
  	Enable_Int(nDMA1_INT);
  	Enable_Int(nDMA2_INT);
  	Enable_Int(nDMA3_INT);
  	Enable_Int(nIIC_INT);
  	
  	
}



