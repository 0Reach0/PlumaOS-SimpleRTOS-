
#include "sQueueMessages.h"

#ifdef QUEUE_MESSAGES
#include "Kernel.h"
#include <stdlib.h>
#include <string.h>

extern struct STask * current;

struct QM_T_Pair ** taskWaitingQueues;
uint8_t taskWaitingQueuesSize;


void sQueueMessages_Init(struct sQueueMessages* queue, uint32_t capacity, uint32_t elementSize) {
    queue->queueArray = malloc(capacity * elementSize);
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0;
    queue->capacity = capacity;
    queue->elementSize = elementSize;
}

uint8_t sQueueMessages_Enqueue(struct sQueueMessages* queue, void* item, uint8_t prior) {
    if (sQueueMessages_IsFull(queue)) {
        make_waiting_task_for_space(queue, current, prior);
				Schedule();
    }
		if(taskWaitingQueuesSize != 0)
		{
			wake_message_waiting_tasks(queue);
		}
    uint32_t index = queue->tail * queue->elementSize;
    memcpy((char*)queue->queueArray + index, item, queue->elementSize);
    queue->tail = (queue->tail + 1) % queue->capacity;
    queue->size++;
    return 1;
}

uint8_t sQueueMessages_Dequeue(struct sQueueMessages* queue, void* item, uint8_t prior) {
    if (sQueueMessages_IsEmpty(queue)) {
        make_waiting_task_for_message(queue, current, prior);
				Schedule();
    }
		if(taskWaitingQueuesSize != 0)
		{
			wake_space_waiting_tasks(queue);
		}
		
    uint32_t index = queue->head * queue->elementSize;
    memcpy(item, (char*)queue->queueArray + index, queue->elementSize);
    queue->head = (queue->head + 1) % queue->capacity; 
    queue->size--;
    return 1;
}


void sQueueMessages_Free(struct sQueueMessages* queue) {
    free(queue->queueArray);
    queue->queueArray = NULL;
    queue->size = 0;
    queue->capacity = 0;
}


uint8_t make_waiting_task_for_message(struct sQueueMessages * q, struct STask * task, uint8_t prior)
{
		if(prior > MESSAGES_QUEUE_PRIOR_LEVELS || prior < 1) return 0;
		for(uint8_t i = 0; i < taskWaitingQueuesSize; i++)
		{
				if(taskWaitingQueues[i]->queue == q)
				{
						
						if(taskWaitingQueues[i]->messageWaitingTasksArrReservedSize[prior] >0)
						{
								taskWaitingQueues[i]->messageWaitingTasks[prior][taskWaitingQueues[i]->messageWaitingTasksArrSize[prior]] = task;
								taskWaitingQueues[i]->messageWaitingTasksArrSize[prior]--;
								taskWaitingQueues[i]->messageWaitingTasksArrReservedSize[prior]++;
								return 1;
						}
						else
						{
								struct STask ** newArr = (struct STask **)malloc((taskWaitingQueues[i]->messageWaitingTasksArrSize[prior] + MESSAGES_QUEUE_RESERVE_INCREMENT) * sizeof(struct STask *));
								if(newArr == 0) return 0;
								for(uint8_t t = 0; t < taskWaitingQueues[i]->messageWaitingTasksArrSize[prior]; t++)
								{
										newArr[t] = taskWaitingQueues[i]->messageWaitingTasks[prior][t];
								}
								free(taskWaitingQueues[i]->messageWaitingTasks[prior]);
								taskWaitingQueues[i]->messageWaitingTasks[prior] = newArr;
								taskWaitingQueues[i]->messageWaitingTasks[prior][taskWaitingQueues[i]->messageWaitingTasksArrSize[prior]] = task;
								taskWaitingQueues[i]->messageWaitingTasksArrSize[prior]--;
								taskWaitingQueues[i]->messageWaitingTasksArrReservedSize[prior]++;
								return 1;
						}
				}
		}
		struct QM_T_Pair ** newArr = (struct QM_T_Pair **)malloc(taskWaitingQueuesSize + 1 * sizeof(struct QM_T_Pair *));
		if(newArr == 0) return 0;
		for(uint8_t i = 0; i <taskWaitingQueuesSize; i++)
		{
				newArr[i] = taskWaitingQueues[i];
		}
		struct QM_T_Pair * newPair =  (struct QM_T_Pair *)malloc(sizeof(struct QM_T_Pair *));;
		newPair->queue = q;
		for(uint8_t i = 0; i < MESSAGES_QUEUE_PRIOR_LEVELS; i++)
		{
			newPair->messageWaitingTasks[i] = (struct STask **)malloc(DEFAULT_RESERVED_QMT_SIZE * sizeof(struct STask *));
			free(newPair);
			return 0;
		}
		newPair->messageWaitingTasks[prior][0] = task;
		return 1;
}


