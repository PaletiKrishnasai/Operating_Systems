#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()

{
    int pipe1[2], pipe2[2];
    int pid;
    char string1[512], string2[512] ,destination[512];
    printf("Enter string1 :\n");
    scanf("%[^\n]%*c", string1);
    printf("Enter string2 :\n");
    scanf("%[^\n]%*c", string2);
    strcpy(destination,string1);
    char readmessage[512];
    char readmessage2[512];
    int returnstatus1, returnstatus2;
    returnstatus1 = pipe(pipe1);
    if (returnstatus1 == -1)
    {
        printf("Unable to create pipe 1 \n");
        return 1;
    }
    returnstatus2 = pipe(pipe2);
    if (returnstatus2 == -1)
    {
        printf("Unable to create pipe2 \n");
        return 1;
    }
    pid = fork();
    if (pid>0)
    {
        close(pipe1[1]); //close write of pipe1
        close(pipe2[0]); //close read of pipe2
       
        read(pipe1[0], readmessage, sizeof(readmessage));
        strcat(destination,readmessage);
        write(pipe2[1],destination,sizeof(destination)+1);

    }
    else
    {
        close(pipe1[0]); //close read of pipe1
        close(pipe2[1]); //close write of pipe2
        //sleep(50);
       
        write(pipe1[1],string2,sizeof(string2)+1);
        read(pipe2[0],readmessage2,sizeof(readmessage2));
        printf("Concatnated string is : %s\n",readmessage2);
    }
    
    
}