/** @file Mutex.h
 *  @brief Mutex synchronization primitive implementation
 *  @author 0Reach0
 *  @date 2025
 */

#ifndef __MUTEX_H__
#define __MUTEX_H__


#include "PlumaConfig.h"

#ifdef MUTEX


#include "Kernel.h"


/*
* @defgroup mutex Mutex
* @{
*/


/**
 * @def sMutex
 * @brief Mutex type definition
 * @details Simple binary mutex implementation using uint8_t:
 * - 0: Unlocked/free state
 * - 1: Locked/acquired state
 */
#define sMutex uint8_t



/**
 * @def unlock_mutex(sMutex)
 * @brief Release a locked mutex
 * @param sMutex Mutex to unlock (must be previously locked)
 */
#define unlock_mutex(sMutex) (sMutex = 0)


/**
 * @brief Acquire a mutex lock
 * @param m Mutex to lock
 * @details Implementation-defined locking behavior:
 * - Busy-wait spins until mutex available
 * - No priority inheritance support
 * - Not recursive/reentrant
 */
void locK_mutex(sMutex m);

// /** @} */ // end of mutex


#endif // MUTEX


#endif // __MUTEX_H__