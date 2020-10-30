#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>


void *child(void *param)
{   int temporary =*((int*) param);
    int num, originalNum, rem, result = 0;

    originalNum = temporary;
    num = temporary;
    while (originalNum != 0)
    {
        // rem contains the last digit
        rem = originalNum % 10;

        result += rem * rem * rem;

        // removing last digit from the orignal number
        originalNum /= 10;
    }
    if (result == num)
    printf("%d \n", num);
    pthread_exit(NULL);
}

int main()
{
    int start, end ;
    int range;
    printf("Enter the range : ");
    scanf("%d",&end);
    range = end + 1;

    pthread_t tid[range] ;
    for (int i = 0; i <= end; i++)
    {
        pthread_create(&tid[i],NULL,child,&i);
        pthread_join(tid[i], NULL);
    }
    

        return 0;
}