#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("OS");
    fork();
    fork();
    fork();

    //return 0;
}