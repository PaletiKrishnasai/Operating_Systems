// simulate producer consumer code discussed in the class

// 1 producer 3 consumers using semaphores

//Assumption: Buffer Size = 1
//We manually define the 3 consumers the consume exactly one-third of the items produced by the Producer for ease of Understanding.

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SHARED 1

void * Producer();
void *Consumer();

sem_t empty, full, sm;
int data;

int main()
{
    pthread_t ptid, ctid1, ctid2, ctid3;
    int x = 1, y = 2, z = 3;
    int *a = &x;
    int *b = &y;
    int *c = &z;
    sem_init(&empty, SHARED, 1);
    sem_init(&full, SHARED, 0);
    sem_init(&sm, SHARED, 1);
    pthread_create(&ptid, NULL, Producer, NULL);
    pthread_create(&ctid1, NULL, Consumer, (void *)a);
    pthread_create(&ctid2, NULL, Consumer, (void *)b);
    pthread_create(&ctid3, NULL, Consumer, (void *)c);
    pthread_join(ptid, NULL);
    pthread_join(ctid1, NULL);
    pthread_join(ctid2, NULL);
    pthread_join(ctid3, NULL);
    printf("\nMain done\n");
}

void *Producer()
{
    int produced;
    printf("\nProducer created");
    printf("\nProducer id is %ld\n", pthread_self());
    for (produced = 0; produced < 30; produced++)
    {
        sem_wait(&empty);
        sem_wait(&sm);
        data = produced;
        sem_post(&sm);
        sem_post(&full);
        printf("\nProducer: %d", data);
    }
}

void *Consumer(void *no)
{
    int consumed, total = 0;
    int *thread = (int *)no;
    printf("\nConsumer created, Thread number: %d\n", *thread);
    printf("\nConsumer id is %ld\n", pthread_self());
    for (consumed = 0; consumed < 10; consumed++)
    {
        sem_wait(&full);
        sem_wait(&sm);
        total = total + data;
        printf("\nThread: %d, Consumed: %d", *thread, data);
        sem_post(&sm);
        sem_post(&empty);
    }
    printf("\nThe total of 10 iterations for thread %d is %d\n", *thread, total);
}