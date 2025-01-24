/** @file taskmanagement.h
 *  @brief Priority-based task scheduling system
 *  @author 0Reach0
 *  @date 2025
 */
#ifndef __TASKMANAGEMENT_H__
#define __TASKMANAGEMENT_H__

#include <stdint.h>
#include "sTask.h"




/**
 * @defgroup task_managment Task Management
 * @brief task management system
 * @{
 */

/** @brief Pointer to currently running task */
extern struct sTask *current; 

/** @brief Task queue array*/
extern struct sTask **queue[PRIOR_LEVELS];

/** @brief Task queue size*/
extern uint8_t queueSize[PRIOR_LEVELS];

/** @brief Reserved queue size */
extern uint8_t reservedQueueSize[PRIOR_LEVELS];





/**
 * @defgroup task_management_config Task Management Configuration
 * @brief Task management system configuration
 * @{
 */



/**
 * @def PRIOR_LEVELS
 * @brief Number of task priority levels
 */
#define PRIOR_LEVELS 6


/**
 * @def DEFAULT_RESERVED_Q_SIZE
 * @brief Default size of reserved queue
 */
#define DEFAULT_RESERVED_Q_SIZE 2


/**
 * @def TASK_RESIZE_INCREMENT
 * @brief Queue resizing increment step
 */


#define TASK_RESIZE_INCREMENT 3
/** @} */ // end of task_management_config



/**
 * @def make_sleep(task)
 * @brief Put task into sleep mode
 * @param task Pointer to task structure
 */
#define make_sleep(task) (task->isReady = 0)


/**
 * @def wake(task)
 * @brief Wake up a sleeping task
 * @param task Pointer to task structure
 */
#define wake(task) (task->isReady = 1)



/**
 * @def GET_CURRENT()
 * @brief Retrieve currently running task
 * @return Pointer to current task
 */
#define GET_CURRENT() current


/**
 * @def GET_TASKS_ARR(numOfArr)
 * @brief Get task queue for specific priority
 * @param numOfArr Priority level (0 = highest)
 * @return Pointer to task array
 */
#define GET_TASKS_ARR(numOfArr) queue[numOfArr]


/**
 * @def GET_TASKS_ARR_SIZE(numOfArr)
 * @brief Get size of task queue for priority
 * @param numOfArr Priority level
 * @return Current queue size
 */
#define GET_TASKS_ARR_SIZE(numOfArr) queueSize[numOfArr]


/**
 * @def GET_TASKS_ARR_RESERVED(numOfArr)
 * @brief Get reserved queue size for priority
 * @param numOfArr Priority level
 * @return Reserved queue size
 */
#define GET_TASKS_ARR_RESERVED(numOfArr) reservedQueueSize[numOfArr]



/**
 * @brief Change task priority
 * @param task Task pointer to modify
 * @param prior New priority level (0-5)
 * @return 0 on success, error code otherwise
 */
uint8_t change_prior(struct sTask *task, uint8_t prior);


/**
 * @brief Deallocate task resources
 * @param task Task pointer to free
 */
void free_sTask(struct sTask *task);


/**
 * @brief Create new task
 * @param task Handler function pointer
 * @param args Task arguments
 * @param prior Priority level (0-5)
 * @param stackPointer Stack memory pointer
 * @param stackSize Stack size in bytes
 * @param quant Time quantum
 * @return Pointer to created task or NULL
 */
struct sTask *create_sTask(
    void (*task)(uint32_t *),
    uint32_t *args,
    uint8_t prior,
    uint32_t *stackPointer,
    uint32_t stackSize,
    uint8_t quant
);



/**
 * @brief Function that starts when task is ended before time quantum
 */
void sExit(void);


/**
 * @brief Empty cycle process
 * @details Infinite sleep-loop process
 */
void null_process(void);


// @} // end of task_managment


#endif // __TASKMANAGEMENT_H__