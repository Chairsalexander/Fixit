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

int searchValue(int arr[], int size, int value) {
	for(int i = 0; i < size; i++) {
		if(arr[i] == value) {
			return i;
		}
	}
	return -1;
}

//Parent should be tracking array of children


int main(int argc, const char * argv[]) {

    pid_t parent_pid = getpid();
    printf("parent pid is %d\n", parent_pid);
    
    //Make an array and stoire the PID vales in it
    int num_child = atoi(argv[1]);
    pid_t myArray[num_child]; 
	int finishedArray[num_child];
	printf("count = %d\n", num_child);
	pid_t child_pid;
	
    int status;
    //Trying ot figureout the loop based off the number input by the user in terminal to identify how many children to make
    //wait() - returns PID when finished - gets each program in the folder and forks
    const char *files[5] = {"./test1", "./test2", "./test3", "./test4", "./test5"};
	const char *files1[5] = {"test1", "test2", "test3", "test4", "test5"};
    for(int i = 0; i < num_child; i++)            
    {
		int random = rand() % (5); //https://www.geeksforgeeks.org/c-rand-function/
        
		//Need conditional state around fork to make sure onyl parent funtion calls fork
		if(parent_pid == getpid())
		{
			child_pid = fork();
		}

		if(child_pid < 0)
		{
			exit(EXIT_FAILURE);
		}

        else if(child_pid == 0)
        {
			//Child Process
			child_pid = getpid();
            printf("started child %d with pid %d, rv %d\n", i+1, child_pid, random);
        //RUN THE Excecutable which will run a specific test file
        //Either make a random number generator to chppse which executable to run to make it run 
        //Like a round robin, 1, 2, 3, 4, 5, 1, 2, ....
            execlp(files[random], files1[random], NULL); //From notes 
        }
		else
		{
			myArray[i] = child_pid;
		} 

    }
	
    //For loop to see when the PIDs have finished using wait()
    //Order in whihc they finish has nothig to do with how they started
    //Loop that assigns the CHild number to the order of which the PIDs have finished
    //each iteration collects the order of PIDs finishing. 1 iteration for one PID to finish
	for(int i = 0; i < num_child; i++)
    {
        //int searchValue(int arr[], int size, int value)
		
		int status = 0;
		pid_t num = wait(&status); //From notes and OS_lec3_IPC.pdf		
        
		int value = searchValue(myArray, num_child, num);
		
		if(num > 0)
        {
            printf("Child %d (PID %d) Finished\n", value + 1, num);
        }

    }
	
    
    
}