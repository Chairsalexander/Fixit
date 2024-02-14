///
// Group_project_one
//
//Created by alexander Chairs
//      2/5/24
//Make file help, Need to update Make file to make it run the xecutable to run the test file
//g++ -o test1 test1.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
//#include <process.h> //for fork()
//#include <io.h> //for iostream
#include <string.h>
//#include <fstream>
//#include "queue.h"
//#include <stack>
//#include <list>
//#include <windows.h>
#include <sys/wait.h>
//extern "C" {
#include <unistd.h> // For fork() and getpid()
//}
//#define _XOPEN_SOURCE 600
#ifndef __FORK_WINDOWS_H__
#define __FORK_WINDOWS_H__
#endif
//using namespace std;


int main(int argc, const char * argv[]) {

    pid_t parent_pid = getpid();

    printf("parent pid is %d\n", parent_pid);
	pid_t child_pid;
    /* = fork();
	if (child_pid< 0) {// Error occurred
		printf("Fork ID=%d failed/n", child_pid);
		fprintf(stderr, "Fork failed");
		return 1;
	} else if (child_pid==0) {
		child_pid = getpid();
		//execlp("/bin/ls", "ls", NULL);
	} 
	printf("Started child with pid %d\n", child_pid); 
	wait(NULL);
	printf("Child (PID %d) finished\n", child_pid);*/
	//Does argv give the address or actual value of 2nd input?
    //Make an array and stoire the PID vales in it
	int counter = atoi(argv[1]);
	char *file = argv[2];
	int myArray[counter];
	int status;
    child_pid = 0;
    //Trying ot figureout the loop based off the number input by the user in terminal to identify how many children to make
    //wait() - returns PID when finished
    //gets each program in the folder and forks
	const char *files[5] = {"test1.c", "test2.c", "test3.c", "test4.c", "test5.c"};
	if (file==NULL) {
		//const char *arg = argv[2];
		for(int i = 0; i < counter-1; i++)            
		{
			//int random = rand() % (counter); //https://www.geeksforgeeks.org/c-rand-function/
			//pid_t child_pid = fork();
			myArray[i+1] = fork();
			wait(&status);
			child_pid = myArray[i+1];
			//int pid = execlp(arg[random], "ls", NULL);
			if(myArray[i+1] == 0)
			{
				myArray[i+1] = getpid();
				//child_pid = myArray[i+1];
			//STart Child precces
			//RUN THE Excecutable which will run a specific test file
			//Either make a random number generator to chppse which executable to run to make it run 
			//Like a round robin, 1, 2, 3, 4, 5, 1, 2, ....
				//execlp(files[random], "ls", NULL); //From notes 
				
			} else if (myArray[i+1] < 0) {
				while (myArray[i+1] < 0) {
					printf("fork failed, again\n");
					myArray[i+1] = fork();
					//printf("started child %d with pid %d\n", i+1, myArray[i+1]);
					//pid = execlp(files[random], NULL);
				}
			}
			//printf("started child %d with pid %d\n", i+1, myArray[i+1]);
			//wait(NULL);
			//printf("Child (PID %d) finished\n", myArray[i+1]);
		}
	}	else	{
		for(int i = 0; i < counter; i++)            
		{
			//int random = rand() % (counter); //https://www.geeksforgeeks.org/c-rand-function/
			//pid_t child_pid = fork();
			myArray[i+1] = execlp(file, NULL);
			//int pid = execlp(arg[random], "ls", NULL);
			if(myArray[i+1] == 0)
			{
				myArray[i+1] = getpid();
				//child_pid = myArray[i+1];
			//STart Child precces
			//RUN THE Excecutable which will run a specific test file
			//Either make a random number generator to chppse which executable to run to make it run 
			//Like a round robin, 1, 2, 3, 4, 5, 1, 2, ....
				//execlp(files[random], "ls", NULL); //From notes 
				
			} else if (myArray[i+1] < 0) {
				while (myArray[i+1] < 0) {
					printf("fork failed, again\n");
					myArray[i+1] = execlp(file, NULL);
				}
			}
			printf("Running program %s in process %d\n", file, myArray[i+1]);
			wait(NULL);
			printf("Child (PID %d) finished\n", myArray[i+1]);
		}
	}	
	if (file==NULL) {
		printf("Started child with pid %d\n", child_pid); 
		wait(NULL);
		printf("Child (PID %d) finished\n", child_pid);
	}
    //For loop to see when the PIDs have finished using wait()
    //Order in whihc they finish has nothig to do with how they started
    //Loop that assigns the CHild number to the order of which the PIDs have finished
    /*for(int i = 1; i <= counter; i++)
    {
        int num = wait(NULL); //From notes and OS_lec3_IPC.pdf		
        int* location = myArray[i];

        if(location == myArray[i])
        {
            printf("Child %d (PID %n) Finished\n",num,location);
        }

    }*/


    /*
    if(child_pid == 0)
    {
        cout << "started child with pid " << getpid() << endl;
        
        //Child proccess logic

        cout << "Child (PID " << getpid() << ") Finished" << endl;
    }
    */
}
