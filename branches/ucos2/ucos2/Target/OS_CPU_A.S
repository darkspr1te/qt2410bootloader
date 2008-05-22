        AREA    os_cpu_a, CODE, READONLY
        CODE32

        IMPORT  OSTCBCur                                ; 指向當前任務TCB的指針.
        IMPORT  OSTCBHighRdy                            ; 指向將要運行的任務TCB的指針.
        IMPORT  OSPrioCur                               ; 當前任務的優先級.
        IMPORT  OSPrioHighRdy                           ; 將要運行的任務的優先級.
        IMPORT  OSTaskSwHook                            ; 任務切換的鉤子函數.
        IMPORT  OSRunning                               ; uC/OS-II運行標誌.

        EXPORT  OSStartHighRdy                           ; 開始最高優先級任務.
		EXPORT  OS_CPU_SR_Save
   		EXPORT  OS_CPU_SR_Restore
		EXPORT  OSIntCtxSw 
		EXPORT  OSCtxSw

OSStartHighRdy

    ; OSRunning = TRUE
    LDR     R0, =OSRunning
    MOV     R1, #1
    STRB    R1, [R0]
    
    ; Load First Task
    LDR     R0, OSTCBHighRdy    ; Load address of OSTCBHighRdy
    LDR     SP, [R0]            ; Load SP of task
        
    LDMFD   SP!, {R1}       ; get spsr of first task
    MSR     SPSR_cxsf, R1
    LDMFD   SP!, {R0-R12, LR, PC}^  ;run first task!
;    
; void OSIntCtxSw(void)    
;
OSIntCtxSw
    LDR     R4, =OSPrioCur         ; OSPrioCur = OSPrioHighRdy
    LDR     R5, =OSPrioHighRdy
    LDRB    R6, [R5]
    STRB    R6, [R4]
    
    LDR     R4, =OSTCBCur          ; OSTCBCur = OSTCBHighRdy
    LDR     R5, =OSTCBHighRdy
    LDR     R6, [R5]
    STR     R6, [R4]
    
    LDR     SP, [R6]                ; SP = OSTCBCur->OSTCBStkPtr
    
    LDMFD   SP!, {R4}
    MSR     SPSR_cxsf, R4
    LDMFD   SP!, {R0-R12, LR, PC}^  ; pop new task's context
    
;
; OS_CPU_SR  OS_CPU_SR_Save(void)
;
OS_CPU_SR_Save
    MRS     R0, CPSR
    ORR     R1, R0, #0xC0    
    MSR     CPSR_c, R1      ;disabel IRQ and FIQ    
    MRS     R1, CPSR
    AND     R1, R1, #0xC0
    CMP     R1, #0xC0
    BNE     OS_CPU_SR_Save
    BX      LR
;
; void OS_CPU_SR_Restore(OS_CPU_SR cpu_sr)
;
OS_CPU_SR_Restore
    MSR     CPSR_c, R0
    BX      LR
;
; void OSCtxSw(void)
;    
OSCtxSw    
    STMFD   SP!, {LR}           ; save context of previous task 
    STMFD   SP!, {LR}
    STMFD   SP!, {R0-R12}
    MRS     R4, CPSR
    STMFD   SP!, {R4}
    
    LDR     R4, =OSTCBCur       ; OSTCBCur->OSTCBStkPtr = SP;
    LDR     R5, [R4]
    STR     SP, [R5]
    
    LDR     R4, =OSPrioCur         ; OSPrioCur = OSPrioHighRdy    
    LDR     R6, =OSPrioHighRdy    
    LDRB    R6, [R6]
    STRB    R6, [R4]
    
    LDR     R4, =OSTCBCur          ; OSTCBCur = OSTCBHighRdy
    LDR     R6, =OSTCBHighRdy
    LDR     R6, [R6]
    STR     R6, [R4]
    
    LDR     SP, [R6]                ; SP = OSTCBCur->OSTCBStkPtr
    
    LDMFD   SP!, {R4}
    MSR     SPSR_cxsf, R4
    
    LDMFD   SP!, {R0-R12, LR, PC}^  ; pop new task's context
    
    END      