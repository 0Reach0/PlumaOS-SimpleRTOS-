/** @file CPUDriver.h
 *  @brief Low-level CPU control and context management
 *  @author 0Reach0
 *  @date 2025
 */
#ifndef __CPUDRIVER_H__
#define __CPUDRIVER_H__


#include <stdint.h>
#include "PlumaConfig.h"


/**
 * @defgroup cpudriver CPU Driver
 * @brief Low-level CPU control and context management
 * @{
 */



/** @brief Floating Point Context Control Register (volatile) */
extern volatile uint32_t *FPCCR;

/** @brief Floating Point Context Address Register (volatile) */
extern volatile uint32_t *FPCAR;

/** @brief System Timer Reload Value Register (volatile) */
extern volatile uint32_t *SYS_RVR;

/** @brief System Timer Current Value Register (volatile) */
extern volatile uint32_t *SYS_CVR;

/** @brief System Timer Control/Status Register (volatile) */
extern volatile uint32_t *SYS_CSR;

/** @brief Exception return value pattern */
extern uint32_t exc_return;



/** @brief Target architecture definition (ARMv7) */
#define ARCH ARM_V7




/** @brief Get current 24-bit timer value */
#define get_CVR (*SYS_CVR >> 8)

/** @brief Get timer reload value */
#define get_RVR (*SYS_RVR >> 8)





/**
 * @brief Initialize new task context
 * @param topStack Pointer to stack top
 * @param task Task entry function
 * @param args Task arguments
 */
#define create_new_context(topStack, task, args)\
    { create_new_context_ll(topStack, task, args, sExit); }



#ifdef USE_SYSTICK_TIMER_AS_MAIN


/** @brief Disable SysTick timer interrupts */
#define disable_mainTimer() *SYS_CSR &= ~(1 << 1)

/** @brief Enable SysTick timer interrupts */
#define enable_mainTimer() *SYS_CSR |=  (1 << 1)


#endif



/**
 * @brief Save execution context with atomic protection
 * @details Performs:
 * - Atomic context preservation
 * - Task state management
 * - Queue maintenance
 * - Task reinitialization if completed
 */
#define SAVE_CONTEXT()                                                                  \
    disable_irq();                                                                      \
    if(current != NULL) {                                                               \
        uint8_t currentPrior = current->prior;                                          \
        queue[currentPrior][queueSize[currentPrior]-1] = current;                       \
        if(!current->isComplete){                                                       \
            save_context_ll(&current->topStack);                                        \
        }                                                                               \
        else {                                                                          \
            current->isComplete = 0;                                                    \
            current->topStack = current->stackPointer;                                  \
            create_new_context(&current->topStack, current->task, current->args);       \
        }                                                                               \
    }                                                                                   \
    enable_irq();




/** @brief Prepare CPU for context saving */
extern void PRESAVE();

/** @brief Save minimal task context */
extern void save_context_ll(uint32_t **stackPointer);

/** @brief Save full CPU context */
extern void save_full_context(uint32_t **stackPointer);

/** @brief Save optimized context */
extern void save_lazy_context(uint32_t **stackPointer);

/** @brief Set Main Stack Pointer */
extern void set_MSP(uint32_t *new_sp);

/** @brief Set Process Stack Pointer */
extern void set_PSP(uint32_t *new_sp);

/** @brief Perform final context switch */
extern void reset_stack_and_switch(uint32_t *stackPointer);

/** @brief Restore full CPU context */
extern void restore_full_context(uint32_t *stackPointer);

/** @brief Restore optimized context */
extern void restore_lazy_context(uint32_t *stackPointer);



/**
 * @brief Low-level context initialization
 * @param topStack Stack top pointer
 * @param task Task function pointer
 * @param args Task arguments
 * @param free_sTask Task destructor
 */
extern void create_new_context_ll(uint32_t **topStack, 
                                 void (*task)(uint32_t *), 
                                 uint32_t *args, 
                                 void (*free_sTask)());

/** @brief Disable all interrupts */
extern void disable_irq(void);

/** @brief Enable all interrupts */
extern void enable_irq(void);

/** @brief Set timer reload value */
void set_main_RVR(uint32_t ticks);

/** @brief Get and clear FPU status */
extern uint8_t GET_FPU_STATUS_AND_RESET();

/** @brief Task termination handler */
void sExit();


/** @} */ // end of cpudriver


#endif // __CPUDRIVER_H__