#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define MAX_SIZE 100

int num_processes = 0;

struct process {
	int processID;
	int burst_time;
	int priority;
	int arrival_time;
	int starting_time;
	int finishing_time;
	int turnaround_time;
	int waiting_time;
};
struct Queue {
  int front;
  int rear;
  int size;
  int *array;
};

void createQueue(struct Queue *queue) {
  queue->front = -1;
  queue->rear = -1;
  queue->size = 0;
  queue->array = (int *)malloc(MAX_SIZE * sizeof(int));
}

void enqueue(struct Queue *queue, int data) {
  if (queue->rear == MAX_SIZE - 1) {
    printf("Queue is full\n");
    return;
  }

  queue->rear++;
  queue->array[queue->rear] = data;
  queue->size++;
}

int dequeue(struct Queue *queue) {
  if (queue->front == queue->rear) {
    printf("Queue is empty\n");
    return -1;
  }

  queue->front++;
  return queue->array[queue->front];
}

void initprocess(struct process * p) {
	//struct process * p = (struct process *)malloc(sizeof(struct process));
	p = (struct process *)malloc(sizeof(struct process));
	p->burst_time = 0;//p.burst_time = 0;
	p->priority = 0;//p.priority = 0;
	p->arrival_time = 0;//	p.arrival_time = 0;
	p->starting_time = 0; //p.starting_time = 0;
	p->finishing_time = 0; //p.finishing_time = 0;
	p->turnaround_time = 0; //p.turnaround_time = 0;
	//return *p;
}

void readContents(char * file, struct process * processes) {
	FILE * fp;
	int index=0;
	fp = fopen(file, "r");
	printf("READ CONTENTS: \n");
	if (fp==NULL) {
		printf("File cannot be opened.");
	}

	char line[100];
	char * token;
	/*while (fscanf(fp,"%d %d %d\n", &processes[index], &priorities[index], &arrival_times[index])) {
		index++;
		printf("%d\n", index);
	}*/
	while (fgets(line, sizeof(line), fp)!=NULL) {
		//printf("\nline: %s\n", line);
		//index = 0;
		token = strtok(line, " ");
		initprocess(&processes[index/3]);
		while ( token != NULL ) {
			switch(index%3) {
				case 0:
					processes[index/3].burst_time = atoi(token);
					token = strtok(NULL, " ");
					break;
				case 1:
					processes[index/3].priority = atoi(token);
					token = strtok(NULL, " ");
					break;
				case 2:
					processes[index/3].arrival_time = atoi(token);
					token = strtok(NULL, " ");
					break;
				default:
					break;
			}
			processes[index/3].processID = index/3;
			index++;
			num_processes = index/3-1;
		}
	}
	printf("READING PROCESSES:\n");
	//processes = (struct process *)malloc(index/3 * sizeof(struct process));
	for (int i=0; i<num_processes+1; i++) {
		printf("processID: %d\n", processes[i].processID);
		printf("burst time: %d\n", processes[i].burst_time);
		printf("priority: %d\n", processes[i].priority);
		printf("arrival time: %d\n\n", processes[i].arrival_time);		
	}
	fclose(fp);
}

int itemAt(int * array, int item) {
	int length = sizeof(*array)/sizeof(item);
	for (int i=0; i<length; i++) {
		if (array[i]==item) {
			return i;
		}
	}
	return -1;
}

