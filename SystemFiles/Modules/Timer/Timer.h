/** @file Timer.h
 *  @brief Timer management subsystem with callback support
 *  @author 0Reach0
 *  @date 2025
 */
#ifndef __TIMER_H__
#define __TIMER_H__

#include "PlumaConfig.h"

#ifdef TIMER


#include <stdint.h>

struct STask;

/** 
* @defgroup timer Timer
* @brief Timer management subsystem with callback support
* @{
*/


/** @brief Array of active timers */
extern uint8_t timersArraySize;

/** @brief Reserved array slots count */
extern uint8_t timersArrayReservedSize;

/** @brief Array of active timers */
extern struct Timer **activeTimersArray;




/**
 * @defgroup timer_config Timer Configuration
 * @brief Timer subsystem constants and settings
 * @{
 */



/** @brief Default reserved size for active timers array */
#define DEFAULT_RESERVED_ACTIVE_TIMERS_SIZE 2


/** @brief Timer interrupt interval in hardware ticks */
#define TIMERS_INTERRUPT_INTERVAL_TICKS 0x00FFFFFF


/** @brief Array resize increment step */
#define TIMER_RESIZE_INCREMENT 2

/** @} */ // end of timer_config



/**
 * @def stop_timer(timer)
 * @brief Stop timer execution
 * @param timer Valid Timer pointer
 */
#define stop_timer(timer) ((timer)->isStoped = 1)


/**
 * @def resume_timer(timer)
 * @brief Resume stopped timer
 * @param timer Valid Timer pointer
 */
#define resume_timer(timer) ((timer)->isStoped = 0)




/**
 * @struct Timer
 * @brief Timer structure with callback support
 * @details Supports two-level timing resolution:
 * - Ticks (coarse timing)
 * - Sub-ticks (fine-grained timing)
 */
struct Timer {
    uint32_t remainTicks;    /**< Remaining coarse-grained ticks */
    uint32_t remainSubTicks; /**< Remaining fine-grained sub-ticks */
    void (*callBack)();      /**< Callback function pointer */
    uint8_t isStoped;        /**< Timer state: 0-running, 1-stopped */
};





/**
 * @brief Initialize and start timer
 * @param timer Uninitialized Timer structure
 * @param ticks Initial tick count
 * @param callBack Callback function (void func(void))
 * @return 0 on success, error code otherwise
 * @note Adds timer to activeTimersArray
 */
uint8_t set_timer(struct Timer *timer, 
                 uint32_t ticks, 
                 void (*callBack)());


/**
 * @brief Reset timer with new duration
 * @param timer Initialized Timer pointer
 * @param ticks New tick count
 * @note Maintains current running state
 */
void reset_timer(struct Timer *timer, uint32_t ticks);


/**
 * @brief Precision timer reset
 * @param timer Initialized Timer pointer
 * @param ticks Coarse-grained ticks
 * @param subTicks Fine-grained sub-ticks
 */
void reset_long_timer(struct Timer *timer, 
                     uint32_t ticks, 
                     uint32_t subTicks);


/**
 * @brief Deactivate and remove timer
 * @param timer Active Timer pointer
 * @return 0 on success, error code otherwise
 * @note Removes from activeTimersArray
 */
uint8_t remove_timer(struct Timer *timer);


/**
 * @brief Process timer countdowns
 * @param dec Value to decrement from active timers
 * @warning Called from interrupt context
 */
void process_timers(uint32_t dec);

// /** @} */ // end of timer





#endif // TIMER


#endif // __TIMER_H__