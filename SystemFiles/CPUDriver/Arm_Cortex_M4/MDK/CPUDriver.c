#include "CPUDriver.h"


volatile uint32_t *FPCCR = (volatile uint32_t *)0xE000EF34; 
volatile uint32_t *FPCAR = (volatile uint32_t *)0xE000EF38; 					

			

#ifdef USE_SYSTICK_TIMER_AS_MAIN

volatile uint32_t * MTIM_ADDR =(volatile uint32_t *) 0xE000E010;
volatile uint32_t * SYS_CSR = (volatile uint32_t *)0xE000E010;
volatile uint32_t* SYS_RVR = (volatile uint32_t*)0xE000E014;
volatile uint32_t* SYS_CVR = (volatile uint32_t*)0xE000E018;
uint8_t IS_FPU_USED = 0;


void set_main_RVR(uint32_t ticks)
    {
        if (ticks > 0x00FFFFFF)
        {
            ticks = 0x00FFFFFF;
        }

        uint32_t last_8_bits = 0xFF000000;

        *SYS_RVR = (*SYS_RVR & last_8_bits) | (ticks & 0x00FFFFFF);
        *SYS_CVR = (*SYS_CVR & last_8_bits) | (ticks & 0x00FFFFFF);
    }
		
	 #define disable_mainTimer() *SYS_CSR &= ~(1 << 1)

	 #define enable_mainTimer() *SYS_CSR |=  (1 << 1)
#endif
