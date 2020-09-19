#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("This will be printed 1?\n");
    fork();
    printf("This will be printed 2?\n");
    fork();
    printf("This will be printed 3?\n");
    fork();
    printf("This will be printed 4?\n");

    return 0;
}