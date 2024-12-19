#ifndef __TIMER_H__
#define __TIMER_H__
#include "PlumaConfig.h"


#ifdef TIMER

#include <stdint.h>

struct STask;

#define DEFAULT_RESERVED_ACTIVE_TIMERS_SIZE 2
#define TIMERS_INTERRUPT_INTERVAL_TICKS 0x00FFFFFF 
#define TIMER_RESIZE_INCREMENT 2



#define stop_timer(timer) timer->isStoped = 1;

#define resume_timer(timer) timer->isStoped = 0;

extern uint8_t timersArrayReservedSize;
extern uint8_t timersArraySize;
extern struct Timer ** activeTimersArray ;


		
		


struct Timer
{
    uint32_t remainTicks;
		uint32_t remainSubTicks;
    void (*callBack)();
    uint8_t isStoped; 
};




uint8_t set_timer(struct Timer *, uint32_t,void (*callBack)());

void reset_timer(struct Timer* timer, uint32_t ticks);

void reset_long_timer(struct Timer *timer, uint32_t ticks, uint32_t subTicks);

uint8_t remove_timer(struct Timer *);

void process_timers(uint32_t dec);

#endif

#endif

