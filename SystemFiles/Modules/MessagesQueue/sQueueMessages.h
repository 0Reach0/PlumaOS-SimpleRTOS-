
#include "PlumaConfig.h"


#ifdef QUEUE_MESSAGES


#ifndef __SQUEUE_MESSAGES_H__
#define __SQUEUE_MESSAGES_H__

#include "sTask.h"
#include <stdint.h>

#define DEFAULT_RESERVED_QMT_SIZE 2
#define MESSAGES_QUEUE_PRIOR_LEVELS 3
#define MESSAGES_QUEUE_RESERVE_INCREMENT 2

#define sQueueMessages_IsEmpty(sQueueMessages) sQueueMessages->size == 0

#define sQueueMessages_IsFull(sQueueMessages) sQueueMessages->size == sQueueMessages->capacity

struct sQueueMessages{
    void* queueArray;
    uint32_t head;   
    uint32_t tail;   
    uint8_t size;   
    uint32_t capacity;  
    uint8_t elementSize; 
};

struct QM_T_Pair
{
	struct sQueueMessages * queue;
	struct sTask ** spaceWaitingTasks[MESSAGES_QUEUE_PRIOR_LEVELS];
	uint8_t spaceWaitingTasksArrSize[MESSAGES_QUEUE_PRIOR_LEVELS];
	uint8_t spaceWaitingTasksArrReservedSize[MESSAGES_QUEUE_PRIOR_LEVELS];
	
	struct sTask ** messageWaitingTasks[MESSAGES_QUEUE_PRIOR_LEVELS];
	uint8_t messageWaitingTasksArrSize[MESSAGES_QUEUE_PRIOR_LEVELS];
	uint8_t messageWaitingTasksArrReservedSize[MESSAGES_QUEUE_PRIOR_LEVELS];
};


struct sQueueMessages* createQueue(uint32_t capacity, uint32_t elementSize);

void freeQueue(struct sQueueMessages* queue);

int enqueue(struct sQueueMessages* queue, void* data, uint8_t prior);

int dequeue(struct sQueueMessages* queue, void* data, uint8_t prior);

uint8_t make_waiting_task_for_message(struct sQueueMessages *, struct sTask *,uint8_t);

uint8_t make_waiting_task_for_space(struct sQueueMessages *, struct sTask *,uint8_t);

void wake_space_waiting_tasks(struct sQueueMessages *);

void wake_message_waiting_tasks(struct sQueueMessages *);
#endif 


#endif 
