#include "CPUDriver.h"


uint32_t exc_return = 0;	
volatile uint32_t *FPCAR = (volatile uint32_t *)FPCAR_ADDRES; 					
volatile uint32_t * SYS_CSR = (volatile uint32_t *)0xE000E010;
volatile uint32_t* SYS_RVR = (volatile uint32_t*)0xE000E014;
volatile uint32_t* SYS_CVR = (volatile uint32_t*)0xE000E018;

void save_context_irq(volatile uint32_t ** sp)
	 { 								 
			if(exc_return & (0<<4)) save_full_context(FPCAR,sp);															
			else save_lazy_context(sp);		 
	} 
			

#ifdef USE_SYSTICK_TIMER_AS_MAIN

void postpone(uint32_t ticks)
    {
        if (ticks > 0x00FFFFFF)
        {
            ticks = 0x00FFFFFF;
        }

        uint32_t last_8_bits = 0xFF000000;

        *SYS_RVR = (*SYS_RVR & last_8_bits) | (ticks & 0x00FFFFFF);
				*SYS_CVR = (*SYS_CVR & last_8_bits) | (ticks & 0x00FFFFFF);
    }
#endif
