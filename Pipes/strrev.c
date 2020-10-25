#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void reverseStr(char *str) 
{
    for (int i = 0; i < strlen(str) / 2; i++)
    {
        char temp = str[i];
        str[i] = str[strlen(str) - i - 1];
        str[strlen(str) - i - 1] = temp;
    }
} 


int main()

{
    int pipe1[2],pipe2[2];
    int pid;
    int length;
    char inputstr[512];
    printf("Enter the string :\n");
    scanf("%[^\n]%*c",inputstr);
    char readmessage[512];
    char writemessage[512];
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
    if(pid > 0)
    {
        close(pipe1[0]); //close read of pipe1
        close(pipe2[1]); //close write of pipe2
        write(pipe1[1],inputstr,sizeof(inputstr)+1);
        read(pipe2[0],readmessage,sizeof(readmessage));
        printf("Reversed String is  :%s \n",readmessage);
        length=strlen(readmessage);
        if(strncmp(inputstr,readmessage,length)==0)
        printf("%s is a Palindrome\n",inputstr);
        else printf("%s is NOT a Palindrome\n",inputstr);

    }
    else
    {
        close(pipe1[1]); // close write of pipe1
        close(pipe2[0]); //close read of pipe2
        read(pipe1[0],writemessage,sizeof(writemessage));
        reverseStr(writemessage);
        printf("%s\n",writemessage);
        write(pipe2[1], writemessage, sizeof(writemessage) + 1);
    }

    return 0;
}