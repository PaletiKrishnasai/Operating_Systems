#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("OS\n");
    fork();
    fork();
    fork();
    
}