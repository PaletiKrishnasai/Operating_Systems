#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define MAX_PROCESSES 100

struct data
{
	int i;
	int flow;
};
// -----------------------------------------------------------
sem_t mutex;
int no_of_process = 1;
int flag = 1;
// -----------------------------------------------------------
int baboons_crossing = 0;			// No of baboons crossing currently
int current_flow_direction = 1;		// 1 or -1
int rope_capacity = 5;				// Max no of baboons on the rope allowed
int flow_changing = 0;				//  1 if flow is changing
int rope_broken = 0;				// 0 if no of baboons_crossing < rope_capacity
// -----------------------------------------------------------

void * runner(void * d)
{
	struct data *p = (struct data *)d;

	int passed = 0;
	do
	{
		//while(flag == 0 && passed == 1) printf("\t\t\t\tStuck - flag - %d (%d)...\n", p->i, p->flow);
		sleep(1);
		passed = 0;
		sem_wait(&mutex);

		if(p->flow != current_flow_direction)
		{
			//printf("\t\tIn flow != curdir - %d (%d), flowchange = %d...\n", p->i, p->flow, flow_changing);
			flow_changing = 1;
			while(baboons_crossing > 0 && current_flow_direction != p->flow);//printf("\t\t\t\tStuck - flow - %d (%d), crossing: %d, curdir: %d...\n", p->i, p->flow, baboons_crossing, current_flow_direction);
			flow_changing = 0;
			current_flow_direction = p->flow;
			flag = 1;
		}
		else
		{
			//printf("\t\tIn flow == curdir - %d (%d), flowchange = %d...\n", p->i, p->flow, flow_changing);
			if(flow_changing == 1)
			{
				while((flow_changing == 1 && current_flow_direction == p->flow) || (flow_changing == 0 && current_flow_direction != p->flow));
			}
		}
		// CS
		printf("ENTER B: %d - \t\tflow %d\t\t - \t\t%d / %d\n", p->i, current_flow_direction, baboons_crossing, rope_capacity);
		baboons_crossing++;
		//sleep(1);
		printf("EXIT B: %d - \t\tflow %d\t\t - \t\t%d / %d\n", p->i, current_flow_direction, baboons_crossing, rope_capacity);
		baboons_crossing--;
        // CS

		sem_post(&mutex);

		flag = 0;
		passed = 1;

	} while(1);

	pthread_exit(0);
}
// -----------------------------------------------------------

int main(int argc, char *argv[])
{
	printf("%d\n", (-6%5));
	//printf("------------------------------------ Baboon Crossing --------------------------------------\n");

	if(argc != 2) printf("Wrong number of parameters.\n");
	else
	{
		no_of_process = atoi(argv[1]);

		sem_init(&mutex, 0, rope_capacity);

		pthread_t tid[no_of_process];
		pthread_attr_t attr;
		pthread_attr_init(&attr);

    	srand(time(NULL));

		struct data d[no_of_process];

		for(int i=0;i<no_of_process;i++)
		{
			d[i].i = i;
			if(i%2 == 0) d[i].flow = 1;
			else d[i].flow = -1;
			pthread_create(&tid[i], &attr, runner, &d[i]);
		}

		for(int i=0;i<no_of_process;i++)
		{
			pthread_join(tid[i], NULL);
		}
	}
	printf("\n");
	//printf("------------------------------------ Baboon Crossing --------------------------------------\n");
	return 0;
}
