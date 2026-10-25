#ifndef QUEUE_H
#define QUEUE_H

#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_QUEUE_CAPACITY 10

typedef struct {
    Order* queue[MAX_QUEUE_CAPACITY];
    
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;

    int insertPointer;
    int removePointer;

} OrderQueue;

void init_queue (OrderQueue * q);

int insert_item(Order * item, OrderQueue * q);

int remove_item(Order ** item, OrderQueue * q);


#endif