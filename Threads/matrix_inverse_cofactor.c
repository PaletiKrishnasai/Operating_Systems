#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#define MAX 100
int N;
int matrix[MAX][MAX];
int adjoint[MAX][MAX];
float inverse[MAX][MAX];

struct cell 
{
    int i;
    int j;

};
/* Function to get cofactor of matrix[p][q] in temp[][]. N is current
 dimension of matrix[][]*/
void cofactor(int mat[MAX][MAX], int temp[MAX][MAX],int p,int q,int n)
{
    int i=0,j=0;
    for(int row=0 ; row<n ; row++)
    {
        for(int col=0 ; col<n ; col++)
        {
            if(row!=p && col!=q)
            {
                temp[i][j++] = mat[row][col];
                if (j==n-1)
                {
                    j=0;
                    i++;
                }
            }
        }
    }
}

int determinant(int mat[MAX][MAX],int n)
{
    int D=0;
    if(n==1)
    return mat[0][0];

    int temp[N][N]; // To store cofactors
    int sign = 1;   // To store sign multiplier

    // Iterate for each element of first row
    for(int f=0 ; f<n ; f++)
    {
        cofactor(mat,temp,0,f,n);
        D += sign * mat[0][f] * determinant(temp,n-1);
        sign = -sign;
    }
    return D;
}

void *runner(void *param)
{
    int temp[N][N];
    int sign = 1;

    struct cell *data = param;
    cofactor(matrix,temp,data->i,data->j,N);
    sign = ((data->i + data->j)%2 == 0) ? 1 :-1;
    adjoint[data->j][data->i] = sign * (determinant(temp,N-1));
    pthread_exit(NULL);
}

int main()
{
    printf("Enter the order : \n");
    scanf("%d", &N);
    printf("Enter the matrix :\n");
    for (int i=0;i<N;i++)
    {
        for (int j=0;j<N;j++)
        {
            scanf("%d",&matrix[i][j]);
        }
    }
    printf("\nMatrix:\n");
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        printf("%d ",matrix[i][j]);
        printf("\n");
    }
    pthread_t tid[N*N];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    if (N == 1)
    {
        adjoint[0][0] = 1;
    }
    else
    {
        int k = 0;
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                struct cell *d = (struct cell *)malloc(sizeof(struct cell));

                d->i = i;
                d->j = j;

                pthread_create(&tid[k], &attr, runner, d);
                k++;
            }
        }
        for (int i = 0; i < k; i++)
            pthread_join(tid[i], NULL);
    }
    printf("\nAdjoint:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", adjoint[i][j]);
        printf("\n");
    }
    int det = determinant(matrix, N);
    if (det == 0)
    {
        printf("Inverse doesn't exist\n");
        return 0;
    }
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            inverse[i][j] = adjoint[i][j] / ((float)det);

    printf("Inverse:\n");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%f ", inverse[i][j]);
        printf("\n");
    }
    printf("\n");
    return 0;
}