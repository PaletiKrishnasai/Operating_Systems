#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()

{
    int pid;
    int num, originalNum, remainder, result = 0,range;
    printf("Enter a range : ");
    scanf("%d",&range);
    
    FILE *fp;
    printf(" 0 is an Armstrong number\n");

   for(int i=1 ; i<range ;i++)
 {
     originalNum =i;
     num = i;

    pid = fork();

    if (pid == 0)
    {
         while (originalNum != 0)
                {
                     // remainder contains the last digit
                      remainder = originalNum % 10;

                      result += remainder * remainder * remainder;

                    // removing last digit from the orignal number
                    originalNum /= 10;
                 }
                 fp = fopen("temp.txt", "w");
                 fprintf(fp, "%d", result);
                  fclose(fp);


        
        
        
    }
    else if(pid > 0)
    {
        wait(NULL);
        fp =fopen("temp.txt", "r");
        fscanf(fp, "%d", &result);
        fclose(fp);
        //printf("%d\n", result);
        if (result == num)
            printf("%d is an Armstrong number.\n", num);
        
        
    }
    

 }
    return 0;

}