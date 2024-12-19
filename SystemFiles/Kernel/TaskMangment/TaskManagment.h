#ifndef __TASKMANAGMENT_H__
#define __TASKMANAGMENT_H__
#include <stdint.h>
#include "STask.H"

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

extern struct STask * current;
extern struct STask ** queue[PRIOR_LEVELS];
extern uint8_t queueSize[PRIOR_LEVELS];
extern uint8_t reservedQueueSize[PRIOR_LEVELS];

uint8_t change_prior(struct STask *, uint8_t);

void sExit();

void null_process(void);

void free_task(struct STask*);

struct STask * create_STask(void (*task)(uint32_t *),uint32_t *,uint8_t, uint32_t *, uint32_t , uint8_t);


#endif
