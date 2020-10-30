#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 100
int list[MAX];
int size;
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
void *mean(void *param)
{
    int temp[size];
    for (int i=0;i<size;i++)
    {
        temp[i] = list[i];
    }
    float mean;
    for (int i = 0; i < size; i++)
    {
        mean = mean + temp[i];
    }
    mean = mean / size;
    printf("\nMean : %f\n",mean);
    pthread_exit(NULL);
}

void *median(void *param)
{
    int temp[size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = list[i];
    }
    qsort(temp, size, sizeof(int), cmpfunc);
    int median;
    if(size%2==1)
    median = temp[(size - 1)/2];
    else median = (temp[size/2] + temp[size/2 - 1]) / 2 ;
    printf("\nMedian : %d\n",median);
    pthread_exit(NULL);
}

void *mode(void *param)
{
    
    int temp[size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = list[i];
    }
    int mode;
    int maxCount;
    for (int i = 0; i < size; ++i)
    {
        int count = 0;

        for (int j = 0; j < size; ++j)
        {
            if (temp[j] == temp[i])
                ++count;
        }

        if (count > mode)
        {
            maxCount = count;
            mode = temp[i];
        }
    }
    printf("\nMode : %d\n",mode);
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    if(argc<2)
    printf("Usage: ./a.out <list of numbers>\n");
    size = argc - 1;
    for (int i = 0; i < size; i++)
    {
        list[i] = atoi(argv[i+1]);
    }
    pthread_t tid[3];
    pthread_attr_t attr;
    pthread_attr_init (&attr);

    pthread_create(&tid[0],&attr,mean,NULL);
    pthread_create(&tid[1], &attr, median, NULL);
    pthread_create(&tid[2], &attr, mode, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    return 0;
}
