#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int size;
    printf("Enter the size: \n");
    scanf("%d",&size);
    int pid;
    pid = fork();
    

    if(pid ==0)
    {
        printf("Prime Series : \n");
        int n=2;
        int no=0;
        while(no < size)
        {
            int a = n-1;
            while(a>1)
            {
                if(n%a == 0)
                {
                    a=-1;
                    break;
                }
                a--;
            }
            if(a>0)
            {
                printf("%d\n",n);
                no++;
            }
            n++;
        }
        printf("\n");

    }
    else if(pid > 0)
    {
        wait(NULL);
        printf("Fibonacci series : \n");
        int a= 1,b =1;
        printf("1\n1\n");
        for(int i=0;i<size-2;i++)
        {
            a = a + b;
            b = a - b;
            printf("%d\n",a);
        }
        printf("\n");

    }

    return 0;
}