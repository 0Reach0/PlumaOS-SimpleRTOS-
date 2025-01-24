/** @file Semaphore.h
 *  @brief Semaphore synchronization primitive implementation
 *  @author 0Reach0
 *  @date 2025
 */

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__


#include "PlumaConfig.h"


#ifdef SEMAPHORE


#include "stdint.h"


/*
 * @defgroup semaphore Semaphore
 * @{
 */


/**
 * @struct sSemaphore
 * @brief Counting semaphore structure
 * @details Implements classic Dijkstra semaphore with:
 * - Maximum allowed value
 * - Current available count
 */
struct sSemaphore {
    uint8_t max;     /**< Maximum allowed semaphore value */
    uint8_t current; /**< Current available semaphore count */
};



/**
 * @def down(sSemaphore)
 * @brief Acquire semaphore (decrement count)
 * @param sSemaphore Pointer to semaphore instance
 * @warning Does not block - caller must check count
 */
#define down(sSemaphore) (sSemaphore)->current--



/**
 * @brief Release semaphore (increment count)
 * @param sem Pointer to semaphore instance
 * @details Ensures count never exceeds maximum:
 * @code
 * if(sem->current < sem->max) sem->current++;
 * @endcode
 */
void up(struct sSemaphore *sem);

// /** @} */ // end of semaphore


#endif // SEMAPHORE


#endif // __SEMAPHORE_H__