uint8_t make_waiting_task_for_space(struct sQueueMessages * q, struct STask * task, uint8_t prior)
{
		if(prior > MESSAGES_QUEUE_PRIOR_LEVELS || prior < 1) return 0;
		for(uint8_t i = 0; i < taskWaitingQueuesSize; i++)
		{
				if(taskWaitingQueues[i]->queue == q)
				{
						
						if(taskWaitingQueues[i]->spaceWaitingTasksArrReservedSize[prior] >0)
						{
								taskWaitingQueues[i]->spaceWaitingTasks[prior][taskWaitingQueues[i]->spaceWaitingTasksArrSize[prior]] = task;
								taskWaitingQueues[i]->spaceWaitingTasksArrSize[prior]--;
								taskWaitingQueues[i]->spaceWaitingTasksArrReservedSize[prior]++;
								return 1;
						}
						else
						{
								struct STask ** newArr = (struct STask **)malloc((taskWaitingQueues[i]->spaceWaitingTasksArrSize[prior] + MESSAGES_QUEUE_RESERVE_INCREMENT) * sizeof(struct STask *));
								if(newArr == 0) return 0;
								for(uint8_t t = 0; t < taskWaitingQueues[i]->spaceWaitingTasksArrSize[prior]; t++)
								{
										newArr[t] = taskWaitingQueues[i]->spaceWaitingTasks[prior][t];
								}
								free(taskWaitingQueues[i]->spaceWaitingTasks[prior]);
								taskWaitingQueues[i]->spaceWaitingTasks[prior] = newArr;
								taskWaitingQueues[i]->spaceWaitingTasks[prior][taskWaitingQueues[i]->spaceWaitingTasksArrSize[prior]] = task;
								taskWaitingQueues[i]->spaceWaitingTasksArrSize[prior]--;
								taskWaitingQueues[i]->spaceWaitingTasksArrReservedSize[prior]++;
								return 1;
						}
				}
		}
		struct QM_T_Pair ** newArr = (struct QM_T_Pair **)malloc(taskWaitingQueuesSize + 1 * sizeof(struct QM_T_Pair *));
		if(newArr == 0) return 0;
		for(uint8_t i = 0; i <taskWaitingQueuesSize; i++)
		{
				newArr[i] = taskWaitingQueues[i];
		}
		struct QM_T_Pair * newPair =  (struct QM_T_Pair *)malloc(sizeof(struct QM_T_Pair *));;
		newPair->queue = q;
		for(uint8_t i = 0; i < MESSAGES_QUEUE_PRIOR_LEVELS; i++)
		{
			newPair->spaceWaitingTasks[i] = (struct STask **)malloc(DEFAULT_RESERVED_QMT_SIZE * sizeof(struct STask *));
			free(newPair);
			return 0;
		}
		newPair->spaceWaitingTasks[prior][0] = task;
		return 1;
}



void wake_space_waiting_tasks(struct sQueueMessages * q){
			for(uint8_t i =0; i < taskWaitingQueuesSize; i++)
			{
				if(taskWaitingQueues[i]->queue == q )
				{
						for(uint8_t t =0; t <	MESSAGES_QUEUE_PRIOR_LEVELS; t++){
								for(uint8_t it = 0; it < taskWaitingQueues[i]->spaceWaitingTasksArrSize[t]; it++)
								{
										taskWaitingQueues[i]->spaceWaitingTasks[t][it]->isReady = 1; 
										taskWaitingQueues[i]->spaceWaitingTasksArrSize[t]--;
										taskWaitingQueues[i]->spaceWaitingTasksArrReservedSize[t]++;
								}
						}
						break;
				}
		}
	
}





void wake_message_waiting_tasks(struct sQueueMessages * q){
			for(uint8_t i =0; i < taskWaitingQueuesSize; i++)
			{
				if(taskWaitingQueues[i]->queue == q )
				{
						for(uint8_t t =0; t <	MESSAGES_QUEUE_PRIOR_LEVELS; t++){
								for(uint8_t it = 0; it < taskWaitingQueues[i]->messageWaitingTasksArrSize[t]; it++)
								{
										taskWaitingQueues[i]->messageWaitingTasks[t][it]->isReady = 1; 
										taskWaitingQueues[i]->messageWaitingTasksArrSize[t]--;
										taskWaitingQueues[i]->messageWaitingTasksArrReservedSize[t]++;
								}
						}
						break;
				}
		}
	
}



#endif 