#ifndef __TASKMANAGMENT_H__
#define __TASKMANAGMENT_H__
#include <stdint.h>
#include "STask.H"

#define POINTER_SIZE 32
#define PRIOR_LEVELS 6
#define DEFAULT_RESERVED_Q_SIZE 2
#define RESIZE_INCREMENT      3

#define make_sleep(task) task->isReady = 0
#define wake(task)  task->isReady = 1
extern struct STask * current;
extern struct STask ** queue[PRIOR_LEVELS];
extern uint8_t queueSize[PRIOR_LEVELS];
extern uint8_t reservedQueueSize[PRIOR_LEVELS];


//struct STask * get_current();

//void set_current(struct STask * task);

//struct STask *** get_tasksQueue();

//void set_taskQueue(struct STask *** arr);

//uint8_t * get_tasksSize();

//void set_taskSize(uint8_t sz);

//uint8_t * get_tasksReserved();

//void set_tasksReserved(uint8_t sz);

uint8_t change_prior(struct STask *, uint8_t);


void sExit();

void null_process(void);

void free_task(struct STask*);

struct STask * create_STask(void (*task)(uint32_t *),uint32_t *,uint8_t, uint32_t *, uint32_t , uint8_t);


#endif
