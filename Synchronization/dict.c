#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
#include <stdlib.h>
#define SHARED 1

//pete algo vars
int flag[2];
int turn;
//sem vars for buffer
sem_t empty,full;

struct node
{
    char word_s[1000];
    int index;
    int half;
};

//dict vars
char word[100][1000];
char primary[100][1000];
char secondary[100][1000];
int size;

void lock_ini()
{
    flag[0]=0;
    flag[1]=0;
    turn=0;
}


void swap_word(int i,int j)
{
    char temp[1000]="";
    strcpy(temp,word[i]);
    strcpy(word[i],word[j]);
    strcpy(word[j],temp);
}
void swap_p(int i,int j)
{
    char temp[1000]="";
    strcpy(temp,primary[i]);
    strcpy(primary[i],primary[j]);
    strcpy(primary[j],temp);
}
void swap_s(int i,int j)
{
    char temp[1000]="";
    strcpy(temp,secondary[i]);
    strcpy(secondary[i],secondary[j]);
    strcpy(secondary[j],temp);
}

void bubblesort(int ch,int start ,int end)
{
int i,j;
for(i=start;i<end-1;i++)
{
for(j=start;j<end-(i-start)-1;j++)
{

int choice=(ch==0)?(strcmp(word[j],word[j+1])<0):(strcmp(word[j],word[j+1])>0);
if(choice==1)
{
swap_word(j,j+1);
swap_p(j,j+1);
swap_s(j,j+1);

}
}
}
}

int bs(int start,int end,char key[1000])
{

while(start<=end)
{
int mid=start+(end-start)/2;
if(strcmp(word[mid],key)==0)
return mid;
else if(strcmp(word[mid],key)<0)
start=mid+1;
else
end=mid-1;
}
return -1;
}

void lock(int index)
{
    flag[index]=1;
    turn=1-index;
    while(flag[1-index]==1 && turn==1-index);
}
void unlock(int index)
{
    flag[index]=0;
}

void create_dict()
{

    FILE *fp=fopen("dict.txt","r");
    char c=fgetc(fp);
    //while(c!=feof(fp))
    for(int i=0;i<size;i++)
    {
       int index=0;
      while(c!=';')
        {
            word[i][index++]=c;
            c=fgetc(fp);

        }
        index=0;
        c=fgetc(fp);
        while(c!=';')
        {
            primary[i][index++]=c;
            c=fgetc(fp);
            
        }
        index=0;
        c=getc(fp);
        while(c!='$')
        {
            secondary[i][index++]=c;
            c=fgetc(fp);

        }
        for(int j=0;j<2;j++)
            c=fgetc(fp);

     for(int j=0;j<i;j++)
        {
            if(strcmp(word[j],word[i])==0)
            {
                memset(word[i],0,sizeof(word[i]));
                memset(primary[i],0,sizeof(primary[i]));
                memset(secondary[i],0,sizeof(secondary[i]));
                size-=1;
                i-=1;
                
            }
        }

    }
}
void findsize()
{
    FILE *fp=fopen("dict.txt","r");
    char c;
    for (c = getc(fp); c != EOF; c = getc(fp)) 
        if (c == '\n') // Increment count if this character is newline 
            size+=1; 
    fclose(fp);
}
void *producer()
{
findsize();
sem_wait(&empty);
//entry-section
       lock(0);
           //cs start
                    //assume data to the new producer no
                   create_dict();
           //cs end
       unlock(0);
//exit section
sem_post(&full);

 pthread_exit(NULL);
}

void* process(void *arg)
{
   struct node *temp=(struct node*)arg;
   
   if(temp->half==1)
   {
       bubblesort(1,0,size/2);
       temp->index=bs(0,size/2-1,temp->word_s);
       
   }
   else
   {
       bubblesort(1,size/2,size);
        temp->index=bs(size/2,size-1,temp->word_s);
      
    }
   
   pthread_exit(NULL);
}

void search()
{
  
   pthread_t pth[2];

   struct node* keys=(struct node*)malloc(2*sizeof(struct node));
    printf("Enter the word to be searched in 1st half:\n");
    scanf("%s",keys[0].word_s); 

    printf("\nEnter the word to be searched in 2nd half:\n");
    scanf("%s",keys[1].word_s); 
    keys[0].half=1;
    keys[1].half=2;

    pthread_create(&pth[0],NULL,process,&keys[0]);
    pthread_create(&pth[1],NULL,process,&keys[1]);  

    for(int i=0;i<2;i++)
    {
   pthread_join(pth[i],NULL);   
    }
     if(keys[0].index!=-1)
       {
            printf("\nWord Found By the Consumer in 1st Half:\n\nWord:%s\nPrimary Meaning:%s\nSecondary Meaning:%s\n\n",word[keys[0].index],primary[keys[0].index],secondary[keys[0].index]);
       }
       else
         printf("Word Not found By the Consumer as its not in the Dictionary(1st half)!!!\n\n");

    if(keys[1].index!=-1)
       {
            printf("\nWord Found By the Consumer in 2nd Half:\n\nWord:%s\nPrimary Meaning:%s\nSecondary Meaning:%s\n\n",word[keys[1].index],primary[keys[1].index],secondary[keys[1].index]);
       }
       else
         printf("Word Not found By the Consumer as its not in the Dictionary(2nd half)!!!\n\n");
}
void *consumer()
{ 

sem_wait(&full);
//entry-section
       lock(1);
              //cs start
                     search();
             //cs end
       unlock(1);
//exit section
sem_post(&empty);

 pthread_exit(NULL);
}

//empty to check whether buffer is empty;default 1
//full to check whether buffer is full;default 0
//lock is mutext lock;default 1

int main()
{

    pthread_t p1,c1;
    lock_ini();
    sem_init(&empty,SHARED,1);
    sem_init(&full,SHARED,0);

    pthread_create(&p1,NULL,producer,NULL);
    pthread_create(&c1,NULL,consumer,NULL);

    pthread_join(p1,NULL);
    pthread_join(c1,NULL);

    printf("\nStopped\n");

}