#include "queue.h"

void init_queue (OrderQueue * q){
    pthread_mutex_init(&q->mutex, NULL);
	sem_init(&q->full, 0, MAX_QUEUE_CAPACITY);
	sem_init(&q->empty, 0, 0);
    q->insertPointer = 0;
    q->removePointer = 0;
}

int insert_item(Order * item, OrderQueue * q)
{
	q->queue[q->insertPointer] = item;
	q->insertPointer = (q->insertPointer + 1) % MAX_QUEUE_CAPACITY;
	return 0;
}

int remove_item(Order ** item, OrderQueue * q)
{
	*item = q->queue[q->removePointer];
	q->removePointer = (q->removePointer + 1) % MAX_QUEUE_CAPACITY;
	return 0;
}