#include "Timer.h"


#ifdef TIMER

#include <stdlib.h>
#include "TaskScheduler.h"



uint8_t timersArrayReservedSize = DEFAULT_RESERVED_ACTIVE_TIMERS_SIZE;
uint8_t timersArraySize = 0;

struct Timer ** activeTimersArray;

void process_timers(uint32_t dec)
{				
		    for(uint8_t i =0; i < timersArraySize ; i++)
				{
				if(!(activeTimersArray[i]->isStoped) && (activeTimersArray[i]->remainTicks != 0 || activeTimersArray[i]->remainSubTicks != 0))
        {
					  if(dec >= activeTimersArray[i]->remainSubTicks)
						{
							if(activeTimersArray[i]->remainTicks  == 0)
							{	
								activeTimersArray[i]->callBack();
								activeTimersArray[i]->remainTicks= 0;
								activeTimersArray[i]->remainSubTicks = 0;
								activeTimersArray[i]->isStoped = 1;
							}
							else{
								dec-=activeTimersArray[i]->remainSubTicks;
								activeTimersArray[i]->remainTicks-=1;
								activeTimersArray[i]->remainSubTicks = TIME_TICK_VAL - dec;
								if(activeTimersArray[i]->remainSubTicks== 0)
								{
									activeTimersArray[i]->isStoped = 1;
								}
							}
							}
						else
						{	
							activeTimersArray[i]->remainSubTicks-=dec;
						}			
        }
    }
}



uint8_t set_timer(struct Timer * t, uint32_t ticks, void (*callBack)())
{
     if(timersArrayReservedSize == 0)
    {
        uint8_t newSize = TIMER_RESIZE_INCREMENT+ timersArraySize;
        struct Timer ** newArray = (struct Timer**)malloc(newSize * sizeof(struct Timer*));
        if(newArray == 0) return  0;
        for(int i  = 0; i < timersArraySize; i++)
        {
            newArray[i] = activeTimersArray[i];
        }

        free(activeTimersArray);
        activeTimersArray = newArray;
        timersArrayReservedSize= newSize;

    }

    t->remainTicks = ticks;
    t->callBack = callBack;
    t->isStoped = 1;
    activeTimersArray[timersArraySize] = t;
    timersArraySize++; 
    return 1;
}

    

uint8_t remove_timer(struct Timer * t)
{
    for(uint8_t i = 0; i < timersArraySize; i++)
    {
        if(activeTimersArray[i] == t)
        {
            free(activeTimersArray[i]);
            activeTimersArray[i] = 0;
            for(uint8_t t = 0; t < timersArraySize-1; i ++)
            {
                if(activeTimersArray[t] == 0){
                    activeTimersArray[i] = activeTimersArray[i+1]; }
            }
            timersArrayReservedSize++;
            timersArraySize--;
            return 0;
        }
        return 1;
    }
}

void reset_timer(struct Timer *timer, uint32_t ticks){
	timer->remainTicks= ticks/TIME_TICK_VAL;
	timer->remainSubTicks = ticks%TIME_TICK_VAL;
}


void reset_long_timer(struct Timer* timer, uint32_t ticks, uint32_t subTicks){
	timer->remainTicks = ticks;
	timer->remainSubTicks = subTicks;
}

#endif