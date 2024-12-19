#ifndef __TASKDELAY_H__
#define __TASKDELAY_H__
#include <stdint.h>

#define RESERVED_ON_DELAY_SIZE 2

#define DELAY_RESIZE_INCREMENT      3


#define GET_DELAY_ARR onDelayArr

#define GET_DELAY_SIZE onDelaySize

#define GET_DELAY_RESERVED onDelayReserved


struct STask;

extern struct STask ** onDelayArr;

extern uint8_t onDelaySize;

extern uint8_t onDelayReserved;

//struct STask ** get_onDelayArr();

//inline void set_onDelayArr(struct STask ** arr);

//inline uint8_t get_onDelaySize();

//inline void set_onDelaySize(uint8_t sz);

void sDelay(uint32_t c);

void sLongDelay(uint32_t ticks, uint32_t subTicks);

uint8_t new_onDelay(struct STask * task);


void free_onDelay(struct STask* task);

void process_delays(uint32_t dec);
#endif