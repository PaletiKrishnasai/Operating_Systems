#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int max(int x, int y)
{
    return (x > y ? x : y);
}

struct data
{
    char *s1, *s2;
    int *res;
};

void *runner(void *);

void *longestSubsequence(char *s1, char *s2, int *res)
{
    if (s1[0] == '\0' || s2[0] == '\0')
        *res = 0;
    else if (s1[0] == s2[0])
    {
        int *res1 = malloc(sizeof(int));
        longestSubsequence(&s1[1], &s2[1], res1);
        *res = 1 + *res1;
    }
    else
    {
        int *res1 = malloc(sizeof(int));
        int *res2 = malloc(sizeof(int));

        struct data d1, d2;

        d1.s1 = &s1[1];
        d1.s2 = s2;
        d1.res = res1;

        d2.s1 = s1;
        d2.s2 = &s2[1];
        d2.res = res2;

        pthread_t tid[2];
        pthread_create(&tid[0], NULL, runner, &d1);
        pthread_create(&tid[1], NULL, runner, &d2);

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);

        *res = max(*res1, *res2);
    }
}

void *runner(void *params)
{
    struct data *d = params;
    longestSubsequence(d->s1, d->s2, d->res);
}

int main()
{
    char str1[100], str2[100];
    printf("Enter the strings\n");
    fgets(str1, 100, stdin);
    str1[strlen(str1) - 1] = '\0';
    fgets(str2, 100, stdin);
    str2[strlen(str2) - 1] = '\0';

    int *res = malloc(sizeof(int));
    longestSubsequence(str1, str2, res);
    printf("\nLength: %d\n", *res);
}