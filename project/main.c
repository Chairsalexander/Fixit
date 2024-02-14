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

	//Does argv give the address or actual value of 2nd input?
    //Make an array and stoire the PID vales in it

	int counter = atoi(argv[1]);
	int finished_pids[counter];	
	int status;

    //Trying ot figureout the loop based off the number input by the user in terminal to identify how many children to make
    //wait() - returns PID when finished
    //gets each program in the folder and forks
	const char *files[5] = {"test1.c", "test2.c", "test3.c", "test4.c", "test5.c"};
    for(int i = 0; i < counter; i++)            
    {
		//int random = rand() % (counter+1); //https://www.geeksforgeeks.org/c-rand-function/
        pid_t child_pid = fork();

		if(child_pid < 0)
		{
			//error
			perror("fork");
		}
		else if(child_pid == 0)
        {
			//finished_pids[i] = getpid();
			printf("started child %d with pid %d\n", i+1, get_pid());
			//STart Child precces
        //RUN THE Excecutable which will run a specific test file
        //Either make a random number generator to chppse which executable to run to make it run 
        //Like a round robin, 1, 2, 3, 4, 5, 1, 2, ....

            //execlp(files[random], "ls", NULL); //From notes 
        } 

        /*else if (child_pid < 0) {
			while (child_pid < 0) {
				printf("fork failed, again\n");
				child_pid = fork();
				execlp(files[random], "ls", NULL);
			}
		}
        */

    }

	for(int i = 0; i < counter; i++)
	{
		int status;
		pid_t finished_pid; 
		finished_pid = wait(&status);

		if(finished_pid > 0)
		{
			//Store pid of finished child into an array
			finished_pids[i] = finished_pid;
		}

	}

    //For loop to see when the PIDs have finished using wait()
    //Order in whihc they finish has nothig to do with how they started
    //Loop that assigns the CHild number to the order of which the PIDs have finished
    for(int i = 0; i <= counter; i++)
    {
        int num = wait(NULL); //From notes and OS_lec3_IPC.pdf		
        int* location = finished_pids;
        if(location <= finished_pids + counter)
        {
            printf("Child %d (PID %n) Finished\n", i + 1, num);
        }
    }
    

    /*
    if(child_pid == 0)
    {
        cout << "started child with pid " << getpid() << endl;
        
        //Child proccess logic
        cout << "Child (PID " << getpid() << ") Finished" << endl;
    }
    */
}