#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main()


{
    pid_t pid; //this is to use the pid data type
    pid = fork();
    if(pid == 0)
        execl("/bin/ls", "/bin/ls", "-lh", NULL); //child image is now ls command
    else
    {
        wait(NULL); // parent waits for the child to complete execution
        printf("Parent process gets control \n");
        printf("Parent has waited for child to complete\n");
    }
}