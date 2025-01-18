
#include "sQueueMessages.h"

#ifdef QUEUE_MESSAGES
#include "Kernel.h"
#include <stdlib.h>
#include <string.h>
struct QM_T_Pair ** taskWaitingQueues;
uint8_t taskWaitingQueuesSize = 0;

uint8_t sQueueMessages_Init(struct sQueueMessages* q, uint8_t capacity, uint32_t elementSize) {
    q->queueArray = (uint8_t *)malloc(capacity * elementSize);
    if (q->queueArray == NULL) return 0;

    q->spaceWaiting = (struct sTask **)malloc(WAITING_QUEUE_RESERVED_SIZE * sizeof(struct sTask *));
    if (q->spaceWaiting == NULL) return 0;

    q->messageWaiting = (struct sTask **)malloc(WAITING_QUEUE_RESERVED_SIZE * sizeof(struct sTask *));
    if (q->messageWaiting == NULL) return 0;

    q->head = 0;
    q->tail = 0;
    q->size = 0;
    q->capacity = capacity;
    q->elementSize = elementSize;
    q->messageWaitingArrSize = 0;
    q->spaceWaitingArrSize = 0;

    return 1;
}

uint8_t sQueueMessages_Enqueue(struct sQueueMessages* q, uint8_t *item) {
       if(sQueueMessages_IsEmpty(q) && sQueueMessages_IsMessageWait(q))
    {
	wake_message_waiting_tasks(q);
    }
    else if(sQueueMessages_IsFull(q)) {
        make_waiting_task_for_space(q, current);
        Schedule();
         for(volatile uint8_t i = 0;  i == 0; ){
          i = current->isReady;
        }
    }

    if(q->tail >= q->capacity) q->tail = 0;
    memcpy(&q->queueArray[q->tail], item, q->elementSize);

    q->tail += q->elementSize;
    q->size++;
    return 1;
}

uint8_t sQueueMessages_Dequeue(struct sQueueMessages* q, uint8_t *item) {
    if(sQueueMessages_IsFull(q) && sQueueMessages_IsSpaceWait(q))
    {
	wake_space_waiting_tasks(q);
    }
    else if (sQueueMessages_IsEmpty(q)) {
        make_waiting_task_for_message(q, current);
        Schedule();
        for(uint8_t i = current->isReady;!i;i= current->isReady ){}
        return 1;
    }

   if(q->head >= q->capacity) q->head = 0;
    memcpy(item, &q->queueArray[q->head], q->elementSize);

    q->head  += q->elementSize;
    q->size--;
    return 1;
}


void sQueueMessages_Free(struct sQueueMessages* queue) {
    free(queue->queueArray);
    queue->queueArray = NULL;
    queue->size = 0;
    queue->capacity = 0;
}


uint8_t make_waiting_task_for_message(struct sQueueMessages * q, struct sTask * task)
{
  
        task->remainQuant = 0;
        task->isReady = 0;

        if(WAITING_QUEUE_RESERVED_SIZE > q->messageWaitingArrSize)
        {
            q->messageWaiting[q->messageWaitingArrSize] = task;
             q->messageWaitingArrSize++;
            return 1;   
        }
    
	struct sTask ** newArr = (struct sTask **)malloc(sizeof(struct sTask *));
        if(newArr == 0) return 0;
        for(uint8_t i = 0; i < q->messageWaitingArrSize-1; i ++)
        {
             newArr[i] = q->messageWaiting[i];
             q->messageWaiting[i] = 0;
        }
        free(q->messageWaiting);
        q->messageWaiting = newArr;
        q->messageWaiting[q->messageWaitingArrSize] = task;
        q->messageWaitingArrSize++;
	return 1;
}


uint8_t make_waiting_task_for_space(struct sQueueMessages * q, struct sTask * task)
{
         task->remainQuant = 0;
         task->isReady = 0;

        if(WAITING_QUEUE_RESERVED_SIZE > q->spaceWaitingArrSize)
        {
           q->spaceWaiting[q->spaceWaitingArrSize] = task;
             q->spaceWaitingArrSize++;
            return 1; 
        }
    
	struct sTask ** newArr = (struct sTask **)malloc(sizeof(struct sTask *));
        if(newArr == 0) return 0;
        for(uint8_t i = 0; i < q->spaceWaitingArrSize-1; i ++)
        {
             newArr[i] = q->spaceWaiting[i];
             q->spaceWaiting[i] = 0;
        }
        free(q->spaceWaiting);
        q->spaceWaiting = newArr;
        q->spaceWaiting[q->spaceWaitingArrSize] = task;
        q->spaceWaitingArrSize++;
	return 1;
}



void wake_space_waiting_tasks(struct sQueueMessages *q) {
   
      if(q->spaceWaitingArrSize == 0) return;
       
       q->spaceWaiting[0]->isReady = 1;
       
      for(uint8_t i =0; i < q->spaceWaitingArrSize-2; i ++)
      {
          q->spaceWaiting[i] = q->spaceWaiting[i+1];
          q->spaceWaiting[i+1] = 0;
      }
      q->spaceWaitingArrSize--;
      return;
}       






void wake_message_waiting_tasks(struct sQueueMessages *q) {
      if(q->messageWaitingArrSize == 0) return;
       
       q->messageWaiting[0]->isReady = 1;
       
      for(uint8_t i =0; i < q->messageWaitingArrSize-2; i ++)
      {
          q->messageWaiting[i] = q->messageWaiting[i+1];
          q->messageWaiting[i+1] = 0;
      }
      q->messageWaitingArrSize--;
      return;
}




#endif 