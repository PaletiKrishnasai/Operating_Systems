#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int n;
    int sum =0;
    printf("Enter the size : \n");
    scanf("%d", &n);

    int pid;
    pid = fork();

    if (pid == 0)
    {
        
        printf("Even Series : \n");
        for (int i = 0; i < n; i++)
        sum = sum + (2*i) ;
        printf("%d\n",sum);
        printf("\n");
    }
    else if (pid > 0)
    {
        wait(NULL);

        printf("Odd series : \n");
        for (int i = 0; i < n; i++)
        sum = sum + (2*i+1);
        printf("%d\n",sum);

        
        printf("\n");
    }

    return 0;
}