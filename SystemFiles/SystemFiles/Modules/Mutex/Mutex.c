#include "Mutex.h"

#ifdef MUTEX


void locK_mutex(sMutex m)
{
    while(m)
    {
        Schedule();
    }
    m = true;
}



#endif