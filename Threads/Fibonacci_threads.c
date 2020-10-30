#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

struct keyvalue
{
    int key;
    int value;
};

int fib(int n)
{
    if(n==0 || n==1)
    return n;
    else
    return fib(n-1)+fib(n-2);
}

void *runner(void *param)
{
    struct keyvalue *temporary = (struct keyvalue*)param;
    temporary->value = fib(temporary->key);
    pthread_exit(NULL);
}

int main()
{
    int range;
    printf("enter the number of fibonacci numbers to generate : \n");
    scanf("%d", &range);
    struct keyvalue *generate=(struct keyvalue*)malloc(range*sizeof(struct keyvalue));

    pthread_t tid[range];
    printf("Fibonacci Series of %d terms\n",range);
    for (int i=0;i<range;i++)
    {
        generate[i].key =i;
        pthread_create(&tid[i],NULL,runner,&generate[i]);
        pthread_join(tid[i],NULL);
    }
    for(int i=0;i<range;i++)
    {
        printf("%d\n",generate[i].value);
    }

    return 0;
}