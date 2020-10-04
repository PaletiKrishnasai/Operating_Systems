#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void history(char his[],char cmd[])
{
    strcat(his,"\n");
    strcat(his,cmd);

}


int main()
{

    char his[1000]="";//empty
    char cmd[100]={0};//initialize to 0
    char temp[100][100]={0};
    int len_temp = 0;


    while(1)
    {
        printf("%s","\npaleti@paletil:~$ ");
        scanf("%[^\n]%*c",cmd);
        strcpy(temp[len_temp],cmd);
        len_temp++;
        history(his, cmd);
        if (strcmp(cmd, "quit") == 0)
        {
            break;
        }
        char arg[10][100]={0};
        int argc=0;
        int count =0;
        for(int i=0;i<strlen(cmd);i++)
        {
            if(cmd[i]==' ')
            {
                argc++;
                count=0;
            }
            else
            {
                arg[argc][count++] = cmd[i];
            }
        }
        char *argv[10]={0};
        int k =0;
        for(k=0;k<=argc;k++)
             argv[k]=arg[k];
         argv[k]=NULL;

        pid_t pid ;
        pid = fork();
        if(pid == 0)
        {
            if(!(strcmp(cmd,"history")))
            printf("%s\n",his);
            else if (cmd[0]=='!')
            {
                //strcat()
                int vck = atoi(&cmd[1]);
                for(int i=vck-1;i>-1;i--)
                {
                    printf("%s\n",temp[i]);
                }

            }
            else
            {
                if(execvp(*argv,argv)<0)
                printf("Invalid Command!!!\n");
            }
            exit(0);
            
        }
        else 
        wait(NULL);

    } 
}