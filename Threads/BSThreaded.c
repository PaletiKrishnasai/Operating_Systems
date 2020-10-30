#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

int arr[100];
int pos = -1;
struct data
{
    int beg;
    int end;
    int x;
};
void *BinarySearchMultiple(void *d)
{
    struct data *dm = d;
    int beg = dm->beg;
    int end = dm->end;
    int x = dm->x;


    if (beg < end)
    {
        int mid = (beg + end) / 2;

        if (arr[mid] == x)
        {
            pos = mid;
        }
        else
        {
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);

            struct data d;
            d.x = x;

            if (x < arr[mid])
            {
                d.beg = beg;
                d.end = mid;
            }
            else if (x > arr[mid])
            {
                d.beg = mid + 1;
                d.end = end;
            }

            pthread_create(&tid, &attr, BinarySearchMultiple, &d);

            pthread_join(tid, NULL);
        }
    }
    pthread_exit(0);
}

void Display(int x)
{
    printf("'%d' found at indices: ", x);
    int lend = 0;
    while (lend >= 0)
    {
        if (arr[pos - lend] == x)
        {
            printf("%d ", pos - lend);
            lend++;
        }
        else
            lend = -1;
    }

    int rend = 1;
    while (rend >= 1)
    {
        if (arr[pos + rend] == x)
        {
            printf("%d ", pos + rend);
            rend++;
        }
        else
            rend = -1;
    }
}

int main(int argc, char *argv[])
{

    if (argc < 3)
        printf("Usage: ./a.out <key> <list>\n");
    else
    {
        int n = argc - 2;

        for (int i = 0; i < n; i++)
        {
            arr[i] = atoi(argv[2 + i]);
        }

        // Sort the array
        
		for(int i=0;i<n-1;i++) {
			for(int j=0;j<n-i-1;j++) {
				if(arr[j] > arr[j+1])
				{
					int temp = arr[j];
					arr[j] = arr[j+1];
					arr[j+1] = temp;
				}
			}
		}
        printf("Sorted list : ");
		for(int i=0;i<n;i++) printf("%d ", arr[i]);
		printf("\n");

        struct data d[4];
        d[0].beg = 0;
        d[0].end = n / 4 - 1;
        d[0].x = atoi(argv[1]);
        d[1].beg = n / 4;
        d[1].end = n / 2 - 1;
        d[1].x = atoi(argv[1]);
        d[2].beg = n / 2;
        d[2].end = 3 * n / 4 - 1;
        d[2].x = atoi(argv[1]);
        d[3].beg = 3 * n / 4;
        d[3].end = n - 1;
        d[3].x = atoi(argv[1]);

        pthread_t tid[4];
        pthread_attr_t attr;
        pthread_attr_init(&attr);

        for (int i = 0; i < 4; i++)
        {
            pthread_create(&tid[i], &attr, BinarySearchMultiple, &d[i]);
        }

        for (int i = 0; i < 4; i++)
        {
            pthread_join(tid[i], NULL);
        }

        if (pos > -1)
            Display(atoi(argv[1]));
        else
            printf("\n%d not found\n", atoi(argv[1]));

        printf("\n");
    }

}
