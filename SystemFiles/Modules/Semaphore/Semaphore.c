#include "Semaphore.h"


#ifdef SEMAPHORE
#include "Kernel.h"


void up(struct sSemaphore * sem)
{
    while(sem->current >= sem->max)
    {
        Schedule();
    }  
    sem->current++;
}

#endif