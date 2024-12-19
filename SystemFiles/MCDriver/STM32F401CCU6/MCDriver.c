#include "STask.H"
#include "MCDriver.h"
#include <stdint.h>
#include "PlumaConfig.h"

volatile uint32_t MTIM_ADDR; //ADRESS OF MAIN TIMER

uint32_t ms_to_ticks(uint32_t ms)
{
    uint32_t res = ((ms *PROCESSOR_FREQUENCY)/1000);
    return (res > 0xFFFFFFFF)? 0xFFFFFFFF : res;
}


#ifdef  USE_TIMER_1_AS_MAIN

		#define TIM1_ADDR  0x40010000
		MTIM_ADDR = (volatile uint32_t *)TIM1_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM1_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM1_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM1_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM1_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM1_ADDR 0x24;

		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
		 
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif



#ifdef  USE_TIMER_2_AS_MAIN
    #define TIM2_ADDR  0x40000000
		MTIM_ADDR = (volatile uint32_t *)TIM2_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM2_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM2_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM2_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM2_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM2_ADDR 0x24;
		
		
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
    
		
		inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFFFFFF) ticks = 0xFFFFFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFFFFFF);
        (*ARR) |= ((ticks & 0xFFFFFFFF));


        (*CNT) &= ~(0xFFFFFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;

    }
#endif



#ifdef  USE_TIMER_3_AS_MAIN
    #define TIM3_ADDR  0x4000 0400
		MTIM_ADDR = (volatile uint32_t *)TIM3_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM3_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM3_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM3_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM3_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM3_ADDR 0x24;
				
		
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
    
		
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif
    


#ifdef  USE_TIMER_4_AS_MAIN
    #define TIM4_ADDR  0x40000800
		MTIM_ADDR = (volatile uint32_t *)TIM4_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM4_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM4_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM4_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM4_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM4_ADDR 0x24;
				
		
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
    
		
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif



#ifdef  USE_TIMER_5_AS_MAIN
    #define TIM5_ADDR  0x40000C00
		MTIM_ADDR = (volatile uint32_t *)TIM5_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM4_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM4_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM4_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM4_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM4_ADDR 0x24;
				
		
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
    
		
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif



#ifdef  USE_TIMER_9_AS_MAIN
    #define TIM9_ADDR  0x40014000
		MTIM_ADDR = (volatile uint32_t *)TIM9_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM9_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM9_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM9_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM9_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM9_ADDR 0x24;
						
		
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
    
		
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif



#ifdef  USE_TIMER_10_AS_MAIN    
    #define TIM10_ADDR 0x40014400
		MTIM_ADDR = (volatile uint32_t *)TIM10_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM10_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM10_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM10_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM10_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM10_ADDR 0x24;
						
		
		#define disable_mainTimer() *MTIM_ADDR &= ~(1 << 0);	

		#define enable_mainTimer() *MTIM_ADDR |=  (1 << 0);
    
		
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif



#ifdef  USE_TIMER_11_AS_MAIN
    #define TIM11_ADDR 0x40014800
		MTIM_ADDR = (volatile uint32_t *)TIM11_ADDR;
    volatile  uint32_t  * ARR = (volatile uint32_t *)TIM11_ADDR + 0x2C;
    volatile  uint32_t  *DIER = (volatile uint32_t *)TIM11_ADDR + 0x0C;
    volatile  uint32_t  *SR=  (volatile uint32_t *)TIM11_ADDR + 0x10;
    volatile  uint32_t * CR1 = (volatile uint32_t *)TIM11_ADDR + 0x0;
    volatile uint32_t * CNT =  (volatile uint32_t *)TIM11_ADDR 0x24;
    
		
    inline void set_main_RVR(uint32_t ticks)
    {

        if(ticks > 0xFFFF) ticks = 0xFFFF; 
        (*CR1) &= 0 << 0;


        (*ARR) &= ~(0xFFFF);
        (*ARR) |= ((ticks & 0xFFFF));

        (*CNT) &= ~(0xFFFF);


        (*DIER) &= 0 << 0;

        (*SR) &= 0 <<0

        (*CR1) |= 1 << 0;
    }
#endif
