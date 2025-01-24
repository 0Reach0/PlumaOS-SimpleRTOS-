/** @file MCDriver.h
 *  @brief Hardware abstraction layer for timer peripherals
 *  @author 0Reach0
 *  @date 2025
 */
#ifndef __HARDWAREMKLAYER_H__
#define __HARDWAREMKLAYER_H__

#include <stdint.h>


/** 
 * @defgroup mcdriver Microcontroller Driver
 * @brief Hardware abstraction layer for timer peripherals
 * @{
 */




/**
 * @var MTIM_ADDR
 * @brief Main timer control register address
 * @details Volatile pointer to memory-mapped timer control register
 */
extern volatile uint32_t *MTIM_ADDR;



/**
 * @defgroup stm32f401ccu6_timers STM32F401CCU6 Timers
 * @brief Macros for STM32F401CCU6 timer peripherals
 * @{
 */

/** @brief Base address for Timer 1 */
#define TIM1_ADDR  0x40010000

/** @brief Base address for Timer 2 */
#define TIM2_ADDR  0x40000000

/** @brief Base address for Timer 3 */
#define TIM3_ADDR  0x40000400

/** @brief Base address for Timer 4 */
#define TIM4_ADDR  0x40000800

/** @brief Base address for Timer 5 */
#define TIM5_ADDR  0x40000C00

/** @brief Base address for Timer 9 */
#define TIM9_ADDR  0x40014000

/** @brief Base address for Timer 10 */
#define TIM10_ADDR 0x40014400

/** @brief Base address for Timer 11 */
#define TIM11_ADDR 0x40014800


/** @} */ // end of stm32f401ccu6_timers








/**
 * @brief Set timer reload value
 * @param ticks Reload value in hardware timer ticks
 */
void set_main_RVR(uint32_t ticks);

/**
 * @brief Convert milliseconds to timer ticks
 * @param ms Time value in milliseconds
 * @return Equivalent value in timer ticks
 * @note Uses PROCESSOR_FREQUENCY for conversion calculation
 */
uint32_t ms_to_ticks(uint32_t ms);


/** @} */ // end of mcdriver


#endif // __HARDWAREMKLAYER_H__