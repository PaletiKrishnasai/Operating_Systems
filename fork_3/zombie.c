#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        sleep(50);
        printf("Parent Process\n");
    }
    else if(pid == 0)
    {
        printf("Child Process\n");
        exit(0);
    }
    
    return 0;
}