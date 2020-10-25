#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    srand(time(0));
    int pipe1[2], pipe2[2],pipe3[2];
    int returnstatus1, returnstatus2, returnstatus3;
    int pid;
    char inputstring[512],readmessage[512];
    int startindex,endindex,length,start,end;
    printf("Enter the string : ");
    scanf("%[^\n]%*c", inputstring);
    length = strlen(inputstring);



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
    returnstatus3 = pipe(pipe3);
    if (returnstatus3 == -1)
    {
        printf("Unable to create pipe 3 \n");
        return 1;
    }
    pid = fork();

    if(pid>0)
    {
        close(pipe1[0]); // close read of pipe 1
        close(pipe2[0]); // close read of pipe 2
        close(pipe3[0]); // close read of pipe 3
        startindex = rand() % length/2;
        endindex = length/2 + rand() % length/2;
        printf("\n%d %d\n",startindex,endindex);

        write(pipe1[1],inputstring,sizeof(inputstring));
        write(pipe2[1],&startindex,sizeof(startindex));
        write(pipe3[1],&endindex,sizeof(endindex));

    }
    else
    {
        close(pipe1[1]); // close write of pipe 1
        close(pipe2[1]); // close write of pipe 2
        close(pipe3[1]); // close write of pipe 3

        read(pipe1[0],readmessage,sizeof(readmessage));
        read(pipe2[0],&start,sizeof(start));
        read(pipe3[0],&end,sizeof(end));
        printf("Substring : ");
        for(int i =start;i<=end;i++)
        printf("%c",inputstring[i]);
        printf("\n");
    }

    return 0;
}