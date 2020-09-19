#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

// A generalized equation for fibonacci 
// F(n+k) = F(n+1)*F(k) + F(n)* F(k-1)
// Explanation:
/* 
    F(n+2)=F(n+1)+F(n)         ->(1)
    F(n+3)=F(n+2)+F(n+1)
          =F(n+1)+F(n+1)+F(n) [from (1)]
          =F(n+1)*2 + F(n)*1   ->(2)
    F(n+4)=F(n+3)+F(n+2)
          =F(n+1)*2 + F(n)*1 +F(n+1) + F(n) [from (1 & 2)]
          =F(n+1)*3 + F(n)*2  
    F(0) = 0 
    F(1) = 1
    F(2) = 1
    F(3) = 2
    F(4) = 3
    Hence F(n+k) = F(n+1)*F(k) + F(n)*F(k-1)
*/
int main()

{
    pid_t pid;
    int size ;
    printf("Enter the size : \n");
    scanf("%d",&size);
    int fib[size+1];
    fib[0] = 0;
    fib[1] = 1;
    fib[2] = 1;
    //now from the formula , to simulate in parent child we can take n=1
    printf("1 : %d\n2 : %d\n",fib[1],fib[2]);
    pid = vfork();

    if(pid == 0)
    {
        for(int i=2;i<size;++i)
        {
            fib[i + 1] = fib[2] * fib[i] + fib[1] * fib[i - 1];
            printf("%d : %d\n",i+1,fib[i+1]);
        }
        exit(0);

    }
    else if(pid > 0)
    {
        wait(NULL);
        printf("Prime Series : \n");
        int n = 2;
        int no = 0;
        while (no < size)
        {
            int a = n - 1;
            while (a > 1)
            {
                if (n % a == 0)
                {
                    a = -1;
                    break;
                }
                a--;
            }
            if (a > 0)
            {
                printf("%d\n", n);
                no++;
            }
            n++;
        }
        printf("\n");
    }
    


    return 0;
}