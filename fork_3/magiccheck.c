
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Returns 1 if mat[][] is magic
// square, else returns 0.
int isMagicSquare(int *mat, int N)
{
    // calculate the sum of
    // the prime diagonal
    int sum = 0, sum2 = 0;

    int diag_pid = vfork();
    if (diag_pid == 0)
    {
        for (int i = 0; i < N; i++)
            sum = sum + *((mat + i * N) + i);
        exit(0);
    }
    else if (diag_pid > 0)
    {
        wait(NULL);
        // the secondary diagonal
        for (int i = 0; i < N; i++)
            sum2 = sum2 + *((mat + i * N) + (N - 1 - i));

        if (sum != sum2)
            return 0;
    }

    int row_pid = vfork();
    if (row_pid == 0)
    {
        // For sums of Rows
        for (int i = 0; i < N; i++)
        {

            int rowSum = 0;
            for (int j = 0; j < N; j++)
                rowSum += *((mat + i * N) + j);

            // check if every row sum is
            // equal to prime diagonal sum
            if (rowSum != sum)
                return 0;
        }
        exit(0);
    }
    else if (row_pid > 0)
    {
        wait(NULL);
        // For sums of Columns
        for (int i = 0; i < N; i++)
        {

            int colSum = 0;
            for (int j = 0; j < N; j++)
                colSum += *((mat + j * N) + i);

            // check if every column sum is
            // equal to prime diagonal sum
            if (sum != colSum)
                return 0;
        }
    }

    return 1;
}

int main()
{
    int n, i, j;

    printf("Enter order of matrix:-\n");
    scanf("%d", &n);

    int A[n][n];
    printf("Enter matrix:-\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            scanf("%d", &A[i][j]);
        }
    }

  

    if (isMagicSquare((int *)A, n))
    {
        printf("Magic Square\n");
    }
    else if(isMagicSquare)
    {
        printf("Not a Magic Sqaure\n");
        
    }
    return 0;
}