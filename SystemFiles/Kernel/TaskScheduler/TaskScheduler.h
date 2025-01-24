/** @file task_scheduler.h
 *  @brief Task scheduler implementation for priority-based system
 *  @author 0Reach0
 *  @date 2025
 */
#ifndef __TASK_SCHEDULER_H__
#define __TASK_SCHEDULER_H__

#include "CPUDriver.h"



/** 
* @defgroup task_scheduler Task Scheduler
* @brief Task scheduler implementation for priority-based system
 * @{
*/


/** @brief Task scheduler activation flag */
extern uint8_t isActive;

//  /** @brief Temporary stack memory */
extern uint32_t *tempStack;



/**
 * @defgroup scheduler_settings Scheduler Configuration
 * @brief Task scheduler configuration options
 * @{
 */

/**
 * @def QUANT_MULTIPLIER
 * @brief Multiplier for calculating time quantum
 */
#define QUANT_MULTIPLIER 10000

/**
 * @def TEMP_STACK_SIZE
 * @brief Size of temporary stack in bytes
 */
#define TEMP_STACK_SIZE 1000

/**
 * @def SCHEDULE_TIME
 * @brief Default scheduling interval in cycles
 */
#define SCHEDULE_TIME 10000

/** @} */ // end of scheduler_settings


/**
 * @def Schedule()
 * @brief Configure main timer with default scheduling interval
 */
#define Schedule() set_main_RVR(SCHEDULE_TIME)

/**
 * @def is_active
 * @brief Macro alias for scheduler activation flag
 */
#define is_active isActive

/**
 * @def set_active()
 * @brief Activate task scheduler
 */
#define set_active() isActive = 1

/**
 * @def reset_active()
 * @brief Deactivate task scheduler
 */
#define reset_active() isActive = 0

/**
 * @def GET_TEMP_STACK()
 * @brief Get temporary stack pointer
 * @return Pointer to temporary stack memory
 */
#define GET_TEMP_STACK() tempStack


/** @} */ // end of task_scheduler


/**
 * @page timer_handler_page Timer Interrupt Handler Implementation
 * @brief This page contains the code that **must be copied** into the actual timer interrupt handler(Also you need to include **"Kernel.h"**) .
 * 
 * @details You can find this code in /Kernel/TaskScheduler/MainTimerHeandlerCode.txt.
 * 
 * @code
 * 
 *  if(current != 0)PRESAVE();
 * if(is_active) {
 *  static uint32_t idle_counter = 0;
 *	disable_mainTimer();
 *   while(1) { 
 *	process_delays(MAIN_RVR);
 *	process_timers(MAIN_RVR);
 *	
 *	if(current!= NULL)
 *	{
 *			if(MAIN_RVR < current->remainQuant && current->isComplete != 1)
 *			{
 *					current->remainQuant-= MAIN_RVR;
 *					enable_mainTimer();
 *					return;		
 *			}
 *			else{
 *					current->remainQuant = current->quant;	
 *			}
 *		}
 *			
 *		SAVE_CONTEXT() 
 *               current = 0;
 *		idle_counter = get_CVR;		
 *		for(uint8_t i = 0; i < (uint8_t)PRIOR_LEVELS; i++) {         																				 
 *                for(uint8_t t = 0; t < queueSize[i]; t++) {     																				 
 *                    if(queue[i][t]->isReady) {	
 *			current = queue[i][t];	               																					 																											
 *                       for(uint8_t it = t; it <= (queueSize[i]-2); it++) { 													 																								 
 *														queue[i][it] = queue[i][it+1];	
 *														queue[i][it+1] = NULL;
 *															
 *														}												    		
 *                       set_main_RVR(MAIN_RVR);																																   
 *												enable_mainTimer();																														 
 *                       reset_stack_and_switch(current->topStack);																					 
 *												}
 *									}                                      																					 
 *              }   
 *								current = NULL;
 *								if(idle_counter < get_CVR) idle_counter = get_CVR - idle_counter;
 *								else   idle_counter = (get_RVR - idle_counter) + get_CVR;
 *							 
 *           }                                              																					 
 *      }    
 * @endcode
 * 
 * @note This code is **mandatory** for proper task scheduling.
 * @warning Do not modify the structure unless you understand the consequences.
 */

#endif // __TASK_SCHEDULER_H__