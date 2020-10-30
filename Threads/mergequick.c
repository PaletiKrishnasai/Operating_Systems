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
int qarray[MAX];
int marray[MAX];

struct data 
{
    int beg;
    int end;
};

int Partition(int beg, int end)
{
    int i = beg, j = end;
    int p;
    p = beg;

    int val = p;
    while (i < j)
    {
        while (qarray[p] >= qarray[i] && i < end)
        {
            i++;
        }
        while (qarray[p] < qarray[j] && j > beg)
        {
            if (j == p + 1 && i <= p)
                j = p - 1;
            //if(j!=beg)j--;
            else
                j--;
        }
        if (i < j)
        {
            int temp = qarray[i];
            qarray[i] = qarray[j];
            qarray[j] = temp;
        }
    }
    int temp = qarray[p];
    qarray[p] = qarray[j];
    qarray[j] = temp;
    val = j;
    return val;
}

void *QuickSort(void *arg)
{
    struct data *temp = arg;
    int beg = temp->beg;
    int end = temp->end;

    if (beg < end)
    {
        int j = Partition(beg, end);

        struct data left;
        left.beg = beg;
        left.end = j - 1;
        struct data right;
        right.beg = j + 1;
        right.end = end;

        pthread_t tid[2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        pthread_create(&tid[0], &attr, QuickSort, &left);
        pthread_create(&tid[1], &attr, QuickSort, &right);

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
    }

    pthread_exit(0);
}

void MergeArray(int beg, int mid, int end)
{
    int n1 = mid - beg + 1;
    int n2 = end - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = marray[beg + i];
    for (int j = 0; j < n2; j++)
        R[j] = marray[mid + 1 + j];

    int i = 0, j = 0, k = beg;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            marray[k] = L[i];
            i++;
        }
        else
        {
            marray[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        marray[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        marray[k] = R[j];
        j++;
        k++;
    }
}

void *MergeSort(void *arg1)
{
    struct data *temp1 = arg1;
    int beg = temp1->beg;
    int end = temp1->end;

    if (beg < end)
    {
        int mid = (beg + end) / 2;

        struct data left;
        left.beg = beg;
        left.end = mid;
        struct data right;
        right.beg = mid + 1;
        right.end = end;

        pthread_t tid[2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        pthread_create(&tid[0], &attr, MergeSort, &left);
        pthread_create(&tid[1], &attr, MergeSort, &right);

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);

        MergeArray(beg, mid, end);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[])
{

    if (argc < 2)
        printf("Usage: ./a.out <list of numbers>\n");
    else
    {
        int size = argc - 1;

        for (int i = 0; i < size; i++)
        {
            qarray[i] = atoi(argv[1 + i]);
            marray[i] = atoi(argv[1 + i]);
        }

        struct data param;
        param.beg = 0;
        param.end = size - 1;

        pthread_t tid[2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        pthread_create(&tid[0], &attr, MergeSort, &param);
        pthread_create(&tid[1], &attr, QuickSort, &param);

        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);

        printf("Merge Sort: ");

        for (int i = 0; i < size; i++)
            printf("%d ", qarray[i]);

        printf("\n");

        printf("Quick Sort: ");

        for (int i = 0; i < size; i++)
            printf("%d ", marray[i]);

        printf("\n");
    }
    return 0;
}
