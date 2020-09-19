#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    

    int size = 0;
    printf("Enter size of array: ");
    scanf("%d", &size);

    printf("Enter the array: ");
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    int pid = fork();

    if (pid == 0)
    {
        printf("\nDescending order: ");

        int pid2 = vfork();

        if (pid2 == 0)
        {
            for (int i = 0; i < size; i++)
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
            exit(0);
        }
        else if (pid2 > 0)
        {
            wait(NULL);
            for (int i = 0; i < size; i++)
                printf("%d ", arr[i]);

            printf("\n");
            return 0;
        }
    }
    else if (pid > 0)
    {
        wait(NULL);
        printf("\nAscending order: ");

        int pid2 = vfork();

        if (pid2 == 0)
        {
            for (int i = 0; i < size; i++)
            {
                int max_i = 0;
                for (int j = 0; j < size - i; j++)
                {
                    if (arr[j] > arr[max_i])
                    {
                        max_i = j;
                    }
                }

                int temp = arr[max_i];
                arr[max_i] = arr[size - i - 1];
                arr[size - i - 1] = temp;
            }
            exit(0);
        }
        else if (pid2 > 0)
        {
            wait(NULL);
            for (int i = 0; i < size; i++)
                printf("%d ", arr[i]);

            printf("\n");
            
            return 0;
        }
    }
}
