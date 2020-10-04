#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>

#define DEFAULT 100

void odd_order(int n, int a[][DEFAULT])
{
    int i = n / 2;
    int j = n - 1;
    int p = n / 2;
    int q = 0;
    int split = ((n * n) / 2);
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0)
    {
        for (int num = 1; num <= split + 1;)
        {
            if ((i == -1) && (j == n))
            {
                i = 0;
                j = n - 2;
            }
            else
            {
                if (j == n)
                {
                    j = 0;
                }
                if (i < 0)
                {
                    i = n - 1;
                }
            }
            if (a[i][j])
            {
                j -= 2;
                ++i;
                continue;
            }
            else
            {
                a[i][j] = num;
                ++num;
            }
            ++j;
            --i;
        }
        exit(0);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            for (int num = n * n; num > split + 1;)
            {
                if ((p == n) && (q == -1))
                {
                    p = 0;
                    q = n - 2;
                }
                else
                {
                    if (q == -1)
                    {
                        q = n - 1;
                    }
                    if (p > n - 1)
                    {
                        p = 0;
                    }
                }
                if (a[p][q])
                {
                    q += 2;
                    --p;
                    continue;
                }
                else
                {
                    a[p][q] = num;
                    --num;
                }
                --q;
                ++p;
            }
            exit(0);
        }
        else if (pid2 < 0)
        {
            printf("\nForking failed\n");
            exit(0);
        }
    }
    else
    {
        printf("\nForking failed\n");
        exit(0);
    }
    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    return;
}

void singly_even_order(int n, int a[][DEFAULT])
{
    odd_order(n / 2, a);
    pid_t pid1, pid2, pid3;
    pid1 = fork();
    if (pid1 == 0)
    {
        for (int i = n / 2; i < n; ++i)
        {
            for (int j = n / 2; j < n; ++j)
            {
                a[i][j] = a[i - n / 2][j - n / 2] + (n * n / 4);
            }
        }
        exit(0);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            for (int i = 0; i < n / 2; ++i)
            {
                for (int j = n / 2; j < n; ++j)
                {
                    a[i][j] = a[i][j - n / 2] + (2 * n * n / 4);
                }
            }
            exit(0);
        }
        else if (pid2 > 0)
        {
            pid3 = fork();
            if (pid3 == 0)
            {
                for (int i = n / 2; i < n; ++i)
                {
                    for (int j = 0; j < n / 2; ++j)
                    {
                        a[i][j] = a[i - n / 2][j] + (3 * n * n / 4);
                    }
                }
                exit(0);
            }
            else if (pid3 < 0)
            {
                printf("\nForking failed\n");
                exit(0);
            }
        }
        else
        {
            printf("\nForking failed\n");
            exit(0);
        }
    }
    else
    {
        printf("\nForking failed\n");
        exit(0);
    }
    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    waitpid(pid3, &status, 0);
    int count;
    pid1 = fork();
    if (pid1 == 0)
    {
        for (int i = 0; i < n / 2; ++i)
        {
            int j = -1;
            if (i == n / 4)
            {
                ++j;
            }
            count = n / 4;
            for (; count > 0; ++j, --count)
            {
                int temp = a[i][j + 1];
                a[i][j + 1] = a[i + n / 2][j + 1];
                a[i + n / 2][j + 1] = temp;
            }
        }
        exit(0);
    }
    else if (pid1 > 0)
    {
        pid2 = fork();
        if (pid2 == 0)
        {
            count = n / 4 - 1;
            while (count > 0)
            {
                for (int i = 0; i < n / 2; ++i)
                {
                    int temp = a[i][n - count];
                    a[i][n - count] = a[i + n / 2][n - count];
                    a[i + n / 2][n - count] = temp;
                }
                --count;
            }
            exit(0);
        }
        else if (pid2 < 0)
        {
            printf("\nForking failed\n");
            exit(0);
        }
    }
    else
    {
        printf("\nForking failed...\n");
        exit(0);
    }

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    return;
}

