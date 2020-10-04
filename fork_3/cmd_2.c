#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

void history(char his[], char cmd[])
{
    strcat(his, "\n");
    strcat(his, cmd);
}
int main()
{
    char his[1000] = "";
    char rec[1];
    char cmd[100] = {0};
    int top = 0;
    int fd[2];
    while (1)
    {
        pipe(fd);
        printf("%s", "\npaleti@paletil:~$");
        scanf("%[^\n]%*c", cmd);
        history(his, cmd);
        if (strcmp(cmd, "quit") == 0)
        {
            break;
        }
        char arg[10][100] = {0};
        int argc = 0, count = 0;
        for (int i = 0; i < strlen(cmd); i++)
        {
            if (cmd[i] == ' ')
            {
                argc++;
                count = 0;
            }
            else
            {
                arg[argc][count++] = cmd[i];
            }
        }
        char *argv[10] = {0};
        int k = 0;
        for (k = 0; k <= argc; k++)
        {
            argv[k] = arg[k];
        }
        argv[k] = NULL;
        int pid = fork();
        if (pid == 0)
        {
            if (!strcmp(cmd, "history"))
            {
                printf("%s\n", his);
            }
            else
            {
                dup2(fd[1], 1);
                execvp(*argv, argv);
            }
            exit(0);
        }
        else
        {
            wait(NULL);
            close(fd[1]);
            while (read(fd[0], rec, 1) > 0)
            {

                printf("%c", rec[0]);
            }
            close(fd[0]);
        }
    }
}
