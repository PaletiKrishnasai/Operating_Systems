#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()

{
    pid_t pid;
    int count=0;
    while(1)
    {
        pid = vfork();
        if (pid == 0)       
        {
            count++;
            exit(0); 
        }
        else if(pid == -1)
        {
            printf("Max Processes allowed :%d\n",count);
            exit(-1);
        }
        
    }
    return 0;
}