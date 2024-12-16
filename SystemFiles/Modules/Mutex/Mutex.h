#ifndef __MUTEX_H__
#define __MUTEX_H__
#ifdef MUTEX

#include "Kernel.h"


#define sMutex uint8_t

#define unlock_mutex(sMutex)  sMutex = 0


void lock_mutex(sMutex m);


#endif

#endif
 
