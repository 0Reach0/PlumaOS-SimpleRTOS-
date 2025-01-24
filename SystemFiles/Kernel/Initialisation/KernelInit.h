/** @file KernelInit.h
 *  @brief Kernel initialization and startup routines
 *  @author 0Reach0
 *  @date 2025
 */

 
#ifndef __KERNELINIT_H__
#define __KERNELINIT_H__


/**
 * @defgroup kernel_start_and_init Kernel Initialization and Startup
 * @brief Enable/disable system features
 * @{
 */


/**
 * @brief Starts the kernel and begins task execution.
 * @details This function initializes the kernel scheduler and starts executing tasks.
 * It should be called after the kernel has been properly initialized using `init_kernel()`.
 */
void start_kernel(void);

/**
 * @brief Initializes the kernel and its components.
 * @details This function sets up the kernel environment, including memory allocation, 
 * task queues, and other necessary data structures. It must be called before `start_kernel()`.
 * @return 0 on success, otherwise an error code.
 */
uint8_t init_kernel(void);

/** @} */ // end of kernel_start_and_init
#endif