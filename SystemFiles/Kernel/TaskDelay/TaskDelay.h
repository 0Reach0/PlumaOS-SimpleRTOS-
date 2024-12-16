#ifndef __TASKDELAY_H__
#define __TASKDELAY_H__
#include <stdint.h>

#define RESERVED_ON_DELAY_SIZE 2

#define DELAY_RESIZE_INCREMENT      3


#define GET_DELAY_ARR sDelayArr

#define GET_DELAY_SIZE sDelaySize

#define GET_DELAY_RESERVED sDelayReserved


struct sTask;

extern struct sTask ** sDelayArr;

extern uint8_t sDelaySize;

extern uint8_t sDelayReserved;





void sDelay(uint32_t ticks);

void sLongDelay(uint32_t ticks, uint32_t subTicks);

uint8_t new_sDelay(struct sTask * task);

void free_sDelay(struct sTask* task);

void process_delays(uint32_t dec);
#endif