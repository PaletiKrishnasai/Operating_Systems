#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("A\n");
    fork();
    printf("B\n");
    

    return 0; 
}