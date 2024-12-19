#include "TaskDelay.h"
#include "STask.h"
#include "TaskManagment.h"
#include "TaskScheduler.h"
#include <stdlib.h>


struct STask ** onDelayArr;

uint8_t onDelaySize = 0;
uint8_t onDelayReserved = 0;


void sLongDelay(uint32_t ticks, uint32_t subTicks)
{
	  current->delayTicks = ticks;
		current->delaySubTicks = subTicks;
		current->isReady = 0;
	current->isComplete = 1;
    Schedule();
}


void sDelay(uint32_t ticks)
{   
		current->delayTicks = ticks / TIME_TICK_VAL ;
		current->delaySubTicks = ticks % TIME_TICK_VAL;
		current->isReady = 0;
		current->isComplete = 1;
		Schedule();
}

uint8_t new_onDelay(struct STask * task)
{
		if(onDelayReserved <= 0)
		{
				uint8_t newSize = onDelaySize+DELAY_RESIZE_INCREMENT;
				struct STask** newQueue = (struct STask**)malloc(newSize * sizeof(struct STask*));
				if(newQueue == NULL)
				{
						return 0;
				}
				for (int i = 0; i < onDelaySize; i++) {
						newQueue[i] = onDelayArr[i];
						onDelayArr[i] = NULL;
        }
				free(onDelayArr);
				onDelayReserved+=DELAY_RESIZE_INCREMENT;
				onDelayArr = newQueue;
			}
			onDelayArr[onDelaySize] = task;
			onDelaySize++;    
			onDelayReserved--;
}


void free_onDelay(struct STask * task)
{
	    for(uint8_t i = 0; i < onDelaySize-1; i++)
    {
        if(onDelayArr[i] == task)
        {
            onDelayArr[i] = 0;
						if(onDelayArr[i] == 0 && i != onDelaySize-1)
						{
							onDelayArr[i] = onDelayArr[i+1];
						}
						return;
        }
    }
}

void process_delays(uint32_t dec)
{
    for(uint8_t i =0; i < onDelaySize; i++)
    {
				if(!onDelayArr[i]->isReady && (onDelayArr[i]->delayTicks != 0 || onDelayArr[i]->delaySubTicks != 0))
        {
					  if(dec >= onDelayArr[i]->delaySubTicks)
						{
							if(onDelayArr[i]->delayTicks  == 0)
							{	
								onDelayArr[i]->delayTicks= 0;
								onDelayArr[i]->delaySubTicks = 0;
								onDelayArr[i]->isReady = 1;
							}
							else{
								dec-=onDelayArr[i]->delaySubTicks;
								onDelayArr[i]->delayTicks-=1;
								onDelayArr[i]->delaySubTicks = TIME_TICK_VAL - dec;
								if(onDelayArr[i]->delaySubTicks == 0)
								{
									onDelayArr[i]->isReady = 1;
								}
							}
							}
						else
						{	
							onDelayArr[i]->delaySubTicks-=dec;
						}
						
        }
    }
}

