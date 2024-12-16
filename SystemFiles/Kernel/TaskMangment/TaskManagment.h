#ifndef __TASKMANAGMENT_H__
#define __TASKMANAGMENT_H__
#include <stdint.h>
#include "sTask.H"

#define POINTER_SIZE 32
#define PRIOR_LEVELS 6
#define DEFAULT_RESERVED_Q_SIZE 2
#define TASK_RESIZE_INCREMENT      3

#define make_sleep(task) task->isReady = 0

#define wake(task)  task->isReady = 1 


#define GET_CURRENT()  current

#define GET_TASKS_ARR(numOfArr) queue[numOfArr]

#define GET_TASKS_ARR_SIZE(numOfArr) queueSize[numOfArr]

#define GET_TASKS_ARR_RESERVED(numOfArr) reservedQueueSize[numOfArr]

extern struct sTask * current;
extern struct sTask ** queue[PRIOR_LEVELS];
extern uint8_t queueSize[PRIOR_LEVELS];
extern uint8_t reservedQueueSize[PRIOR_LEVELS];

uint8_t change_prior(struct sTask * task, uint8_t prior);

void sExit(void);    //Using as LR(return link) for tasks

void null_process(void);

void free_sTask(struct sTask* task);

struct sTask * create_sTask(void (*task)(uint32_t *),uint32_t * args ,uint8_t prior, uint32_t *stackPointer, uint32_t stackSize, uint8_t quant);


#endif
