	AREA Vect, CODE, READONLY
Mode_IRQ        EQU     0x12
I_BIT           EQU     0x80 ; when I bit is set, IRQ is disabled
F_BIT           EQU     0x40 ; when F bit is set, FIQ is disabled
Mode_SVC        EQU     0x13

    IMPORT  Reset_Handler           ; In init.s
    IMPORT  ISR_IRQ					; In isr.c 
    IMPORT OSTCBCur
    IMPORT OSTCBHighRdy
    IMPORT OSPrioCur
    IMPORT OSPrioHighRdy
    IMPORT OSTimeTick
    IMPORT OSIntExit        
    IMPORT OSIntEnter                     
	ENTRY 
	 LDR pc,=Reset_Handler
	 B   Undefined_Handler
	 B   SWI_Handler
	 B   Prefetch_Handler
	 B   DataAbort_Handler
	 NOP
	 B   IRQ_Handler
	 B   FIQ_Handler
	 
Undefined_Handler
	 B	Undefined_Handler

SWI_Handler
	 B	SWI_Handler

Prefetch_Handler
	 B	Prefetch_Handler

DataAbort_Handler
	 B	DataAbort_Handler 
IRQ_Handler   
	STMFD   SP!, {R0-R2}                         ; save work registers in IRQ
    MOV     R1, SP
    ADD     SP, SP, #12
    SUB     R2, LR, #4
    MRS     R0, SPSR       
    
    MSR     CPSR_c, #Mode_SVC | I_BIT | F_BIT   ; change to svc mode and disable IRQ,FIQ
    
    STMFD   SP!, {R2}           ; PC
    STMFD   SP!, {LR}           ; LR
    STMFD   SP!, {R3-R12}       ; R3-R12

	LDMFD   R1, {R4-R6}         ; get R1-R3 from IRQ's stack
    
    STMFD   SP!, {R4-R6}        ; push task's R1-R3
    STMFD   SP!, {R0}           ; push task's spsr
    
    LDR     R4, =OSTCBCur     ; OSTCBCur->OSTCBStkPtr = SP
    LDR     R5, [R4]
    STR     SP, [R5]
    
  	BL OSIntEnter
    ; switch to interrupt mode
    MSR     CPSR_c, #Mode_IRQ | I_BIT | F_BIT   ; change to IRQ mode and disable IRQ,FIQ        
    BL	    ISR_IRQ       
	;restore task after interrupt routine is finished
    MSR     CPSR_c, #Mode_SVC | I_BIT | F_BIT   ; change to SVC mdoe
    BL      OSIntExit
    LDMFD   SP!, {R4}
    MSR     SPSR_cxsf, R4
    LDMFD   SP!, {R0-R12, LR, PC}^              ; pop new task's context
FIQ_Handler
 	 B	FIQ_Handler



	END


