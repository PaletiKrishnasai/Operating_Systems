#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    char input[512];
    while(1)
    {
        printf("Enter the input : ");
        scanf("%s",input);
        int count[128] ;
        for(int i =0; i<128;i++)
        {
            count[i]=0;
        }

        pid_t pid;
        pid = vfork();

        if(pid == 0)
        {
            for(int i = 0;i<strlen(input);i++)
            {
                count[(int)input[i]]++;
            }
            exit(0);
        }
        else if (pid > 0)
        {
            wait(NULL);
            for(int i = 0;i<128;i++)
            {
                printf("%c --> %d",(char)i,count[i]);
                for(int j=0;j<count[i];j++)printf("#");
                printf("\n");
            }
            printf("\n");
            int flag;
            printf("Do you want to exit: 1-exit 0-repeat ");
            scanf("%d",&flag);
            if(flag == 1)
            {
                return 0;
            }

        }
    }
    return 0;
}