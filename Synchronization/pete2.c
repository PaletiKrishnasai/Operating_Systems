#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#define SHARED 1

int data;
int flag[2];
int turn;
sem_t empty,full;

void lock_in()
{
    flag[0] = 0;
    flag[1] = 0;
    turn = 0;

}

void lock(int index)
{
    flag[index] = 1;
    turn = 1-index;
    while(flag[1-index]==1 && turn==1-index);
}

void unlock(int index)
{
    flag[index]=0;
}

void *producer()
{
    int p_no;
    printf("\nNew Producer id : %ld\n",pthread_self());
    for(p_no=0;p_no<5;p_no++)
    {
        sem_wait(&empty);
        lock(0);
        //CS starts
        data = p_no;
        //CS ends
        unlock(0);
        sem_post(&full);
        printf("\nProduced data : %d\n",data);
    }
}

void *consumer()
{
    int c_no,total=0;
    printf("\nNew consumer id : %ld\n",pthread_self());
    for(c_no=0;c_no<5;c_no++)
    {
        sem_wait(&full);
        lock(1);
        //CS starts
        total = total + data;
        //CS ends
        unlock(1);
        sem_post(&empty);
        printf("\nconsumed data : %d\n",data);
    }
    printf("\nTotal consumed data %d\n",total);
}

int main()
{
    pthread_t p1,c1;
    lock_in();
    sem_init(&empty,SHARED,1);
    sem_init(&full,SHARED,0);
    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&c1,NULL,consumer,NULL);
    pthread_join(p1,NULL);
    pthread_join(c1,NULL);
    printf("\nSTOPPED\n");
    return 0;
}