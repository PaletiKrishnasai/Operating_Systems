#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
    int n1, n2, n3;
    printf("Enter no. of rows of first matrix: ");
    scanf("%d", &n1);

    printf("Enter no. of rows of second matrix: ");
    scanf("%d", &n2);

    printf("\n Enter no. of columns of second matrix: ");
    scanf("%d", &n3);

    int i, j, k;

    int a[n1][n2], b[n2][n3], c[n1][n3];

    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n3; j++)
        {
            c[i][j] = 0;
        }
    }

    printf("Enter matrix a \n");

    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n2; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    printf("\n");

    printf("Enter matrix b \n");

    for (i = 0; i < n2; i++)
    {
        for (j = 0; j < n3; j++)
        {
            scanf("%d", &b[i][j]);
        }
    }

    pid_t child;

    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n3; j++)
        {
            child = vfork();
            if (child == 0)
            {
                for (k = 0; k < n2; k++)
                {
                    c[i][j] += a[i][k] * b[k][j];
                }
                exit(0);
            }
        }
    }

    printf("\nProduct of the two matrices is \n");

    for (i = 0; i < n1; i++)
    {
        for (j = 0; j < n3; j++)
        {
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}
