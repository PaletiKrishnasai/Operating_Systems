#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX 100000

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        for (int k = 0; k < n; ++k)
            printf(" %d", arr[k]);
        printf("\n");
    }
}
void printArray1(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
    int i, j, pass = 0;
    for (i = 0; i < n - 1; i++)
    {
        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
        //pass++;
        //printf("  After pass %d:", pass);
        for (int k = 0; k < n; ++k)
            printf(" %d", arr[k]);
        printf("\n");
    }
}

/* Function to print an array */
void printArray2(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{
    srand(time(0));
    struct timeval start, stop;
    double secs = 0;
    //int output_fds = open("./output.txt", O_WRONLY);
    //dup2(output_fds, STDOUT_FILENO);
    int size, array1[MAX], array2[MAX];
    printf("Enter the size of the list : \n");
    scanf("%d", &size);
    for (int i = 0; i < size; i++)
    {
        array1[i] = rand() % size+1;
        array2[i] = array1[i];
    }
    printf("\nArray:");
    for (int i = 0; i < size; i++)
    {
        printf(" %d", array1[i]);
    }
    printf("\n");
    printf("--------------------------------------\n\n");

    gettimeofday(&start, NULL);

    insertionSort(array1, size);
    printf("\n");
    printArray1(array1, size);
    printf("--------------------------------------\n\n");
    printf("\n");
    bubbleSort(array2, size);
    printf("\n");
    printArray2(array2, size);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    printf("\n");
    printf("Execution time:  %f\n", secs);

    return 0;
}