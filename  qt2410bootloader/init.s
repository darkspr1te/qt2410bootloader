BIT_SELFREFRESH EQU	(1<<22)

;stack base address
_STACK_BASEADDRESS	EQU 0x31ff8000  

;BWSCON
DW8		    EQU	(0x0)
DW16		EQU	(0x1)
DW32		EQU	(0x2)
WAIT		EQU	(0x1<<2)
UBLB		EQU	(0x1<<3)

;BUSWIDTH=32
B1_BWSCON	EQU (DW32)
B2_BWSCON	EQU (DW16)
B3_BWSCON	EQU (DW16+WAIT+UBLB)
B4_BWSCON	EQU (DW16)
B5_BWSCON	EQU (DW16)
B6_BWSCON	EQU (DW32)
B7_BWSCON	EQU (DW32)

;BANK0CON 
B0_Tacs		EQU	0x0	;0clk
B0_Tcos		EQU	0x0	;0clk
B0_Tacc		EQU	0x7	;14clk
B0_Tcoh		EQU	0x0	;0clk
B0_Tah		EQU	0x0	;0clk
B0_Tacp		EQU	0x0	
B0_PMC		EQU	0x0	;normal

;BANK1CON
B1_Tacs		EQU	0x0	;0clk
B1_Tcos		EQU	0x0	;0clk
B1_Tacc		EQU	0x7	;14clk
B1_Tcoh		EQU	0x0	;0clk
B1_Tah		EQU	0x0	;0clk
B1_Tacp		EQU	0x0	
B1_PMC		EQU	0x0	;normal

;Bank 2 parameter
B2_Tacs		EQU	0x0	;0clk
B2_Tcos		EQU	0x0	;0clk
B2_Tacc		EQU	0x7	;14clk
B2_Tcoh		EQU	0x0	;0clk
B2_Tah		EQU	0x0	;0clk
B2_Tacp		EQU	0x0	
B2_PMC		EQU	0x0	;normal

;Bank 3 parameter
B3_Tacs		EQU	0x0	;0clk
B3_Tcos		EQU	0x1	;0clk
B3_Tacc		EQU	0x7	;14clk
B3_Tcoh		EQU	0x1	;0clk
B3_Tah		EQU	0x0	;0clk
B3_Tacp		EQU	0x0	
B3_PMC		EQU	0x0	;normal

;Bank 4 parameter
B4_Tacs		EQU	0x0	;0clk
B4_Tcos		EQU	0x0	;0clk
B4_Tacc		EQU	0x7	;14clk
B4_Tcoh		EQU	0x0	;0clk
B4_Tah		EQU	0x0	;0clk
B4_Tacp		EQU	0x0	
B4_PMC		EQU	0x0	;normal

;Bank 5 parameter
B5_Tacs		EQU	0x0	;0clk
B5_Tcos		EQU	0x0	;0clk
B5_Tacc		EQU	0x7	;14clk
B5_Tcoh		EQU	0x0	;0clk
B5_Tah		EQU	0x0	;0clk
B5_Tacp		EQU	0x0	
B5_PMC		EQU	0x0	;normal

;Bank 6 parameter
B6_MT		EQU	0x3	;SDRAM
B6_Trcd		EQU	0x1	;3clk
B6_SCAN		EQU	0x1	;9bit

;Bank 7 parameter
B7_MT		EQU	0x0	; ROM or SRAM
B7_Trcd		EQU	0x0	;2clk
;B7_Trcd		EQU	0x1	;3clk
B7_SCAN		EQU	0x1	;9bit

;ram related variables
REFEN		EQU	0x1	;Refresh enable
TREFMD		EQU	0x0	;CBR(CAS before RAS)/Auto refresh
Trp		    EQU	0x0	;2clk
Trc		    EQU	0x3	;7clk
Tchr		EQU	0x2	;3clk
REFCNT		EQU	1113	;period=15.6us, HCLK=60Mhz, (2048+1-15.6*60)

