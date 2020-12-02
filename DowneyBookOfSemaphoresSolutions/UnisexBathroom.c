#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex,womanSem,manSem;
int menInside =0, womenInside = 0, menOutside =0, womenOutside =0;

void manEnter()
{
    while(sem_wait(&mutex)!=0);
    if (womenInside > 0)
    {
        menOutside++;
        sem_post(&mutex);
        while(sem_wait(&manSem)!=0);
        menOutside--;
    }
    menInside++;
    if(menOutside > 0) sem_post(&manSem);
    else sem_post(&mutex);
}

void manLeave()
{
    while (sem_wait(&mutex)!=0);
    menInside--;
    if((womenOutside>0) && (menInside == 0))
    sem_post(&womanSem);
    else if(menOutside>0) sem_post(&manSem);
    else sem_post(&mutex);
}

void womanEnter()
{
    while(sem_wait(&mutex)!=0);
    if (menInside > 0)
    {
        womenOutside++;
        sem_post(&mutex);
        while(sem_wait(&womanSem)!=0);
        womenOutside--;
    }
    womenInside++;
    if(womenOutside>0) sem_post(&womanSem);
    else sem_post(&mutex);
}

void womanLeave()
{
    while (sem_wait(&mutex)!=0);
    womenInside--;
    if((menOutside>0) && (womenInside==0))
    sem_post(&manSem);
    else if (womenOutside>0) sem_post(&womanSem);
    else sem_post(&mutex);
}

void manGoes(int x)
{
    manEnter();
    printf("MAN-%d has entered the restroom.\n",x);
    sleep(2);
    printf("MAN-%d is leaving the restroom\n",x);
    manLeave();
}

void womanGoes(int x)
{
    womanEnter();
    printf("WOMAN - %d has entered the restroom\n",x);
    sleep(5);
    printf("WOMAN - %d is leaving the restroom.\n",x);
    womanLeave();
}

void *runner(void *arg)
{
    int x = *((int*)arg);
    if(x<3)
    {
        printf("Starting thread MAN - %d.\n",x);
        manGoes(x);
    }
    else
    {
        printf("Starting thread WOMAN - %d.\n",x-3);
        womanGoes(x-3);
    }
}

int main()
{
    pthread_t t[5];
    //Senario 1: woman starts 
     int arg[5] ={3,0,1,4,2};

    //Senario 2 : man starts
    //int arg[5] = {0,1,3,2,4};
    sem_init(&mutex,0,1);
    sem_init(&manSem,0,0);
    sem_init(&womanSem,0,0);

    for(int i=0;i<5;i++)
    pthread_create(&t[i],NULL,runner,(void*)&arg[i]);
    for(int i=0;i<5;i++)
    pthread_join(t[i],NULL);
    return 0;
}


