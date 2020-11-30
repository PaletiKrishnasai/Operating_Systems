#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/types.h>
#define BUFFER 10

int flag[2],turn;
int in=0;
int out=0;
int counter=0;
void *produce(void *param)
{
flag[0]=1;
turn=0;
while(1)
{
while (in+1%BUFFER==out);
while(flag[0]==1&&turn==0)
{
printf("Produced at %d th place\n",in);
in=(in+1)%BUFFER;
turn=1;
sleep(1);
}
}
}
void *consume(void *param)
{
flag[1]=1;
turn=1;
while(1)
{
while(in==out);
while(flag[1]==1&&turn==1)
{
printf("consumer consumed at %d th place\n",out);
out=(out+1)%BUFFER;
turn=0;
sleep(1);
}
}
}

int main()
{
pthread_t producer,consumer;
pthread_create(&producer,NULL,produce,NULL);
sleep(1);
pthread_create(&consumer,NULL,consume,NULL);
pthread_join(producer,NULL);
pthread_join(consumer,NULL);
return 0;
}
