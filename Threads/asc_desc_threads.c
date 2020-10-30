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

int a[MAX],d[MAX];
int size;

void *ascending(void *param)
{
    for (int i = 0; i < size; i++)
    {
        int max_i = 0;
        for (int j = 0; j < size - i; j++)
        {
            if (a[j] > a[max_i])
            {
                max_i = j;
            }
        }

        int temp = a[max_i];
        a[max_i] = a[size - i - 1];
        a[size - i - 1] = temp;
    }
    printf("\nAscending order: ");

    for (int i = 0; i < size; i++)
        printf("%d ", a[i]);

    printf("\n");
    pthread_exit(NULL);
}

void *descending(void *arg)
{
    for (int i = 0; i < size; i++)
    {
        int max_i = i;
        for (int j = i; j < size; j++)
        {
            if (d[j] > d[max_i])
            {
                max_i = j;
            }
        }
        int temp = d[max_i];
        d[max_i] = d[i];
        d[i] = temp;
    }
    printf("\nDescending order: ");
    for (int i = 0; i < size; i++)
        printf("%d ", d[i]);

    printf("\n");
    pthread_exit(NULL);
}
int main()
{

        printf("Enter size of array: ");
        scanf("%d", &size);
        printf("Enter the array: ");
        for (int i = 0; i < size; i++)
        {
            scanf("%d", &a[i]);
            d[i] = a[i];
        }
        pthread_t tid[2];
        pthread_create(&tid[0],NULL,ascending,NULL);
       
        pthread_create(&tid[1],NULL,descending,NULL);
        pthread_join(tid[0], NULL);
        pthread_join(tid[1],NULL);

    return 0;
}