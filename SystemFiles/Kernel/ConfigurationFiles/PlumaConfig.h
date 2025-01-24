/** @file config.h
 *  @brief System configuration constants and feature flags
 *  @author 0Reach0
 *  @date 2025
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

/**
 * @defgroup config Configuration
 * @brief System configuration constants and feature flags
 * @{
 */




/**
 * @defgroup hardware_config Hardware Configuration
 * @brief Hardware specific configuration
 * @{
 */

/**
 * @def PROCESSOR_FREQUENCY
 * @brief Processor operating frequency in Hz
 */
#define PROCESSOR_FREQUENCY 84000000

/**
 * @def TIME_TICK_VAL
 * @brief Maximum value for system tick counter
 */
#define TIME_TICK_VAL 16777215

/**
 * @def MAIN_RVR
 * @brief Main timer reload value
 */
#define MAIN_RVR 16777215

/** @} */ // end of hardware_config

/**
 * @defgroup aditional_modules Aditional Modules
 * @brief Enable/disable system features
 * @{
 */

/**
 * @def SEMAPHORE
 * @brief Enable semaphore synchronization primitive
 */
#define SEMAPHORE

/**
 * @def MUTEX
 * @brief Enable mutex synchronization primitive
 */
#define MUTEX

/**
 * @def TIMER
 * @brief Enable timer management subsystem
 */
#define TIMER

/**
 * @def QUEUE_MESSAGES
 * @brief Enable message queue functionality
 */
#define QUEUE_MESSAGES

/** @} */ // end of aditional_modules

/**
 * @defgroup main_timer_config MainTimer Configuration
 * @brief Choose some timer as main system timer(which will be used for task scheduling)
 * @note Uncomment only one timer option below
 * @{
 */




/*! @name Available main timer options
 *  @brief Select primary system timer by uncommenting one
 *
*@{
*/
#define USE_SYSTICK_TIMER_AS_MAIN ///< Use SysTick timer as main
 //#define USE_TIMER_1_AS_MAIN  ///< Use Timer 1 as main
 //#define USE_TIMER_2_AS_MAIN  ///< Use Timer 2 as main
 //#define USE_TIMER_3_AS_MAIN  ///< Use Timer 3 as main
 //#define USE_TIMER_4_AS_MAIN  ///< Use Timer 4 as main
 //#define USE_TIMER_5_AS_MAIN  ///< Use Timer 5 as main
 //#define USE_TIMER_6_AS_MAIN  ///< Use Timer 6 as main
 //#define USE_TIMER_7_AS_MAIN  ///< Use Timer 7 as main
 //#define USE_TIMER_8_AS_MAIN  ///< Use Timer 8 as main
 //#define USE_TIMER_9_AS_MAIN  ///< Use Timer 9 as main
 //#define USE_TIMER_10_AS_MAIN ///< Use Timer 10 as main
 //#define USE_TIMER_11_AS_MAIN ///< Use Timer 11 as main
///@}

/** @} */ // end of main_timer_config

/**
 * @defgroup arch_defines Architecture Definitions
 * @brief Processor architecture identifiers
 * @{
 */

/**
 * @def ARM_V7
 * @brief ARMv7 architecture identifier
 */
#define ARM_V7 0x01

/**
 * @def ARM_V8
 * @brief ARMv8 architecture identifier
 */
//#define ARM_V8 0x02

/**
 * @def Xtensa_LX6
 * @brief Xtensa LX6 architecture identifier
 */
//#define Xtensa_LX6 0x03

/** @} */ // end of arch_defines



/** @} */ // end of config


#endif // __CONFIG_H__