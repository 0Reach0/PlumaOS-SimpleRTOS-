#ifndef __TASKDELAY_H__
#define __TASKDELAY_H__
#include <stdint.h>

#define RESERVED_ON_DELAY_SIZE 2

struct STask;

extern struct STask ** onDelayArr;

extern uint8_t onDelaySize;

//struct STask ** get_onDelayArr();

//inline void set_onDelayArr(struct STask ** arr);

//inline uint8_t get_onDelaySize();

//inline void set_onDelaySize(uint8_t sz);

void sDelay(uint32_t c);


uint8_t new_onDelay(struct STask * task);


void free_onDelay(struct STask* task);

void process_delays(uint32_t dec);
#endif