void STCF(struct process * processes, int num_proc) {
  int current_time = 0;
  int completed_proc = 0;
  int running_proc_ind = -1;
  int context_switches = 0;
  int ready_Queue[num_proc];
  int Q_index = 0;
  //ready_Queue[0] = processes[0].processID;
  int flag = 0;

  printf("***** STCF Scheduling *****\n");
  while((completed_proc < num_proc))
  {//Need soemthign to keep track of readyqueue
    ready_Queue[num_proc];
    //First find process with shortest remanding burst time
    int shortestBT = 99999;
    int shortestBT_Index = -1;
    for(int i = 0; i < num_proc; i++)
    {
        if((processes[i].burst_time > 0) && (processes[i].arrival_time <= current_time) && (processes[i].burst_time < shortestBT))
    	{
        	shortestBT = processes[i].burst_time;
        	shortestBT_Index = i;
        }
    }
	
	if(flag == 0)
	{
		printf("\nt2 = %d:\n", current_time);
    	printf("CPU: ");
	}
	
	if(running_proc_ind != -1){
        if(running_proc_ind != shortestBT_Index)
				{
					printf("Preempting process %d (remaining CPU burst = %d);  loading process %d (CPU burst = %d)\n", processes[running_proc_ind].processID, processes[running_proc_ind].burst_time, processes[shortestBT_Index].processID, processes[shortestBT_Index].burst_time);
                	running_proc_ind = shortestBT_Index;
                	context_switches = context_switches + 1;
					//Q_index = Q_index + 1;
					ready_Queue[Q_index] = processes[running_proc_ind].processID;
					Q_index = Q_index + 1;
					processes[running_proc_ind].burst_time = processes[running_proc_ind].burst_time - 1;
				}
		else{
					printf("1 Running process %d (remaining CPU burst = %d)", processes[running_proc_ind].processID, processes[running_proc_ind].burst_time);
					processes[running_proc_ind].burst_time = processes[running_proc_ind].burst_time - 1;

				}

				printf("\nReady Queue:1 ");
		 for(int i = 0; i < num_proc ; i++)
    	  {
    	   	if((processes[i].arrival_time <= current_time) && (processes[i].burst_time > 0))
        	{
            	printf("%d", processes[i].processID);
        		if(i < completed_proc)
            	{
                	printf("-");
            	}
        	}
    	}
		printf("\n");
    }
    else{
          printf("Loading process %d (CPU burst = %d)", processes[shortestBT_Index].processID, processes[shortestBT_Index].burst_time);
		  running_proc_ind = shortestBT_Index;
		  shortestBT_Index = -1;
		  processes[running_proc_ind].burst_time = processes[running_proc_ind].burst_time - 1;
		  context_switches = context_switches + 1;
		  //Q_index = Q_index + 1;
		  ready_Queue[Q_index] = processes[running_proc_ind].processID;
		  Q_index = Q_index + 1;
		  flag = 0;

		  printf("\nReady Queue:2 ");
		  int num =0;
		  for(int j = 0; j < num_proc - completed_proc ; j++)
    	  {
			shortestBT = 99999;
			
				for(int i = 0; i < num_proc; i++)
    			{
					
        			if((processes[i].burst_time > num) && (processes[i].arrival_time <= current_time) && (processes[i].burst_time < shortestBT))
    				{
        				shortestBT = processes[i].burst_time;
        				shortestBT_Index = i;
        			}
    			}
				num = processes[shortestBT_Index].burst_time;
				//if(j < completed_proc)
				//{
					printf("%d", processes[shortestBT_Index].processID);
				//}
        		if(j < completed_proc - 1)
            	{
                	printf("-");
            	}
    	}
		printf("\n");
    }
	

    if(shortestBT_Index != -1)
    {
        current_time = current_time + 1;
		
        if(processes[shortestBT_Index].burst_time == 0)
        {
            printf("\n\nt3 = %d\n", current_time);
            printf("CPU: finishing process %d; ", processes[shortestBT_Index].processID);
            processes[shortestBT_Index].finishing_time = current_time;
            processes[shortestBT_Index].turnaround_time = processes[shortestBT_Index].finishing_time - processes[shortestBT_Index].arrival_time;
            completed_proc++;
		
			processes[shortestBT_Index].waiting_time = processes[shortestBT_Index].turnaround_time - processes[shortestBT_Index].burst_time; // Corrected waiting time calculation
            ready_Queue[Q_index] = processes[shortestBT_Index].processID;
			running_proc_ind = -1;      //Acts as a reset
			flag = -1;
        }
         
		 if(flag == 0)
		 {
			int num =0;
		 	printf("Ready queue:3 ");
		 	for(int j = 0; j < num_proc - completed_proc ; j++)
    	  	{
			shortestBT = 99999;
			
				for(int i = 0; i < num_proc; i++)
    			{
					
        			if((processes[i].burst_time > num) && (processes[i].arrival_time <= current_time) && (processes[i].burst_time < shortestBT))
    				{
        				shortestBT = processes[i].burst_time;
        				shortestBT_Index = i;
        			}
    			}
				if((processes[j].burst_time > num) && (processes[j].arrival_time <= current_time) && (processes[j].burst_time < shortestBT))
				{

				}
				num = processes[shortestBT_Index].burst_time;
				
				if(processes[j].processID != processes[j - 1].processID)
				{
					printf("%d", processes[shortestBT_Index].processID);
				}
        		if(j < completed_proc)
            	{
                	printf("-");
            	}
    	}
		 printf("\n");
		 }
		
      }
      else{
          current_time++;
      }
  }

  printf("\n\n");
  printf("*********************************************************\n");
  printf("STCF Summary (WT = wait time, TT = turnaround time):\n");
  printf("PID     WT      TT\n");
  int total_wait = 0, total_turnaround = 0;
  for(int i = 0; i < num_proc; i++)
  {
      printf("%d      %d      %d\n",processes[i].processID, processes[i].waiting_time, processes[i].turnaround_time );
      total_wait= total_wait + processes[i].turnaround_time - processes[i].burst_time;
      total_turnaround = total_turnaround + processes[i].turnaround_time;
  }
  printf("AVG      %.2f         %.2f", (float)total_wait/num_proc, (float)total_turnaround/num_proc);
  printf("\nProcess sequence: ");
  for(int i = 0; i < Q_index; i++)
		 {
			printf("%d", ready_Queue[i]);
			if(i < Q_index - 1)
            	{
                	printf("-");
            	}
		 }
		 printf("\n");
  printf("Contex Switches: %d\n", context_switches);
}



