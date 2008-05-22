
#define  OS_CPU_GLOBALS
#include "uC_OS.h"
#include "isr.h"

#define  ARM_SVC_MODE   (0x00000013L)

extern unsigned int OS_CPU_SR_Save(void);
extern void OS_CPU_SR_Restore(unsigned int temp);
unsigned int mytemp;

void OS_ENTER_CRITICAL()
{
	mytemp=OS_CPU_SR_Save();
}

void OS_EXIT_CRITICAL()
{
	OS_CPU_SR_Restore(mytemp);
}
/*
********************************************************************************************************
* 函數: OSIntCtxSw.
* 描述: 中斷級任務切換,此處並不真正進行任務切換,具體切換在 IRQ 服務程序的彙編返回中.
********************************************************************************************************
*/
/*void OSIntCtxSw(void)
{
   // __OSIntCtxSw();
}*/

/*
********************************************************************************************************
* 函數: OSTaskStkInit.
* 描述: 任務堆棧初始化代碼.
* 輸入: task  : 任務開始執行的地址.
*       pdata ：傳遞給任務的參數.
*       ptos  ：任務的堆棧開始位置.
*       opt   ：附加參數，當前版本對於本函數無用，具體意義參見OSTaskCreateExt()的opt參數.
* 輸出: 棧頂指針位置.
********************************************************************************************************
*/
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
 INT32U *stk;

    stk = (INT32U*)ptos;    
    *stk-- = (INT32U)task;
    *stk-- = (INT32U)0x14141414;  //R14(LR)
    *stk-- = (INT32U)0x12121212;  //R12
    *stk-- = (INT32U)0x11111111;  //R11
    *stk-- = (INT32U)0x10101010;  //R10
    *stk-- = (INT32U)0x09090909;  //R9
    *stk-- = (INT32U)0x08080808;  //R8
    *stk-- = (INT32U)0x07070707;  //R7
    *stk-- = (INT32U)0x06060606;  //R6
    *stk-- = (INT32U)0x05050505;  //R5
    *stk-- = (INT32U)0x04040404;  //R4
    *stk-- = (INT32U)0x03030303;  //R3
    *stk-- = (INT32U)0x02020202;  //R2
    *stk-- = (INT32U)0x01010101;  //R1
    *stk-- = (INT32U)(pdata);     //R0    
    *stk   = (INT32U)0x13;        //SPSR(SVC MODE)
   
    return ((OS_STK *)stk);
}

#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                            (BEGINNING)
*
* Description: This function is called by OSInit() at the beginning of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}
#endif

/*
*********************************************************************************************************
*                                       OS INITIALIZATION HOOK
*                                               (END)
*
* Description: This function is called by OSInit() at the end of OSInit().
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts should be disabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSInitHookEnd (void)
{
}
#endif

/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                           OSTCBInit() HOOK
*
* Description: This function is called by OSTCBInit() after setting up most of the TCB.
*
* Arguments  : ptcb    is a pointer to the TCB of the task being created.
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
#if OS_VERSION > 203
void OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                                           /* Prevent Compiler warning                 */
}
#endif


/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void)
{
}

/*
*********************************************************************************************************
*                                             IDLE TASK HOOK
*
* Description: This function is called by the idle task.  This hook has been added to allow you to do  
*              such things as STOP the CPU to conserve power.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are enabled during this call.
*********************************************************************************************************
*/
#if OS_VERSION >= 251
void OSTaskIdleHook (void)
{
}
#endif
#endif
/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
