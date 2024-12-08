#ifndef __TIMER_H__
#define __TIMER_H__
#include "PlumaConfig.h"


#ifdef TIMER

#include <stdint.h>

struct STask;

#define DEFAULT_RESERVED_ACTIVE_TIMERS_SIZE 2
#define TIMERS_INTERRUPT_INTERVAL_TICKS 0x00FFFFFF 
#define TIMER_RESIZE_INCREMENT 2


#define reset_timer(timer, counter) timer->remainTicks = counter

#define stop_timer(timer) timer->isStoped = 1;

#define resume_timer(timer) timer->isStoped = 0;



#define TIMER_HANDLE                               \
     uint8_t isEdited = 0;													\
    for(uint8_t i =0; i < timersArraySize ; i++)			\
    {\
        if(activeTimersArray[i]->remainTicks > 0 && !(activeTimersArray[i]->isStoped))\
        {\
            if(activeTimersArray[i]->remainTicks<= dec)\
            {\
               activeTimersArray[i]->callBack();\
               free(activeTimersArray[i]);\
               isEdited = 1;  \
               timersArraySize--;\
               timersArrayReservedSize++;\
							activeTimersArray[i]->remainTicks= 0;\
							continue;\
            }\
						activeTimersArray[i]->remainTicks-= dec;\
        }\


		
		


struct Timer
{
    uint32_t remainTicks;
    void (*callBack)();
    uint8_t isStoped; 
};




uint8_t set_timer(struct Timer *, uint32_t,void (*callBack)());


uint8_t remove_timer(struct Timer *);

void process_timers(uint32_t dec);

#endif

#endif