void RR(struct process * processes, int num_proc) {
	int current_time = 0;
	int contex_switch = 0;
	int completed_procs = 0;
	int next_proc_index = 0;
	int quantum = 2;
	int current_POS = -1;
	struct Queue queue;
  	createQueue(&queue);

	

	printf("****** Round Robin Scheduling *******\n");
	while( completed_procs < num_proc )
	{
		int index = 0;
		int max = 100;
		int queue_ARR[max];
		int size = sizeof(queue_ARR)/sizeof(queue_ARR[0]);
		printf("%d, %d", size, sizeof(queue_ARR));
		
		for(int y = 0; y < num_proc; y++)
		{
			if(processes[y].arrival_time == current_time)
			{
				processes[y].arrival_time = current_time;
			}
			if(processes[y].burst_time > 0)
			{
				next_proc_index = y;
			}

			for(int i = 0; i < quantum; i++)
			{
				if(processes[i].burst_time <= 0)
			{
				i++;	
			}
			printf("\n\nt = %d\n", current_time);
			printf("CPU: ");
			if(current_time == 0)
			{
				printf("Loading process %d (CPU burst = %d)", processes[0].processID, processes[0].burst_time);
				processes[0].burst_time--;
				next_proc_index = i;
				queue_ARR[index] = processes[0].processID;
				queue_ARR[++index] = processes[1].processID;
			
				printf("\nReady Queue: ");
				for(int w = 0; w <= index; w++)
				{
					printf("%d-", queue_ARR[w]);
				}

				current_time++;
				printf("\n\nt = %d\n", current_time);
				printf("CPU: ");
				printf("Running process %d (remaining CPU burst = %d)", processes[0].processID, processes[0].burst_time);
				processes[0].burst_time--;

			}
			else if(i == quantum - 1)
			{
				int temp_next = next_proc_index + 1;
				while(processes[temp_next].arrival_time > current_time)
				{
					temp_next = temp_next + 1;
					if(temp_next > num_proc)
					{
						temp_next = 0;
					}
				}
				printf("Preempting process %d (remaining CPU burst = %d); loading process %d (CPU burst = %d)", processes[next_proc_index].processID, processes[next_proc_index].burst_time, processes[temp_next].processID, processes[temp_next].burst_time);
				processes[next_proc_index + 1].burst_time--;
				next_proc_index = next_proc_index + 1;
				contex_switch++;

				index++;
				queue_ARR[index] = processes[next_proc_index + 1].processID;

				for(int c = 0; c < size - 1; c++)
				{
					queue_ARR[c] = queue_ARR[c + 1];
				}
				size--;
			}
			else if(processes[next_proc_index].burst_time == 0)
			{
				next_proc_index;
				while(processes[next_proc_index].burst_time <= 0)
				{
					next_proc_index++;
					if(next_proc_index > num_proc)
					{
						next_proc_index = 0;
					}
				}
				printf("Finishing process %d; loading process %d (CPU burst = %d)", processes[next_proc_index].processID, processes[next_proc_index + 1].processID, processes[next_proc_index + 1].burst_time);
				completed_procs++;
				processes[next_proc_index].finishing_time = current_time;
				processes[next_proc_index].turnaround_time = current_time - processes[next_proc_index].arrival_time;
				processes[next_proc_index].starting_time = current_time - processes[next_proc_index].burst_time;
				next_proc_index = next_proc_index + 1;
				contex_switch++;
				processes[next_proc_index + 1].burst_time--;
				index++;
				queue_ARR[index] = processes[next_proc_index + 1].processID;

				for(int c = 0; c < size - 1; c++)
				{
					queue_ARR[c] = queue_ARR[c + 1];
				}
				size--;
			}	
			else if(processes[next_proc_index].burst_time > 0)
			{
				printf("Running process %d (remaining CPU burst = %d)", processes[next_proc_index].processID, processes[next_proc_index].burst_time);
				processes[next_proc_index].burst_time--;
				size--;
			}

			current_time++;

			printf("\nReady Queue: ");
			for(int w = 0; w < index; w++)
			{
				printf("%d-", queue_ARR[w]);
			}
			

			printf("\n%d Completed: %d\n",  num_proc, completed_procs);
		}
		}
	}


	printf("\n*********************************************************\n");
	printf("Round robin Summary (WT = wait time, TT = turnaround time):\n\n");
	printf("PID		WT		TT");
	int total_wait = 0, total_turnaround = 0;

	for(int i = 0; i < num_proc; i++)
	{
		processes[i].turnaround_time = processes[i].finishing_time - processes[i].arrival_time;
		int WT = processes[i].starting_time = processes[i].finishing_time - processes[i].burst_time;
		processes[i].turnaround_time = processes[i].finishing_time - processes[i].arrival_time;

		printf("%d 		%d		%d\n", processes[i].processID, WT - processes[i].arrival_time, processes[i].turnaround_time);
		total_wait += WT - processes[i].arrival_time;
		total_turnaround += processes[i].turnaround_time;

	}
	printf("AVG		%.2f		%.2f\n", (float)total_wait/num_proc, (float)total_turnaround/num_proc);
	printf("\nProcess sequence: ");

	for(int i = 0; i < num_proc; i++)
	{
		printf("%d-", processes[i].processID);
	}
	printf("\nContex Switches: %d\n", contex_switch);
}

int main(int argc, char* argv[]) {
	struct process * processes = (struct process *)malloc(sizeof(struct process));
	readContents("testin1.dat", processes);
	//SJF(processes, 10);
	RR(processes, 5);
	//FCFS(processes);
	//SJF(processes);
	//STCF(processes, 5);
	return 0;
}
