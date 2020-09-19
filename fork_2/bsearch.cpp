#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;
int main()
{
    int size;
    printf("Enter the size of the list : \n");
    scanf("%d",&size);
    int key;int count=0,count1=0;
    int arr[size];
    printf("Enter the list : \n");
    for(int i=0; i<size ;i++)
    scanf("%d",&arr[i]);
    printf("Enter the key : \n");
    scanf("%d",&key);
    int beg,end;
    int mid=size/2;

    pid_t pid;
    pid = vfork();

    if(pid==0)
    {
        sort(arr,arr+size/2);
        
        beg = 0;
        end = mid;
        for(int i=0;i<end;i++)
        printf("%d",arr[i]);
        printf("\n");
      //printf("%d  %d ",beg,end);
        while(beg<=end)
        {
            int mid_temp = (beg + end) / 2;
            //printf("%d\n",mid_temp);
            if(arr[mid_temp]==key)
            {
                count++;
                for(int i=mid_temp+1;i<end;i++)
                {
                    if(arr[i]==key)
                    count++;
                    else break;
                }
                for(int i=beg;i<mid_temp;i++)
                {
                    if(arr[i]==key)
                    count++;
                    else break;
                } 
                break;
            }
            else if (arr[mid_temp] < key)
                beg = mid_temp + 1;
            else end = mid_temp-1;
        }
        printf("%d occurs %d times in first half\n",key,count);

        exit(0);
    }

    else if (pid > 0)
    {
        wait(NULL);
        sort(arr+size/2,arr+size);
        beg=mid;
        end=size;
        for (int i = beg; i < end; i++)
            printf("%d", arr[i]);
        printf("\n");
        //printf("%d  %d ",beg,end);
        while (beg <= end)
        {
            int mid_temp = (beg + end) / 2;
            //printf("%d\n", mid_temp);
            if (arr[mid_temp] == key)
            {
                count1++;
                for (int i = mid_temp + 1; i < end; i++)
                {
                    if (arr[i] == key)
                        count1++;
                    else
                        break;
                }
                for (int i = beg; i < mid_temp; i++)
                {
                    if (arr[i] == key)
                        count1++;
                    else
                        break;
                }
                break;
            }
            else if (arr[mid_temp] < key)
                beg = mid_temp + 1;
            else
                end = mid_temp - 1;
        }
        printf("%d occurs %d times in second half\n", key, count1);
    }



    return 0;
}