;FPCAR  EQU 0xE000EF38
	
	
	AREA    Contexts, CODE, READONLY

    EXPORT  save_full_context
	EXPORT  save_lazy_context
	EXPORT  restore_full_context
    EXPORT  restore_lazy_context
	EXPORT  reset_stack_and_switch
	EXPORT  set_MSP;
	EXPORT  set_PSP
    EXPORT  create_new_context_ll
	EXPORT	disable_irq
	EXPORT  enable_irq
	EXTERN  tempStack
	EXTERN  FPCAR

save_full_context

	LDR  R3, =FPCAR
	
	LDR  R2, [R3]
	
	LDR R1 , [R2]
	
	MRS	  R2, PSP
	
	
    VSTR     S0, [R1, #0]
    VSTR     S1, [R1, #4]
    VSTR     S2, [R1, #8]
    VSTR     S3, [R1, #12]
    VSTR     S4, [R1, #16]
    VSTR     S5, [R1, #20]
    VSTR     S6, [R1, #24]
    VSTR     S7, [R1, #28]
    VSTR     S8, [R1, #32]
    VSTR     S9, [R1, #36]
    VSTR     S10, [R1, #40]
    VSTR     S11, [R1, #44]
    VSTR     S12, [R1, #48]
    VSTR     S13, [R1, #52]
    VSTR     S14, [R1, #56]
	VSTR     S15, [R1, #60]


    VMRS    R3, FPSCR
	
    STR     R3, [R1, #64] 
	
	STR R4, [R2, #-4]
	STR R5, [R2, #-8]
	STR R6, [R2, #-12]
	STR R7, [R2, #-16]
	STR R8, [R2, #-20]
	STR R9, [R2, #-24]
	STR R10, [R2, #-28]
	STR R11, [R2, #-32]

	VSTR S16, [R2, #-36]
	VSTR S17, [R2, #-40]
	VSTR S18, [R2, #-44]
    VSTR S19, [R2, #-48]
    VSTR S20, [R2, #-52]
    VSTR S21, [R2, #-56]
    VSTR S22, [R2, #-60]
    VSTR S23, [R2, #-64]
    VSTR S24, [R2, #-68]
    VSTR S25, [R2, #-72]
    VSTR S26, [R2, #-76]
    VSTR S27, [R2, #-80]
    VSTR S28, [R2, #-84]
    VSTR S29, [R2, #-88]
    VSTR S30, [R2, #-92]
    VSTR S31, [R2, #-96]
	
	
	SUB R2, R2, #100
    
	MOV R3, #0x00000000
		
	STR R3, [R2]
	
	STR 	R2, [R0]
	

    BX      LR	

save_lazy_context
	MRS	  R2, PSP
	
	
	STR R4, [R2, #-4]
	STR R5, [R2, #-8]
	STR R6, [R2, #-12]
	STR R7, [R2, #-16]
	STR R8, [R2, #-20]
	STR R9, [R2, #-24]
	STR R10, [R2, #-28]
	STR R11, [R2, #-32]
    
	SUB R2, R2, #36
	
	MOV R3, #0x0000010
		
		
	STR R3, [R2]
	
	
	STR 	R2, [R0]
	

    BX      LR	
set_MSP

	MSR MSP, R0
    BX      LR

set_PSP

	MSR PSP, R0
    BX      LR

reset_stack_and_switch

	LDR R2, =tempStack
	LDR R1, [R2]
	MSR MSP, R1
	
	LDR R1, [R0]
	TST R1, #0x10  
	BEQ restore_full_context        
	
	BL restore_lazy_context
	 
	 BX      LR	

restore_full_context

	VLDR S31, [R0, #4]
	VLDR S30, [R0, #8]
	VLDR S29, [R0, #12]
	VLDR S28, [R0, #16]
	VLDR S27, [R0, #20]
	VLDR S26, [R0, #24]
	VLDR S25, [R0, #28]
	VLDR S24, [R0, #32]	
	VLDR S23, [R0, #36]
	VLDR S22, [R0, #40]
	VLDR S21, [R0, #44]
	VLDR S20, [R0, #48]
	VLDR S19, [R0, #52]
	VLDR S18, [R0, #56]
	VLDR S17, [R0, #60]
	VLDR S16, [R0, #64]

	
	LDR R11, [R0, #68]
	LDR R10, [R0, #72]
	LDR R9, [R0, #76]
	LDR R8, [R0, #80]
	LDR R7, [R0, #84]
	LDR R6, [R0, #88]
	LDR R5, [R0, #92]
	LDR R4, [R0, #96]
	
	ADD R0, R0 ,#100


	MOV LR, #0xFFFFFFED
		
	MSR PSP, R0
	BX      LR


restore_lazy_context
	
	LDR R11, [R0, #4]
	LDR R10, [R0, #8]
	LDR R9, [R0, #12]
	LDR R8, [R0, #16]
	LDR R7, [R0, #20]
	LDR R6, [R0, #24]
	LDR R5, [R0, #28]
	LDR R4, [R0, #32]
	
	ADD R0, R0, #36

	MOV LR, #0xFFFFFFFD
	
	MSR PSP, R0
   	BX      LR


create_new_context_ll
	
	
	MOV      R4, #0

	MOV      R6, #0x01000000
	
	LDR     R5,  [R0]
	
	
	
    STR     R6 , [R5, #0]
	
    STR     R1, [R5, #-4]
	STR     R3, [R5, #-8]
	STR     R4, [R5, #-12]
	STR     R4, [R5, #-16]
	STR     R4, [R5, #-20]
	STR     R4, [R5, #-24]
	STR     R2, [R5, #-28]
	STR     R4, [R5, #-32]
	STR     R4, [R5, #-36]
	STR     R4, [R5, #-40]
	STR     R4, [R5, #-44]
	STR     R4, [R5, #-48]
	STR     R4, [R5, #-52]
	STR     R4, [R5, #-56]
	STR     R4, [R5, #-60]
	
	MOV R6, #0x00000010
	
	STR  R6, [R5, #-64]

	SUB     R5, R5, #64
	
	STR     R5, [R0]
	
	BX      LR

disable_irq
		MOV     R0, #0xF0    
        MSR     BASEPRI, R0 
		CPSID   I		
        ISB                        
        DSB   
		BX      LR		


enable_irq
	   MOV     R0, #0
       MSR     BASEPRI, R0
	   CPSIE   I
       ISB
       DSB
	   BX      LR
   
	END


