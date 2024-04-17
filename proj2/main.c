#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

int *buffer;	//Buffer with size from input how to get?
int count = 0;
int in = 0;
int out = 0;
int num_buffer = 0;
int num_producers = 0;
int num_consumers = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg);
void *consumer(void *arg);

int total_stuff;
int remaider;
int extra_rem;

struct thread_data 
{
	int thread_id;
	int items;

};

struct thread_data thread_data_array[];

int main(int argc, char* argv[]) {

	num_buffer = atoi(argv[1]);
	num_producers = atoi(argv[2]);
	num_consumers = atoi(argv[3]);

	pthread_t producers[num_producers];
	int producer_ids[num_producers];
	int consumer_ids[num_consumers];

	thread_data_array[num_consumers];
	
	buffer = (int *)malloc(num_buffer * sizeof(int));

	srand(time(NULL));

	total_stuff = 2*num_buffer*num_producers;
	remaider = total_stuff/num_consumers;
	extra_rem = total_stuff%num_consumers;

	//struct thread_data_array.value = 1;

	for(int i = 0; i < num_producers; i++)
	{
		
		producer_ids[i] = i;													//Change producer_ids to (void *)&thread_data_array with all of the items set to it
		pthread_create(&producers[i], NULL, *producer, (&producer_ids[i]));		//instead of &producer_ids[i] pass in (void *)&consumer_vales[i]
																				//An array that holds all of the info each consumer/producer needs
		printf("Main: started producer %d\n", i);

	}

	pthread_t consumers[num_consumers];
	for(int i = 0; i < num_consumers; i++)
	{
		if(i == 0)
		{
			thread_data_array[i].items = remaider + extra_rem;
		}
		else
		{
			thread_data_array[i].items = remaider;
		}
		thread_data_array[i].thread_id = i;
		
		consumer_ids[i] = i;
		pthread_create(&consumers[i], NULL, *consumer, (void *)&thread_data_array[i]);
		printf("Main: started consumer %d\n", i);

	}


	for(int i = 0; i < num_producers; i++)
	{
		pthread_join(producers[i], NULL);
		printf("Main: producer %d joined\n", i);
	}

	for(int i = 0; i < num_consumers; i++)
	{
		pthread_join(consumers[i], NULL);
		printf("Main: consumer %d joined\n", i);
	}

	printf("Main: Program completed\n");

}

void *producer(void *arg)		//Need to pass in multiple amounts of info not just the one value
								//Need argumanet tot be the address of a structure which holds all the info I need each thread
								//
{
	int pid = *((int *)arg);

	for(int i = 0; i < 2 * num_buffer; i++)
	{
		sleep(rand() %2 + 1);
		int rand_num = rand() % 10 +1;
		printf("P%d: Producing %d values\n", pid, rand_num);

		pthread_mutex_lock(&mutex);

		while(count == num_buffer)
		{
			printf("P%d: Blocked due to full buffer\n", pid);
			pthread_cond_wait(&empty, &mutex);
			printf("P%d: done waiting on full buffer\n", pid);
		}

		buffer[in] = rand_num;
		printf("P%d: Writing %d to position %d\n", pid, rand_num, in);
		in = (in +1) % num_buffer;
		count++;

		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&full);

	}

	printf("P%d: Exiting\n", pid);
	pthread_exit(NULL);

}

void *consumer(void *threadarg)
{
	int cid, item;
	struct thread_data *my_data;

	my_data = (struct thread_data *) threadarg;
	cid = my_data->thread_id;
	item = my_data->items;

	int value = buffer[out];
	printf("C%d: Consuming %d values\n", cid, value);
	
	for(int i = 0; i < item; i++ )
	{
		sleep(rand() % 2 + 1);

		pthread_mutex_lock(&mutex);
        while (count == 0) {
            printf("C%d: Blocked due to empty buffer\n", cid);
            pthread_cond_wait(&full, &mutex);
			printf("C%d: done waiting on empty buffer\n", cid);
        }
        int value = buffer[out];
        printf("C%d: Reading %d from position %d\n", cid, value, out);
        out = (out + 1) % num_buffer;
        count--;

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&empty);
    }

	printf("C%d: Exiting\n", cid);
	pthread_exit(NULL);

}

