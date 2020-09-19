#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork(); //A
    if(pid!=0)
    fork();
    fork();
    printf("Count \n");
    return 0;
}