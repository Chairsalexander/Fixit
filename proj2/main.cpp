#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <queue>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

int buffer[];	//Buffer with size from input how to get?
int count = 0;
int in = 0;
int out = 0;
int num_buffer = NULL;
int num_producers = NULL;
int num_consumers = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

int main(int argc, char* argv[]) {

	int num_producers = *argv[2];
	int num_consumers = *argv[3];
	int num_buffer = *argv[1];

	pthread_t producers[num_producers];
	pthread_t consumers[num_consumers];
	int producer_ids[num_producers];
	int consumer_ids[num_consumers];
	buffer[num_buffer];

	srand(time(NULL));


	for(int i = 0; i < num_producers; i++)
	{
		producer_ids[i] = i;
		pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
	}

	for(int i = 0; i < num_consumers; i++)
	{
		consumer_ids[i] = i;
		pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
	}


	for(int i = 0; i < num_producers; i++)
	{
		pthread_join(producers[i], NULL);
		printf("Main: producer m%d joined\n", i);
	}

	for(int i = 0; i < num_consumers; i++)
	{
		pthread_join(consumers[i], NULL);
		printf("Main: consumer m%d joined\n", i);
	}

	printf("Main: Program completed\n");

}

void *producer(void *arg)
{
	int pid = *((int *)arg);
	printf("Main: started producer %d\n", pid);

	for(int i = 0; i < num_consumers; i++)
	{
		sleep(rand() %2 + 1);
		int rand_num = rand() % 10 +1;
		printf("P%d: Producing %d value\n", pid, rand_num);

		pthread_mutex_lock(&mutex);

		while(count == num_buffer)
		{
			printf("P%d: Blocked due to full buffer\n");
			pthread_cond_wait(&empty, &mutex);
		}

		buffer[in] = rand_num;
		printf("P%d: Writing %d to position %d\n", pid, rand_num, in);
		in = (in +1) % num_buffer;
		count++;

		pthread_mutex_unlock(&mutex);
		pthread_cond_signal(&full);

	}

}

void *consumer(void *arg)
{
	int cid = *((int *)arg);
	printf("Main: started consumer %d\n", cid);

	for(int i = 0; i < num_consumers; i++ )
	{
		sleep(rand() % 2 + 1);

		pthread_mutex_lock(&mutex);
        while (count == 0) {
            printf("C%d: Blocked due to empty buffer\n", cid);
            pthread_cond_wait(&full, &mutex);
        }
        int item = buffer[out];
        printf("C%d: Consuming %d values\n", cid, item);
        printf("C%d: Reading %d from position %d\n", cid, item, out);
        out = (out + 1) % num_buffer;
        count--;

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&empty);
    }
    pthread_exit(NULL);
}

