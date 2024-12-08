#include "TaskManagment.h"
#include "TaskScheduler.h"
#include <stdlib.h>
#include "CPUDriver.h"
#include "TaskDelay.h"

struct STask * current;
struct STask ** queue[PRIOR_LEVELS];
uint8_t queueSize[PRIOR_LEVELS];
uint8_t reservedQueueSize[PRIOR_LEVELS];

		


//inline struct STask * get_current()
//{
//	return current;
//}

//inline void set_current(struct STask * task)
//{
//		current = task;
//}

//inline struct STask *** get_tasksQueue() {return queue;}

//inline void set_taskQueue(STask *** arr){queue = arr;}

//inline uint8_t * get_tasksSize() {return queueSize;}

//inline void set_taskSize(uint8_t * sz){ queueSize =sz;}

//inline uint8_t * get_tasksReserved() {return  reservedQueueSize;}

//inline void set_tasksReserved(uint8_t * sz){return reservedQueueSize = sz;}

uint8_t change_prior(struct STask * task, uint8_t prior)
{
    if(prior > PRIOR_LEVELS || prior <0) return 0;
    task->prior = prior;
    return 1;
}


struct STask * create_STask(void (*task)(uint32_t *),uint32_t * args ,uint8_t prior, uint32_t *stackPointer, uint32_t stackSize, uint8_t quant)
{

		uint32_t * updatedPointer = stackPointer+(((stackSize/sizeof(uint32_t *))-2));
    if(reservedQueueSize[prior]== 0)
    {
        uint8_t newSize = RESIZE_INCREMENT + queueSize[prior];

        struct STask** newQueue = (struct STask**)malloc(newSize * sizeof(struct STask *));
        
        if(newQueue == NULL) {
            return 0;
        }

        for (int i = 0; i < queueSize[prior]; i++) {
            newQueue[i] = queue[prior][i];
						queue[prior][i] = NULL;
        }

        free(queue[prior]);

        queue[prior] = newQueue;
        reservedQueueSize[prior] = RESIZE_INCREMENT;
    }
    struct STask  * newSTask = (struct STask *)malloc(sizeof(struct STask));
		if(newSTask ==  NULL) 
		{
			return 0;
		}
    newSTask->task = task;
    newSTask->args = args;
    newSTask->stackPointer = updatedPointer;
		newSTask->topStack = updatedPointer;
    newSTask->stackSize = stackSize;
    newSTask->prior = prior;
    newSTask->delayTime = 0;
		newSTask->isComplete = 1;
		newSTask->isReady = 1;
		newSTask->quant = quant;
    queue[prior][queueSize[prior]] = newSTask;
    queueSize[prior]+=1;
    if(!new_onDelay(newSTask)) return 0;
    reservedQueueSize[prior]-=1;
    create_new_context(newSTask->topStack, task, args);
    return newSTask;
}

void free_task(struct STask* task)
{
    task->isReady = 0;

    for(uint8_t i = 0; i < queueSize[task->prior]; i++)
    {
        if((queue[task->prior])[i] == task)
        {
            (queue[task->prior])[i] = 0;
            queueSize[task->prior]--;
            reservedQueueSize[task->prior]++;
            break;
        }
    }
    for(uint8_t i =0; i < reservedQueueSize[task->prior]-1; i++)
    {
        if(queue[task->prior] == 0)
        {    
            queue[task->prior][i] = queue[task->prior][i+1];
        }    
    }
		free_onDelay(task);
    free(task->stackPointer);
    free(task->task);
    free(task);

}

void sExit()
{
	disable_mainTimer();
	disable_irq();
	current->isComplete = 1;
	Schedule();
	enable_irq();
	enable_mainTimer();
	null_process();
}



void null_process()
{
  	while(1);
}
