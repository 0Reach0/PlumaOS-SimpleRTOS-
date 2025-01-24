/** @file TaskDelay.h
 *  @brief Task delay management subsystem
 *  @author Your Name
 *  @date 2023
 */
#ifndef __TASKDELAY_H__
#define __TASKDELAY_H__

#include <stdint.h>


/**
 * @defgroup task_delay TaskDelay
 * @brief Task delay management subsystem 
 * @{
 */


/**
 * @struct sTask
 * @brief Forward declaration of task structure
 */
struct sTask;

/** @brief Array of delayed task pointers */
extern struct sTask **sDelayArr; 

/** @brief Current number of delayed tasks */
extern uint8_t sDelaySize;        

/** @brief Reserved array slots count */
extern uint8_t sDelayReserved;   



/**
 * @defgroup delay_config Delay Configuration
 * @brief Configuration options for delay subsystem
 * @{
 */

/**
 * @def RESERVED_ON_DELAY_SIZE
 * @brief Default size of reserved space for delayed tasks array
 */
#define RESERVED_ON_DELAY_SIZE 2

/**
 * @def DELAY_RESIZE_INCREMENT
 * @brief Increment step for array expansion
 */
#define DELAY_RESIZE_INCREMENT 3

/** @} */ // end of delay_config



/**
 * @def GET_DELAY_ARR
 * @brief Get pointer to delayed tasks array
 * @return Pointer to sTask* array
 */
#define GET_DELAY_ARR sDelayArr

/**
 * @def GET_DELAY_SIZE
 * @brief Get current size of delayed tasks array
 * @return Number of elements in array
 */
#define GET_DELAY_SIZE sDelaySize

/**
 * @def GET_DELAY_RESERVED
 * @brief Get reserved slots count
 * @return Number of reserved slots
 */
#define GET_DELAY_RESERVED sDelayReserved

 
/**
 * @brief Delay task execution for specified ticks
 * @param ticks Number of system ticks to delay
 */
void sDelay(uint32_t ticks);

/**
 * @brief Extended precision delay with sub-ticks
 * @param ticks Whole ticks component
 * @param subTicks Fractional ticks component
 */
void sLongDelay(uint32_t ticks, uint32_t subTicks);

/**
 * @brief Add new task to delay queue
 * @param task Task to delay
 * @return 0 on success, error code otherwise
 */
uint8_t new_sDelay(struct sTask *task);

/**
 * @brief Remove task from delay queue
 * @param task Task to remove and deallocate
 */
void free_sDelay(struct sTask *task);

/**
 * @brief Process delay queue decrements
 * @param dec Value to subtract from active delays
 */
void process_delays(uint32_t dec);

#endif // __TASKDELAY_H__