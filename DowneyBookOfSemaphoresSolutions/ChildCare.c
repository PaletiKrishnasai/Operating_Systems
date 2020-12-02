//Child Care Problem from Downey Book of semaphores
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#define Nchildren 8
#define Nadult 3
int children = 4, adult = 2, children_waiting = 0, adult_exiting = 0; 
sem_t adultsem;
sem_t childrensem;
pthread_mutex_t mutex;
int minimum(int a, int b)
{
	if(a<b)
	    return a;
  	return b;
}
void * childThread()
{
	while(1)
	{
	pthread_mutex_lock(&mutex); 
  	if(children<3*adult)
  	{ 
    	children++;       
    	printf("Child enters the room\n Children = %d; Adults = %d; children_waiting = %d; adult_exiting = %d;\n\n",children, adult,children_waiting, adult_exiting);
    	pthread_mutex_unlock(&mutex);
  	}
  	else
  	{
    	children_waiting++;//The number of children trying to enter increases  
    	printf("A Child tried to enter\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult,children_waiting, adult_exiting);
    	//sleep(2);
    	pthread_mutex_unlock(&mutex);
    	sem_wait(&childrensem);
  	}
  	sleep(4);
  	pthread_mutex_lock(&mutex);
  	children--;
  	printf("Child exits\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, adult_exiting);
  	sleep(2);
  	if(adult_exiting && (children <= 3 * (adult - 1)))
  	{ 
    	adult_exiting--;
    	adult--;
     	printf("Adult Exited\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, adult_exiting);
    	sleep(2);
    	sem_post(&adultsem); 
  	}
  	if(children_waiting && (children < 3 * adult))
  	{ 
    	sem_post(&childrensem); 
    	children_waiting--;  
    	children++;   
   		printf("Child  tried to enter\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, adult_exiting);
    	sleep(2);
  	}
  	pthread_mutex_unlock(&mutex);
  	} 
  	pthread_exit(NULL);
}
void * adultThread()
{
	int n, i;
	while(1)
	{
	pthread_mutex_lock(&mutex); 
	adult++;
	printf("Adult enters\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, 		adult_exiting);
	if(children_waiting)
	{   
    	n = minimum(3, children_waiting); 
    	for(i=0;i<n;i++)
    	{
      	sem_post(&childrensem); 
      	children_waiting--; 
      	children++;
      	printf("Child enters\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, adult_exiting);
      	//sleep(2);
    	}
  	}
  	pthread_mutex_unlock(&mutex); 
  	sleep(4);
  	pthread_mutex_lock(&mutex);
  	if((children <= 3 * (adult - 1)) || ((adult > 1) && (children_waiting == 0 && children == 0)))
  	{
    	adult--;
    	printf("Adult Exits\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, adult_exiting);
    	sleep(2);
    	pthread_mutex_unlock(&mutex);
  	}
  	else
  	{
    	adult_exiting++;
    	printf("Adult tried to Exit\nChildren = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult, children_waiting, adult_exiting);
    	sleep(2);
    	pthread_mutex_unlock(&mutex);
    	sem_wait(&adultsem);
  	}
  	}
  	pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
	sem_init(&adultsem, 0, 0);
	sem_init(&childrensem, 0, 0);
	pthread_mutex_init(&mutex, NULL);
  	int nchildren, nadult, returning;
  	nchildren=1;
  	nadult=1;
  	printf("Program initial status \n\n Children = %d; adult = %d; children_waiting = %d; adult_exiting = %d;\n\n", children, adult,children_waiting, adult_exiting);
  	pthread_t* threadschildren = (pthread_t*) malloc(sizeof(pthread_t) * nchildren);
  	pthread_t* threadsadult = (pthread_t*) malloc(sizeof(pthread_t) * nadult);
  	for(int i=0; i<nchildren; i++)
  	{
    	returning = pthread_create(&threadschildren[i], NULL, childThread, NULL);
    	if (returning)
    	{  
      		printf("Error in thread creation!\n");
      		exit(0);
    	}
  	}
  	for(int i=0;i<nadult; i++)
  	{
    	returning=pthread_create(&threadsadult[i], NULL, adultThread, NULL);
    	if(returning)
    	{ 
      		printf("Error in thread creation!\n");
      		exit(0);
    	}
  	}
  	for(int i=0;i<nadult;i++)
    	pthread_join(threadsadult[i], NULL);
  	for(int i=0; i<nchildren; i++)
    	pthread_join(threadschildren[i], NULL);
  	free(threadschildren);
  	free(threadsadult);
  return 0;
}
