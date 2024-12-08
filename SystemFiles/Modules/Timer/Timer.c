#include "Timer.h"


#ifdef TIMER

#include <stdlib.h>
#include "TaskScheduler.h"



uint8_t timersArrayReservedSize = DEFAULT_RESERVED_ACTIVE_TIMERS_SIZE;
uint8_t timersArraySize = 0;

struct Timer ** activeTimersArray ;

void process_timers(uint32_t dec)
{
    uint8_t isEdited = 0;
    for(uint8_t i =0; i < timersArraySize ; i++)
    {
        if(activeTimersArray[i]->remainTicks > 0 && !(activeTimersArray[i]->isStoped))
        {
            if(activeTimersArray[i]->remainTicks<= dec)
            {
               activeTimersArray[i]->callBack();
               free(activeTimersArray[i]);
               isEdited = 1;  
               timersArraySize--;
               timersArrayReservedSize++;
							activeTimersArray[i]->remainTicks= 0;
							continue;
            }
						activeTimersArray[i]->remainTicks-= dec;
        }
    }
    if(isEdited == 1)
    {
        for(uint8_t i =0; i < timersArrayReservedSize-1 ; i++)
        {
            if(activeTimersArray[i] == 0)
            {
                activeTimersArray[i] = activeTimersArray[i+1];
            }
        }
    }
    return;
}



uint8_t set_timer(struct Timer * t, uint32_t c, void (*callBack)())
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

    t->remainTicks = c *QUANT_MULTIPLIER ;
    t->callBack = callBack;
    t->isStoped = 0;
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



#endif