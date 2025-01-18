#include "TaskManagment.h"
#include "TaskScheduler.h"
#include <stdlib.h>
#include "CPUDriver.h"
#include "TaskDelay.h"

struct sTask * current;
struct sTask ** queue[PRIOR_LEVELS];
uint8_t queueSize[PRIOR_LEVELS];
uint8_t reservedQueueSize[PRIOR_LEVELS];


uint8_t change_prior(struct sTask * task, uint8_t prior)
{
    if(prior > PRIOR_LEVELS) return 0;
    task->prior = prior;
    return 1;
}


struct sTask * create_sTask(void (*task)(uint32_t *),uint32_t * args ,uint8_t prior, uint32_t *stackPointer, uint32_t stackSize, uint8_t quant)
{
	uint32_t * updatedPointer = stackPointer+(((stackSize/sizeof(uint32_t *))-1));
    if(reservedQueueSize[prior]== 0)
    {
        uint8_t newSize = TASK_RESIZE_INCREMENT + queueSize[prior];

        struct sTask** newQueue = (struct sTask**)malloc(newSize * sizeof(struct sTask *));
        
        if(newQueue == NULL) {
            return 0;
        }

        for (int i = 0; i < queueSize[prior]; i++) {
            newQueue[i] = queue[prior][i];
						queue[prior][i] = NULL;
        }

        free(queue[prior]);

        queue[prior] = newQueue;
        reservedQueueSize[prior] =TASK_RESIZE_INCREMENT;
    }
    struct sTask  * newsTask = (struct sTask *)malloc(sizeof(struct sTask));
		if(newsTask ==  NULL) 
		{
				return 0;
		}
    newsTask->task = task;
    newsTask->args = args;
    newsTask->defStackPointer = stackPointer;
    newsTask->stackPointer = updatedPointer;
		newsTask->topStack = updatedPointer;
    newsTask->stackSize = stackSize;
    newsTask->prior = prior;
    newsTask->delayTicks = 0;
		newsTask->delaySubTicks = 0;
		newsTask->isComplete = 0;
		newsTask->isReady = 1;
		newsTask->quant = quant * QUANT_MULTIPLIER;
		newsTask->remainQuant = quant * QUANT_MULTIPLIER;
    if(!new_sDelay(newsTask))
		{
				free(newsTask);
				return 0;
		}
		queue[prior][queueSize[prior]] = newsTask;
    queueSize[prior]+=1;
    reservedQueueSize[prior]-=1;
    create_new_context(&newsTask->topStack, task, args);
    return newsTask;
}

void free_sTask(struct sTask* task)
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
    for(uint8_t i =0; i < reservedQueueSize[task->prior]-2; i++)
    {
        if(queue[task->prior] == 0)
        {    
            queue[task->prior][i] = queue[task->prior][i+1];
						queue[task->prior][i+1] = 0;
        }    
    }
		free_sDelay(task);
    free(task->stackPointer);

    free(task);
}

void sExit(void)
{
	disable_mainTimer();
	disable_irq();
	current->isComplete = 1;
	enable_irq();
	enable_mainTimer();
	Schedule();
	null_process();
}



void null_process(void)
{
  	while(1);
}
