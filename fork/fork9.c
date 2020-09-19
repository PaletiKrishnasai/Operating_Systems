/*Express the following in a process tree setup and also write the C code for the same setup
1 forks 2 and 3
2 forks 4 5 and 6
3 forks 7
4 forks 8
5 forks 9
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("main or node 1 \n");
    pid_t c1; // 1 is parent and 2 and 3 are in scope of 1
    c1 = fork();
    if(c1 == 0)
    {
        //node 2 
        pid_t c2; // 4 5 6 are in scope of 2 and 1 
        c2 = fork(); // 2 split to 2 and 4
        if(c2 ==0)
        {
            //node 4  
            pid_t c4;
            c4 =fork();
            if(c4 == 0)
            {
                printf("node 8 in tree\n");
            }
            else if(c4 >0)
            {
                printf("node 4 in tree\n");
            }
        }
        else if(c2 >0)
        {
            // node 2 in level 3 (levels starting from 1)
            c2 = fork();
            if(c2 == 0)
            {
                pid_t c5;
                c5 = fork();
                if(c5 == 0)
                {
                    printf("node 9 in tree \n");
                }
                else if(c5 > 0)
                {
                    printf("node 5 in tree \n");
                }
            }
            if(c2 >0)
            {
                c2 = fork();
                if (c2 == 0)
                {
                    printf("node 6 in tree \n");
                }
                else if(c2 >0)
                {
                    printf("node 2 in tree \n");
                }
            }
            
         }
    }
    else if(c1 > 0)
    {
        // node 1 in level 2
        c1 = fork();
        if(c1 == 0)
        {
            pid_t c3;
            c3 = fork();
            if(c3 ==0)
            {
                printf("node 7 in tree \n");

            }
            else if(c3>0)
            {
                printf("node 3 in tree \n");
            }
        }
        else if(c1 >0)
        {
            printf("node 1 in tree \n");
        }
    }

    return 0;

}