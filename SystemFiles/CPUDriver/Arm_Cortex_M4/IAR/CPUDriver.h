#ifndef __HARDWARECPULAYER_H__
#define __HARDWARECPULAYER_H__
#include <stdint.h>
#include "PlumaConfig.h"

extern volatile uint32_t * FPCCR;
extern volatile uint32_t *FPCAR;
extern volatile uint32_t* SYS_RVR;
extern volatile uint32_t* SYS_CVR;
extern volatile uint32_t * SYS_CSR;
extern uint32_t exc_return;



#define ARCH  ARM_V7
	

#define get_CVR (*SYS_CVR >> 8)

#define get_RVR (*SYS_RVR >> 8)
		


#define create_new_context(topStack, task, args)\
		{			\
			create_new_context_ll(topStack, task, args, sExit);\
		}

		
		
#ifdef USE_SYSTICK_TIMER_AS_MAIN
	 #define disable_mainTimer() *SYS_CSR &= ~(1 << 1)

	 #define enable_mainTimer() *SYS_CSR |=  (1 << 1)
#endif		

		
		
#define SAVE_CONTEXT()                                                                                  \
				disable_irq();                                                          \
		if(current != NULL) {                                                                   \
			uint8_t currentPrior = current->prior;                                          \
			queue[currentPrior][queueSize[currentPrior]-1] = current;                       \
			if(!current->isComplete){                                                       \
			save_context_ll(&current->topStack); }                                    \
			else                                                                            \
			{                                                                               \
				current->isComplete = 0;                                                \
					current->topStack = current->stackPointer;                      \
  					create_new_context(&current->topStack, current->task, current->args);\
				}                                                                       \
		}                                                                                       \
		enable_irq();                                                                                                                                           

		
		

extern void PREBASE();

extern void save_context_ll( uint32_t ** stackPointer);

extern void save_full_context(uint32_t ** stackPointer);
	
	
extern void save_lazy_context(uint32_t ** stackPointer);

	
extern void set_MSP(uint32_t *new_sp);

		
extern void set_PSP(uint32_t *new_sp);

		
extern void reset_stack_and_switch(uint32_t * stackPointer);	  //using to end shcedule and restore context of parametr stack	

		
extern void restore_full_context(uint32_t* stackPointer);

	
extern void restore_lazy_context(uint32_t* stackPointer);
	

extern void create_new_context_ll(uint32_t **topStack, void (*task)(uint32_t *), uint32_t * args, void (*free_sTask)());  //better to use create_new_context() mcros instead
	
	
extern void disable_irq(void);	

	
extern void enable_irq(void);


void set_main_RVR(uint32_t); //using to set the main timer reset value

extern uint8_t GET_FPU_STATUS_AND_RESET();

void sExit();

#endif 
