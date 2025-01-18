#include "Mutex.h"

#ifdef MUTEX


void lock_mutex(sMutex m)
{
    while(m)
    {
        Schedule();
    }
    m = true;
}



#endif