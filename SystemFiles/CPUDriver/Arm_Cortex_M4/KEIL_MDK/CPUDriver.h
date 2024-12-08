#ifndef __HARDWARECPULAYER_H__
#define __HARDWARECPULAYER_H__
#include <stdint.h>
#include "PlumaConfig.h"


extern volatile uint32_t* SYS_RVR;
extern volatile uint32_t* SYS_CVR;
extern volatile uint32_t * SYS_CSR;
extern uint32_t exc_return;




#define ARCH  ARM_V7
		
#ifdef USE_SYSTICK_TIMER_AS_MAIN

	
			#define disable_mainTimer() *SYS_CSR &= ~(1 << 1);	

			#define enable_mainTimer() *SYS_CSR |=  (1 << 1);

#endif

#define FPCAR_ADDRES 0xE000EF38

#define get_CVR (*SYS_CVR >> 8)

#define get_RVR (*SYS_RVR >> 8)

#define read_exc_return(exc_return) \
			__asm volatile("mov %0, lr" : "=r"(exc_return));\

								
#define create_new_context(topStack, task, args)\
		{			\
			create_new_context_ll((volatile uint32_t **)&topStack, task, args, sExit);\
		}

#define SAVE_CONTEXT()	\		
			read_exc_return(exc_return);																							\                  
			disable_irq();																			                      \                    
		if(current != NULL) {																		                    \   
			uint8_t currentPrior = current->prior;								                    \                     	 	
			queue[currentPrior][queueSize[currentPrior]-1] = current;									\
			if(!current->isComplete){ 																								\
				save_context_irq(current->topStack);}   																\
			else																																			\									 
			{																																					\									 
				current->isComplete = 0;																								\									 
					current->topStack = current->stackPointer;														\									 
  					create_new_context(current->topStack, current->task, current->args);\									 
				}																																				\
		}																																						\
		enable_irq();			

		
extern void save_context_irq(volatile uint32_t **);
		
		
extern void save_full_context(uint32_t *, volatile uint32_t **);
	
	
extern void save_lazy_context(volatile uint32_t **);

	
extern void set_MSP(uint32_t *new_sp);

		
extern void set_PSP(uint32_t *new_sp);

		
extern void reset_stack_and_switch(uint32_t * );		

		
extern void restore_full_context(uint32_t*);

	
extern void restore_lazy_context(uint32_t*);
	

extern void create_new_context_ll(volatile uint32_t **topStack, void (*task)(uint32_t *), uint32_t *, void (*free_task)());
	
	
extern void disable_irq(void);	

	
extern void enable_irq(void);

void postpone(uint32_t);



void sExit();

#endif 
