#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 100000

int get_max(int a[], int n)
{
    int max = a[0];
    for (int i=1;i<n;i++)
        if(a[i]>max)
            max = a[i];
    return max;
}

int main()
{
    srand(time(0));
    struct timeval start, stop;
    double secs = 0;
    
    int output_fds = open("./output.txt",O_WRONLY);
    dup2(output_fds,STDOUT_FILENO);
    int size,array[MAX];
    printf("Enter the size of the list : \n");
    scanf("%d",&size);
    for(int i=0;i<size;i++)
    {
        array[i] = rand()%(size+1);
    }
  /* for (i = 0; i < 100; i++)
    {
        printf("%d --->  %d\n",i+1,array[i]);
    }
    */
    gettimeofday(&start, NULL);
    int bucket[size][size], bucket_count[size];
    int i, j, k, r, NOP = 0, divisor = 1, lar, pass;
    lar = get_max(array, size);
    
    int pid = vfork();
    if(pid==0)
    {
      
        while(lar > 0)
        {
            NOP++;
            lar /= 10;

        }
        for(pass=0;pass<NOP/2;pass++)
        {
            for(i=0;i<size;i++)
            {
                bucket_count[i] = 0;
            }
            for(i =0;i<size;i++)
            {
                r = (array[i]/divisor)%10;
                bucket[r][bucket_count[r]] = array[i];
                bucket_count[r] += 1;

            }
            i=0;
            for(k=0;k<size;k++)
            {
                for (j=0;j<bucket_count[k];j++)
                {
                    array[i] = bucket[k][j];
                    i++;
                }
            }
            divisor *= 10;
            printf("PASS %d : \n",pass+1);
            for(i =0;i<size;i++)
            {
                printf("%d ",array[i]);
            }
            printf("\n");
        }
        exit(0);
    }
    if(pid>0)
    {
        wait(NULL);
        for (pass = NOP/2; pass < NOP; pass++)
        {
            for (i = 0; i < size; i++)
            {
                bucket_count[i] = 0;
            }
            for (i = 0; i < size; i++)
            {
                r = (array[i] / divisor) % 10;
                bucket[r][bucket_count[r]] = array[i];
                bucket_count[r] += 1;
            }
            i = 0;
            for (k = 0; k < size; k++)
            {
                for (j = 0; j < bucket_count[k]; j++)
                {
                    array[i] = bucket[k][j];
                    i++;
                }
            }
            divisor *= 10;
            printf("\n");
            printf("PASS %d : \n", pass + 1);
            printf("\n");
            for (i = 0; i < size; i++)
            {
                printf("%d ", array[i]);
            }
            printf("\n");
        }
    }

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    printf("\n");
    printf("Sorted list : \n");
    printf("\n");
    for (i=0;i<size;i++)
    printf("%d ",array[i]);
    printf("\n");
    printf("Execution time:  %f\n",secs);

    return 0;
}
