#ifndef __HARDWAREMKLAYER_H__
#define __HARDWAREMKLAYER_H__
#include <stdint.h>

extern volatile uint32_t MTIM_ADDR;


#ifndef USE_SYSTICK_TIMER_AS_MAIN


 		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
			
			
#endif

void set_main_RVR(uint32_t);



uint32_t ms_to_ticks(uint32_t);


#endif
