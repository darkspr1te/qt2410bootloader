#include <stdio.h>
#include <stdlib.h>
#include "isr.h"
#include "sys.h"
#include  "uC_OS.h"//ucos2
#define TaskStkLeath      10240*3                            


OS_STK TestTask1Stk[TaskStkLeath];
OS_STK TestTask2Stk[TaskStkLeath];


void TestTask1(void *pdata)
{

    pdata = pdata;
    while (1) {
      
     printf("##############run Task1!!!################\n\r");
     OSTimeDly(5000);

        
    }
}

void TestTask2 (void *pdata)
{
    pdata = pdata;

    while(1) {
      printf("##############run Task2!!!################\n\r");
      OSTimeDly(8000);
    }
}


int main(void)
{
 	int ret;
 	u_int MyMMUBase,i=0;
 	
 	PortInit();
 	setupIRQEnv();
 	InitIRQDevices();
 	OSInit();
    (void)OSTaskCreateExt(TestTask1,(void *)1,&TestTask1Stk[TaskStkLeath-1],1,0,&TestTask1Stk[0],TaskStkLeath,(void *)0,OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    (void)OSTaskCreateExt(TestTask2,(void *)2,&TestTask2Stk[TaskStkLeath-1],50,0,&TestTask2Stk[0],TaskStkLeath,(void *)0,OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
    OSStart();
}