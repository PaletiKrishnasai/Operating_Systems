#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

void *primecheck(void *param )
{
    int n = *((int *)param);
    int j,flag=1;
    if (n <= 1)
        flag = 0;
    else if (n == 2)
        flag = 1;
    else 
    {
        for(j=2;j<=sqrt(n);j++)
        {
            if(n%j == 0)
            {  
                flag=0;
                break;
            }
        }
    }
    if(flag == 1)
    printf("%d\n",n);
}

int main(int argc,const char *argv[])
{
    if(argc!=2)
    printf("Usage: ./a.out num(limit of prime numbers to be generated)\n");
    else
    {
        int count = atoi(argv[1]);
        pthread_t tid[count*2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        for (int i=1;i<=count;i++)
        {
            pthread_create(&tid[i],&attr,primecheck,&i);
            pthread_join(tid[i],NULL);
        }

    }
    return 0;
}