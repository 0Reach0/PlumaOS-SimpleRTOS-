#include "PlumaConfig.h"

#ifdef SEMAPHORE

#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__
#include "stdint.h"

#define down(sSemaphore) sem->current--

struct sSemaphore{
    uint8_t max;
    uint8_t current;
};

void up(struct sSemaphore *);


#endif

#endif