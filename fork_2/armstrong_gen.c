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
    int number,remainder;
    int start,end;
    printf("Enter the starting number\n");
    scanf("%d",&start);
    printf("Enter the ending number\n");
    scanf("%d",&end);
    int range = end-start+1;
    int result[range];
    for(int i=0;i<range;i++)
    result[i]=0;

    pid = vfork();

    if (pid == 0)
    {
        for (int i = start; i < end+1; i++)
        {
            number = i;
            do 
            {
                remainder = number % 10;
                number = number / 10 ;
                result[i-start] += pow(remainder,3);
            }while (number != 0);
        }
        exit(0);
    }
    else if( pid >0 )
    {
        wait(NULL);
        for (int i = start; i <=end; i++)
        {
            if (result[i-start]==i)
            printf("%d is an armstrong number\n",i);
        }
        

    }
    
      return 0;
}

