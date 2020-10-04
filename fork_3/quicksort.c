#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void quicksort(int number[], int first, int last)
{
    int i, j, pivot, temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (number[i] <= number[pivot] && i < last)
                i++;
            while (number[j] > number[pivot])
                j--;
            if (i < j)
            {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }

        temp = number[pivot];
        number[pivot] = number[j];
        number[j] = temp;

        if (vfork() == 0)
        {
            quicksort(number, first, j - 1);
            exit(0);
        }
        quicksort(number, j + 1, last);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main()
{

    int n;
    printf("Enter size of array:-\n");
    scanf("%d", &n);

    int arr[n];
    printf("Enter array elements:-\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Given array is \n");
    printArray(arr, n);

    quicksort(arr, 0, n - 1);

    printf("\nSorted array is \n");
    printArray(arr, n);
    return 0;
}
