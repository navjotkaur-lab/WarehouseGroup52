#include <stdlib.h>
#include "inventory.h"
#include "queue.h"
#include <pthread.h>

#define QUEUE_SIZE 10

OrderQueue pending_orders_queue;
OrderQueue packing_queue;

//Threads

//NOTE: Maybe move these functions to another file??? (think about organizing files later)

//Order receivers (producers)
void receivers(){
    
    Order * current_order;
    
    while (true){
        // todo -> gets an incoming orders from another process

        // PUTTING ORDER into pending order queue (producer)

        sem_wait(&pending_orders_queue.full);
		pthread_mutex_lock(&pending_orders_queue.mutex);

        insert_item(current_order, &pending_orders_queue);
        // todo -> log

        pthread_mutex_unlock(&pending_orders_queue.mutex);
		sem_post(&pending_orders_queue.empty);
        
    }

}

// Picker robots (consumers/producers)
void picker(){
    Order * current_order;
    
    while (true){
        //GETTING ORDER from pending orders queue (consumer)
        sem_wait(&pending_orders_queue.empty);
        pthread_mutex_lock(&pending_orders_queue.mutex);

        // current order now stores the order that is going to the packing queue
        remove_item(&current_order, &pending_orders_queue);

        pthread_mutex_unlock(&pending_orders_queue.mutex);
        sem_post(&pending_orders_queue.full);


         // Should sleep be inside or outside the mutex???
        sleep(1); // todo -> random duration from 1 to 3


        // PUTTING ORDER into packing queue (producer)
        sem_wait(&packing_queue.full);
		pthread_mutex_lock(&packing_queue.mutex);

        insert_item(current_order, &packing_queue);
        // todo -> log

        pthread_mutex_unlock(&packing_queue.mutex);
		sem_post(&packing_queue.empty);
        
    }
}

// Packers (consumers)
void packers(){
     Order * current_order;
    
    while (true){
        //GETTING ORDER from pending orders queue (consumer)
        sem_wait(&packing_queue.empty);
        pthread_mutex_lock(&packing_queue.mutex);

        // current order now stores the order that is going to the packing queue
        remove_item(&current_order, &packing_queue);

        pthread_mutex_unlock(&packing_queue.mutex);
        sem_post(&packing_queue.full);

        
        // Should sleep be inside or outside the mutex???
        sleep(1); // todo -> random duration from 1 to 3
    }
}

int main(int argc, char *argv[]){

    init_queue(&pending_orders_queue);
    init_queue(&packing_queue);

    //todo -> Create threads

    return 0;
}

