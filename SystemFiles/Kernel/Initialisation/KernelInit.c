#include "Kernel.h "
#include <stdint.h>
#include <stdlib.h>
#include "PlumaConfig.h"

#ifdef TIMER
		#include "Timer.h"
#endif


 void start_kernel() {
	set_active();
	Schedule()
	set_MSP(tempStack);
	while(1);
 }

uint8_t init_kernel()
{
	for(uint8_t i = 0; i < PRIOR_LEVELS;  i++)
	{
			queueSize[i] = 0;
			queue[i] = (struct STask **)malloc(DEFAULT_RESERVED_Q_SIZE * sizeof(struct STask *));
			if(queue[i] == NULL)
			{
					return 0;
			}
	}
	
		for(uint8_t i = 0; i < PRIOR_LEVELS;  i++)
		{
				reservedQueueSize[i] = DEFAULT_RESERVED_Q_SIZE;

		}
		
		
		tempStack = (uint32_t *)malloc(TEMP_STACK_SIZE);
		
	
		
		if (tempStack == NULL) {

			return 0;
		}
		
		
		tempStack +=(TEMP_STACK_SIZE/sizeof(uint32_t *))-1 ;
		
		
		onDelayArr = (struct STask **) malloc(RESERVED_ON_DELAY_SIZE *sizeof(struct STask *));
		
		
		
		if(onDelayArr == 0)
		{
			return 0;
		}
		
		#ifdef TIMER
					activeTimersArray = (struct Timer **)malloc(DEFAULT_RESERVED_ACTIVE_TIMERS_SIZE * sizeof(struct Timer *));
		
		
					if(activeTimersArray  == 0)
					{
							return 0;
					}
		#endif
}