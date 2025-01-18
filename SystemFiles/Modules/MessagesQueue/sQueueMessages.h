
#include "PlumaConfig.h"


#ifdef QUEUE_MESSAGES


#ifndef __SQUEUE_MESSAGES_H__
#define __SQUEUE_MESSAGES_H__

#include "sTask.h"
#include <stdint.h>

#define WAITING_QUEUE_RESERVED_SIZE  2

#define sQueueMessages_IsEmpty(sQueueMessages) sQueueMessages->size == 0

#define sQueueMessages_IsFull(sQueueMessages) sQueueMessages->size >= sQueueMessages->capacity

#define sQueueMessages_IsMessageWait(sQueueMessages)  sQueueMessages->messageWaitingArrSize > 0

#define sQueueMessages_IsSpaceWait(sQueueMessages)  sQueueMessages->spaceWaitingArrSize > 0

struct sQueueMessages{
    uint8_t * queueArray;
    uint8_t head;   
    uint8_t tail;   
    uint8_t size;   
    uint8_t capacity;  
    uint32_t elementSize; 


    struct sTask ** spaceWaiting;
    uint8_t spaceWaitingArrSize;
	
    struct sTask ** messageWaiting;
    uint8_t messageWaitingArrSize;
};


uint8_t sQueueMessages_Init(struct sQueueMessages* queue, uint8_t capacity, uint32_t elementSize);

void freeQueue(struct sQueueMessages* queue);

uint8_t sQueueMessages_Enqueue(struct sQueueMessages* q, uint8_t *data);

uint8_t sQueueMessages_Dequeue(struct sQueueMessages* q, uint8_t *data);

uint8_t make_waiting_task_for_message(struct sQueueMessages *, struct sTask *);

uint8_t make_waiting_task_for_space(struct sQueueMessages *, struct sTask *);

void wake_space_waiting_tasks(struct sQueueMessages *);

void wake_message_waiting_tasks(struct sQueueMessages *);
#endif 


#endif 
