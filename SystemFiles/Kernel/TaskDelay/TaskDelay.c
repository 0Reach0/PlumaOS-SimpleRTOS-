#include "TaskDelay.h"
#include "sTask.h"
#include "TaskManagment.h"
#include "TaskScheduler.h"
#include <stdlib.h>


struct sTask ** sDelayArr;

uint8_t sDelaySize = 0;
uint8_t sDelayReserved = 0;


void sLongDelay(uint32_t ticks, uint32_t subTicks)
{
	  current->delayTicks = ticks;
		current->delaySubTicks = subTicks;
		current->isReady = 0;
		current->isComplete = 1;
                Schedule();
                while(!current->isReady);
}


void sDelay(uint32_t ticks)
{   
		current->delayTicks = ticks / TIME_TICK_VAL ;
		current->delaySubTicks = ticks % TIME_TICK_VAL;
		current->isReady = 0;
		current->isComplete = 1;
		Schedule();
                while(!current->isReady);
}

uint8_t new_sDelay(struct sTask * task)
{
		if(sDelayReserved <= 0)
		{
				uint8_t newSize = sDelaySize+DELAY_RESIZE_INCREMENT;
				struct sTask** newQueue = (struct sTask**)malloc(newSize * sizeof(struct sTask*));
				if(newQueue == NULL)
				{
						return 0;
				}
				for (int i = 0; i < sDelaySize; i++) {
						newQueue[i] = sDelayArr[i];
						sDelayArr[i] = NULL;
        }
				free(sDelayArr);
				sDelayReserved+=DELAY_RESIZE_INCREMENT;
				sDelayArr = newQueue;
			}
			sDelayArr[sDelaySize] = task;
			sDelaySize++;    
			sDelayReserved--;
                        return 1;
}


void free_sDelay(struct sTask * task)
{
	    for(uint8_t i = 0; i < sDelaySize-1; i++)
			{
        if(sDelayArr[i] == task)
        {
            sDelayArr[i] = 0;
						break;
        }
			}
			
			for(uint8_t i = 0; i < sDelaySize-1; i++)
			{
					if(sDelayArr[i] == 0 && i != sDelaySize-2)
					{
							sDelayArr[i] = sDelayArr[i+1];
							sDelayArr[i+1] = 0;
					}
			}
}

void process_delays(uint32_t dec)
{
    for(uint8_t i =0; i < sDelaySize; i++)
    {
				if(!sDelayArr[i]->isReady && (sDelayArr[i]->delayTicks != 0 || sDelayArr[i]->delaySubTicks != 0))
        {
					  if(dec >= sDelayArr[i]->delaySubTicks)
						{
								if(sDelayArr[i]->delayTicks  == 0)
								{	
									sDelayArr[i]->delayTicks= 0;
									sDelayArr[i]->delaySubTicks = 0;
									sDelayArr[i]->isReady = 1;
                                                                        continue;
								}
								else{
									dec-=sDelayArr[i]->delaySubTicks;
									sDelayArr[i]->delayTicks-=1;
									sDelayArr[i]->delaySubTicks = TIME_TICK_VAL - dec;
									if(sDelayArr[i]->delaySubTicks == 0)
									{
                                                                            sDelayArr[i]->isReady = 1;
									}
								}
							}
						else
						{	
							sDelayArr[i]->delaySubTicks-=dec;
						}	
        }
    }
}