;=================
; Memory control 
;=================
BWSCON      EQU  0x48000000     ;Bus width & wait status
BANKCON0    EQU  0x48000004     ;Boot ROM control
BANKCON1    EQU  0x48000008     ;BANK1 control
BANKCON2    EQU  0x4800000c     ;BANK2 cControl
BANKCON3    EQU  0x48000010     ;BANK3 control
BANKCON4    EQU  0x48000014     ;BANK4 control
BANKCON5    EQU  0x48000018     ;BANK5 control
BANKCON6    EQU  0x4800001c     ;BANK6 control
BANKCON7    EQU  0x48000020     ;BANK7 control
REFRESH     EQU  0x48000024     ;DRAM/SDRAM refresh
BANKSIZE    EQU  0x48000028     ;Flexible Bank Size
MRSRB6      EQU  0x4800002c     ;Mode register set for SDRAM
MRSRB7      EQU  0x48000030     ;Mode register set for SDRAM

;=================
; INTERRUPT
;=================
SRCPND       EQU  0x4a000000    ;Interrupt request status
INTMOD       EQU  0x4a000004    ;Interrupt mode control
INTMSK       EQU  0x4a000008    ;Interrupt mask control
PRIORITY     EQU  0x4a00000a    ;IRQ priority control
INTPND       EQU  0x4a000010    ;Interrupt request status
INTOFFSET    EQU  0x4a000014    ;Interruot request source offset
SUSSRCPND    EQU  0x4a000018    ;Sub source pending
INTSUBMSK    EQU  0x4a00001c    ;Interrupt sub mask

;==========================
; CLOCK & POWER MANAGEMENT
;==========================
LOCKTIME    EQU  0x4c000000     ;PLL lock time counter
MPLLCON     EQU  0x4c000004     ;MPLL Control
UPLLCON     EQU  0x4c000008     ;UPLL Control
CLKCON      EQU  0x4c00000c     ;Clock generator control
CLKSLOW     EQU  0x4c000010     ;Slow clock control
CLKDIVN     EQU  0x4c000014     ;Clock divider control

;=================
; WATCH DOG TIMER
;=================
WTCON     EQU  0x53000000       ;Watch-dog timer mode
WTDAT     EQU  0x53000004       ;Watch-dog timer data
WTCNT     EQU  0x53000008       ;Eatch-dog timer count

;Pre-defined constants
USERMODE    EQU 	0x10
FIQMODE     EQU 	0x11
IRQMODE     EQU 	0x12
SVCMODE     EQU 	0x13
ABORTMODE   EQU 	0x17
UNDEFMODE   EQU 	0x1b
MODEMASK    EQU 	0x1f
NOINT       EQU 	0xc0

;The location of stacks
UserStack	EQU	(_STACK_BASEADDRESS-0x3800)	;0x33ff4800 ~ 
SVCStack        EQU	(_STACK_BASEADDRESS-0x2800) 	;0x33ff5800 ~
UndefStack	EQU	(_STACK_BASEADDRESS-0x2400) 	;0x33ff5c00 ~
AbortStack	EQU	(_STACK_BASEADDRESS-0x2000) 	;0x33ff6000 ~
IRQStack        EQU	(_STACK_BASEADDRESS-0x1000)	;0x33ff7000 ~
FIQStack	EQU	(_STACK_BASEADDRESS-0x0)	;0x33ff8000 ~ 	

	
	   ; The main entry of mon program
	;IMPORT  ISR_IRQ
		
	AREA    Init, CODE, READONLY 

	; --- Standard definitions of mode bits and interrupt (I & F) flags in PSRs

	ENTRY

    EXPORT Reset_Handler
    
    
