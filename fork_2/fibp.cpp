#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int fib(int n)
{
    if(n==0 || n==1)
    return n;
    else
    {
        int sum =0;
        pid_t pid;
        pid = vfork();

        if(pid == 0)
        {
            sum +=fib(n-1);
            exit(0);
        }
        else if(pid > 0)
        {
            wait(NULL);
            sum+=fib(n-2);
            return sum;
        }

    }
    
}
int main()

{
    int size;
    printf("Enter the size : \n");
    scanf("%d",&size);
    printf("\n");
    for(int i=1;i<=size;i++)
    printf("%d\n",fib(i));
    return 0;
}