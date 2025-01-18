#ifndef __HARDWAREMKLAYER_H__
#define __HARDWAREMKLAYER_H__
#include <stdint.h>


#define TIM1_ADDR  0x40010000
#define TIM2_ADDR  0x40000000
#define TIM3_ADDR  0x4000 0400
#define TIM4_ADDR  0x40000800
#define TIM5_ADDR  0x40000C00
#define TIM9_ADDR  0x40014000 
#define TIM10_ADDR 0x40014400 
#define TIM11_ADDR 0x40014800

#ifndef USE_SYSTICK_TIMER_AS_MAIN
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
#endif



extern volatile uint32_t * MTIM_ADDR;


void set_main_RVR(uint32_t ticks);   //using to set main timer reload value



uint32_t ms_to_ticks(uint32_t ms);


#endif