Reset_Handler
    LDR r0,=WTCON ;close watch dog 
    LDR r1,=0x0
    STR r1,[r0] 
    
    LDR r0,=INTMSK;mask all interrupt
    LDR r1,=0xffffffff
    STR r1,[r0]
    
    LDR r0,=INTSUBMSK;mask all sub interrupt
    LDR r1,=0x7ff
    STR r1,[r0]
    
    LDR r0,=CLKDIVN;samsung code
    LDR r1,=0x3
    STR r1,[r0]
    
    LDR r0,=LOCKTIME
    LDR r1,=0xffffff
    STR r1,[r0]
    
    LDR r0,=MPLLCON
    ;ldr	r1,=((M_MDIV<<12)+(M_PDIV<<4)+M_SDIV)  ;Fin=12MHz,Fout=50MHz
    LDR r1,=((0x5c<<12)+(0x4<<4)+0x0)  ;Fin=12MHz,Fout=200MHz
    STR r1,[r0]
    
    ldr	r0, =CLKCON
	ldr	r1, =0xffff0
	str	r1, [r0]	
    ;Configure UPLL
    ;ldr     r0, =UPLLCON          
    ;ldr     r1, =((0x48<<12)+(0x3<<4)+0x2)  ;Fin=12MHz, Fout=48MHz
    ;str     r1, [r0]
    ;LDR r1,=GSTATUS2
    ;LDR r10,[r1]
    ;TST r10,#0x2
    ;bne 1000f
    
    

Init_HardWare
	B	Init_Memory ;Init_Stack

Init_Memory

	; Set memory control registers
	add		r0, pc, #SMRDATA - (. + 8)
	ldr	r1, =BWSCON	; BWSCON Address
	add	r2, r0, #52	; End address of SMRDATA
loop10
	ldr	r3, [r0], #4
	str r3, [r1], #4
	cmp	r2, r0
	bne loop10

  	B	Init_Stack


 ;*********************************************************************************/
 ; Init_Stack :  Initialise stack pointer registers and copy .Data
 ;    to RAM
 ;*********************************************************************************/
Init_Stack
     mrs	r0,cpsr
	 bic	r0,r0,#MODEMASK
	 orr	r1,r0,#UNDEFMODE|NOINT
	 msr	cpsr_cxsf,r1		;UndefMode
	 ldr	sp,=UndefStack
	
	 orr	r1,r0,#ABORTMODE|NOINT
	 msr	cpsr_cxsf,r1		;AbortMode
	 ldr	sp,=AbortStack

	 orr	r1,r0,#IRQMODE|NOINT
	 msr	cpsr_cxsf,r1		;IRQMode
	 ldr	sp,=IRQStack
    
	 orr	r1,r0,#FIQMODE|NOINT
	 msr	cpsr_cxsf,r1		;FIQMode
	 ldr	sp,=FIQStack

	 bic	r0,r0,#MODEMASK|NOINT
	 orr	r1,r0,#SVCMODE
	 msr	cpsr_cxsf,r1		;SVCMode
	 ldr	sp,=SVCStack
	 
	 ;COPY VECTOR DATA
	 ;LDR r0,=Start
	 ;LDR r1,=0x0
	 ;LDR R3,=0x1000
;CopyVector
     ;LDR r4,[r0],#4
	 ;STR r4,[r1],#4
	 ;SUB R3,R3,#4
	 ;CMP R3,#0
	 ;BNE CopyVector
         
     MOV fp,#0 
     MOV a1,#0
     MOV a2,#0

; --- Now enter the C code
     IMPORT  __main  
     B  __main  ; note use B not BL, because an application will never return this way

LTORG
;======================================================
; Memory System Initialize Data for NET-Start!
;======================================================
SMRDATA DATA
; Memory configuration should be optimized for best performance 
; The following parameter is not optimized.                     
; Memory access cycle parameter strategy
; 1) The memory settings is  safe parameters even at HCLK=75Mhz.
; 2) SDRAM refresh period is for HCLK=75Mhz. 

        DCD (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
    	DCD ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))   ;GCS0
    	DCD ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))   ;GCS1 
    	DCD ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))   ;GCS2
    	DCD ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))   ;GCS3
    	DCD ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))   ;GCS4
    	DCD ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))   ;GCS5
    	DCD ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))    ;GCS6
    	DCD ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))    ;GCS7
    	DCD ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)    
	    DCD 0x32            ;SCLK power saving mode, BANKSIZE 128M/128M
    	DCD 0x30            ;MRSR6 CL=3clk
    	DCD 0x30            ;MRSR7
        ;ALIGN
  
	END



