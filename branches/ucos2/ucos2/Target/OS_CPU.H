#ifndef  __OS_CPU_H
#define  __OS_CPU_H

#ifdef  OS_CPU_GLOBALS
    #define OS_CPU_EXT
#else
    #define OS_CPU_EXT  extern
#endif

/*
*********************************************************************************************************
*                    定義與編譯器無關的數據類型.
*********************************************************************************************************
*/
typedef unsigned char  BOOLEAN;                 /* 布爾變量                                 */
typedef unsigned char  INT8U;                   /* 無符號8位整型變量                        */
typedef signed   char  INT8S;                   /* 有符號8位整型變量                        */
typedef unsigned short INT16U;                  /* 無符號16位整型變量                       */
typedef signed   short INT16S;                  /* 有符號16位整型變量                       */
typedef unsigned int   INT32U;                  /* 無符號32位整型變量                       */
typedef signed   int   INT32S;                  /* 有符號32位整型變量                       */
typedef float          FP32;                    /* 單精度浮點數（32位長度）                 */
typedef double         FP64;                    /* 雙精度浮點數（64位長度）                 */

typedef INT32U         OS_STK;                  /* 堆棧是32位寬度                           */

/*
*********************************************************************************************************
*                    與 ARM 體系結構相關的一些定義.
*********************************************************************************************************
*/
#define     OS_CRITICAL_METHOD     2            /* 選擇開、關中斷的方式.        */
extern void OS_ENTER_CRITICAL (void);
extern void OS_EXIT_CRITICAL (void);
extern void OS_TASK_SW (void);

#define OS_STK_GROWTH    1                      /*  堆棧是從上往下長的          */

#endif                                          /* __OS_CPU_H */

/*
********************************************************************************************************
* End.
********************************************************************************************************
*/