void doubly_even_order(int n, int a[][DEFAULT])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            a[i][j] = (n * i) + j + 1;
        }
    }
    pid_t TLeft, TRight, BLeft, BRight, center;
    TLeft = fork();
    if (TLeft == 0)
    {
        for (int i = 0; i < n / 4; ++i)
        {
            for (int j = 0; j < n / 4; ++j)
            {
                a[i][j] = (n * n + 1) - a[i][j];
            }
        }
        exit(0);
    }
    else if (TLeft > 0)
    {
        TRight = fork();
        if (TRight == 0)
        {
            for (int i = 0; i < n / 4; ++i)
            {
                for (int j = 3 * (n / 4); j < n; ++j)
                {
                    a[i][j] = (n * n + 1) - a[i][j];
                }
            }
            exit(0);
        }
        else if (TRight > 0)
        {
            BLeft = fork();
            if (BLeft == 0)
            {
                for (int i = 3 * (n / 4); i < n; ++i)
                {
                    for (int j = 0; j < n / 4; ++j)
                    {
                        a[i][j] = (n * n + 1) - a[i][j];
                    }
                }
                exit(0);
            }
            else if (BLeft > 0)
            {
                BRight = fork();
                if (BRight == 0)
                {
                    for (int i = 3 * (n / 4); i < n; ++i)
                    {
                        for (int j = 3 * (n / 4); j < n; ++j)
                        {
                            a[i][j] = (n * n + 1) - a[i][j];
                        }
                    }
                    exit(0);
                }
                else if (BRight > 0)
                {
                    center = fork();
                    if (center == 0)
                    {
                        for (int i = (n / 4); i < 3 * (n / 4); ++i)
                        {
                            for (int j = n / 4; j < 3 * (n / 4); ++j)
                            {
                                a[i][j] = (n * n + 1) - a[i][j];
                            }
                        }
                        exit(0);
                    }
                    else if (center < 0)
                    {
                        printf("\nForking failed\n");
                        exit(0);
                    }
                }
                else
                {
                    printf("\nForking failed\n");
                    exit(0);
                }
            }
            else
            {
                printf("\nForking failed\n");
                exit(0);
            }
        }
        else
        {
            printf("\nForking failed\n");
            exit(0);
        }
    }
    else
    {
        printf("\nForking failed\n");
        exit(0);
    }
    int status;
    waitpid(TLeft, &status, 0);
    waitpid(TRight, &status, 0);
    waitpid(BLeft, &status, 0);
    waitpid(BRight, &status, 0);
    waitpid(center, &status, 0);
    return;
}

void print(int n, int a[][DEFAULT])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int n;
    printf("\nEnter the order of Magic square : ");
    scanf("%d", &n);
    int shm_id;
    key_t key = IPC_PRIVATE;
    shm_id = shmget(key, sizeof(int[n][n]), IPC_CREAT | 0666);
    int(*a)[n];
    if (shm_id < 0)
    {
        printf("\nSHM Failed\n");
        exit(0);
    }
    a = shmat(shm_id, 0, 0);
    if (a == (void *)-1)
    {
        printf("\nSHM Failed\n");
        exit(0);
    }
    if ((n <= 0) || (n == 2))
    {
        printf("\nMagic square not possible\n");
    }
    else if (n == 1)
    {
        printf("\nMagic square of Order %d\n", n);
        printf("1\n");
    }
    else if (n % 2 == 1)
    {
        printf("\nMagic square of Order %d\n", n);
        odd_order(n, a);
        print(n, a);
    }
    else if (n % 4 == 0)
    {
        printf("\nMagic square of Order %d\n", n);
        doubly_even_order(n, a);
        print(n, a);
    }
    else
    {
        printf("\nMagic square of Order %d\n", n);
        singly_even_order(n, a);
        print(n, a);
    }
    if (shmdt(a) == -1)
    {
        exit(0);
    }
    if (shmctl(shm_id, IPC_RMID, NULL) == -1)
    {
        exit(0);
    }
    return 0;
}
