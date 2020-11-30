#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX_PROCESSES 100

struct data
{
    int i;
};

int lock;
int waiting[MAX_PROCESSES];
int no_of_process = 1;

int test_set(int *target)
{
    int rv = *target;
    *target = 1;
    return rv;
}

int x = 5;


void *runner(void *arg)
{
    struct data *t = (struct data *)arg;
    do 
    {
        waiting[t->i] = 1;
        int key = 1;
        while(waiting[t->i] == 1 && key == 1)
        {
            key = test_set(&lock);
        }
        // critical section starts
        printf("Enter P : %d , X : %d\n",t->i,x);
        if(t->i % 2 == 0)
        x++;
        else
        x--;
        printf("Exit P : %d, X : %d\n",t->i,x);
        sleep(1);
        // critical section ends

        waiting[t->i] = 0;
        int j = (t->i+1) % no_of_process;
        while(j != t->i && waiting[j] == 0)
        {
            j = (j+1)%no_of_process;
        }
        if(j == t->i)
        {
            lock =0;

        }
        else
        {
            waiting[j] = 0;
        }

    }while(1);
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        printf("USAGE : ./a.out <no of processes>\n");
    else
        {
            no_of_process = atoi(argv[1]);
            pthread_t tid[no_of_process];
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            struct data d[no_of_process];
            for(int i=0;i<no_of_process;i++)
            {
                d[i].i = i;
                pthread_create(&tid[i],&attr,runner,&d[i]);

            }
            for(int i=0;i<no_of_process;i++)
            {
                pthread_join(tid[i],NULL);
            }
        }
    printf("\n");
    return 0;
}