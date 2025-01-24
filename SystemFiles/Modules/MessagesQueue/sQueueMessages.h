/** @file sQueueMessages.h
 *  @brief Message queue implementation with task synchronization
 *  @author 0Reach0
 *  @date 2025
 */

#ifndef __SQUEUE_MESSAGES_H__
#define __SQUEUE_MESSAGES_H__


#include "PlumaConfig.h"


#ifdef QUEUE_MESSAGES


#include "PlumaConfig.h"
#include "sTask.h"
#include <stdint.h>



/** 
 * @defgroup squeuemessages Queue Messages
 * @brief Message queue implementation with task synchronization
 * @{
 */

/** @brief array of tasks waiting for messages or space */
extern QM_T_Pair ** taskWaitingQueues;

/** @brief Current number of delayed tasks */
extern uint8_t taskWaitingQueuesSize ;



/**
 * @defgroup queue_config Queue Configuration
 * @brief Message queue settings and constants
 * @{
 */



/** @brief Default reserved size for waiting queues */
#define WAITING_QUEUE_RESERVED_SIZE 2

/** @} */ // end of queue_config



/**
 * @def sQueueMessages_IsEmpty(sQueueMessages)
 * @brief Check if queue is empty
 * @param sQueueMessages Queue instance pointer
 * @return true if queue size == 0
 */
#define sQueueMessages_IsEmpty(sQueueMessages) ((sQueueMessages)->size == 0)


/**
 * @def sQueueMessages_IsFull(sQueueMessages)
 * @brief Check if queue is full
 * @param sQueueMessages Queue instance pointer
 * @return true if queue size >= capacity
 */
#define sQueueMessages_IsFull(sQueueMessages) ((sQueueMessages)->size >= (sQueueMessages)->capacity)


/**
 * @def sQueueMessages_IsMessageWait(sQueueMessages)
 * @brief Check for message waiters
 * @param sQueueMessages Queue instance pointer
 * @return true if tasks waiting for messages
 */
#define sQueueMessages_IsMessageWait(sQueueMessages) ((sQueueMessages)->messageWaitingArrSize > 0)


/**
 * @def sQueueMessages_IsSpaceWait(sQueueMessages)
 * @brief Check for space waiters
 * @param sQueueMessages Queue instance pointer
 * @return true if tasks waiting for space
 */
#define sQueueMessages_IsSpaceWait(sQueueMessages) ((sQueueMessages)->spaceWaitingArrSize > 0)



/**
 * @struct sQueueMessages
 * @brief Message queue with task synchronization
 * @details Implements circular buffer with:
 * - Producer/consumer synchronization
 * - Dynamic waiting queues
 * - Element size configuration
 */
struct sQueueMessages {
    uint8_t *queueArray;     /**< Circular buffer storage */
    uint8_t head;            /**< Buffer head index */
    uint8_t tail;            /**< Buffer tail index */
    uint8_t size;            /**< Current element count */
    uint8_t capacity;        /**< Maximum capacity */
    uint32_t elementSize;    /**< Size per element in bytes */

    struct sTask **spaceWaiting;     /**< Tasks waiting to enqueue */
    uint8_t spaceWaitingArrSize;     /**< Space waiters count */

    struct sTask **messageWaiting;   /**< Tasks waiting to dequeue */
    uint8_t messageWaitingArrSize;   /**< Message waiters count */
};




/**
 * @brief Initialize message queue
 * @param queue Queue instance to initialize
 * @param capacity Maximum elements in queue
 * @param elementSize Size of each element in bytes
 * @return 0 on success, error code otherwise
 * @note Allocates memory for buffer and waiting arrays
 */
uint8_t sQueueMessages_Init(struct sQueueMessages *queue, 
                           uint8_t capacity, 
                           uint32_t elementSize);


/**
 * @brief Destroy queue and release resources
 * @param queue Queue instance to destroy
 */
void freeQueue(struct sQueueMessages *queue);


/**
 * @brief Enqueue message with synchronization
 * @param q Queue instance
 * @param data Data to enqueue
 * @return 0 on success, error code otherwise
 * @warning Data buffer must match elementSize
 */
uint8_t sQueueMessages_Enqueue(struct sQueueMessages *q, uint8_t *data);


/**
 * @brief Dequeue message with synchronization
 * @param q Queue instance
 * @param data Buffer for dequeued data
 * @return 0 on success, error code otherwise
 * @warning Buffer must be pre-allocated for elementSize
 */
uint8_t sQueueMessages_Dequeue(struct sQueueMessages *q, uint8_t *data);


/**
 * @brief Register task as message waiter
 * @param queue Queue instance
 * @param task Task to register
 * @return 0 on success, error code otherwise
 */
uint8_t make_waiting_task_for_message(struct sQueueMessages *queue, 
                                    struct sTask *task);

/**
 * @brief Register task as space waiter
 * @param queue Queue instance
 * @param task Task to register
 * @return 0 on success, error code otherwise
 */
uint8_t make_waiting_task_for_space(struct sQueueMessages *queue, 
                                  struct sTask *task);

/**
 * @brief Wake tasks waiting for space
 * @param queue Queue instance
 * @note Called after dequeue operations
 */
void wake_space_waiting_tasks(struct sQueueMessages *queue);


/**
 * @brief Wake tasks waiting for messages
 * @param queue Queue instance
 * @note Called after enqueue operations
 */
void wake_message_waiting_tasks(struct sQueueMessages *queue);

// /** @} */ // end of squeuemessages




#endif // QUEUE_MESSAGES

#endif // __SQUEUE_MESSAGES_H__

