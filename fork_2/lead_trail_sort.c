#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{

    int size = 0;
    printf("Enter size of array: ");
    scanf("%d", &size);

    int mid = size / 2 - 1;

    printf("Enter the array: ");
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    int pid = fork();

    if (pid == 0)
    {
        printf("Sorted array: ");
        //printf("Leading Ascending order: ");

        for (int i = 0; i < mid + 1; i++)
        {
            int max_i = 0;
            for (int j = 0; j < mid + 1 - i; j++)
            {
                if (arr[j] > arr[max_i])
                {
                    max_i = j;
                }
            }
            int temp = arr[max_i];
            arr[max_i] = arr[mid + 1 - i - 1];
            arr[mid + 1 - i - 1] = temp;
        }

        for (int i = 0; i < mid + 1; i++)
            printf("%d ", arr[i]);

        //printf("\n");
        printf(" | ");
        return 0;
    }
    else if (pid > 0)
    {
        wait(NULL);
        //printf("Trailing Descending order: ");

        for (int i = mid + 1; i < size; i++)
        {
            int max_i = i;
            for (int j = i; j < size; j++)
            {
                if (arr[j] > arr[max_i])
                {
                    max_i = j;
                }
            }
            int temp = arr[max_i];
            arr[max_i] = arr[i];
            arr[i] = temp;
        }

        for (int i = mid + 1; i < size; i++)
            printf("%d ", arr[i]);

        printf("\n");
        return 0;
    }
}
