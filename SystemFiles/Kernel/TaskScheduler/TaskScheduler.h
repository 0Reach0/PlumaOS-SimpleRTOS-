#ifndef __TASK_SCHEDULER_H__
#define __TASK_SCHEDULER_H__

#include "CPUDriver.h"

#define QUANT_MULTIPLIER 10000
#define TEMP_STACK_SIZE  1000
#define SCHEDULE_TIME    10000


#define Schedule() set_main_RVR(SCHEDULE_TIME);

#define is_active isActive
#define set_active() isActive = 1
#define reset_activr() isActive = 0

#define GET_TEMP_STACK() tempStack

extern uint8_t isActive;

extern uint32_t * tempStack;

//Also use this definitions in the file with timer interrupt_handler
//#include "Kernel.h"


//code u need to paste in handler of shceduler irq
//disable_mainTimer();
//	static uint32_t idle_counter = 0;
//	process_delays(MAIN_RVR);
//	process_timers(MAIN_RVR);
//	
//	if(current!= NULL)
//	{
//			if(MAIN_RVR < current->remainQuant && current->isComplete != 1)
//			{
//					current->remainQuant-= MAIN_RVR;
//					enable_mainTimer();
//					return;
//		
//			}
//			else{
//					current->remainQuant = current->quant;	
//			}
//		}
//	
//	if(is_active) {			
//		SAVE_CONTEXT()
//    while(1) {  
//						idle_counter = get_CVR;				 	
//						for(int i = 0; i < PRIOR_LEVELS; i++) {         																				 
//                for(int t = 0; t < queueSize[i]; t++) {     																				 
//                     if(queue[i][t]->isReady) {	
//												current = queue[i][t];	
//                        queue[i][t] = 0;                   																					 																											
//                        for(uint8_t it = 0; it < (queueSize[i]-1); it++) { 													 
//														if(queue[i][it] == 0 && it <= (queueSize[i]-1)-1){																									 
//														queue[i][it] = queue[i][it+1];	
//														queue[i][it+1] = NULL;
//															}
//														}												    		
//                        set_main_RVR(MAIN_RVR);																																   
//												enable_mainTimer();																														 
//                        reset_stack_and_switch(current->topStack);																					 
//												}
//									}                                      																					 
//               }   
//								current = NULL;
//								if(idle_counter < get_CVR) idle_counter = get_CVR - idle_counter;
//								else   idle_counter = (get_RVR - idle_counter) + get_CVR;
//							 
//            }                                              																					 
//        }            	  

#endif 
			