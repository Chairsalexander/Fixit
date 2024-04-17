#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"
#include <semaphore.h>
#include <time.h>

sem_t s1, s2;

void *child_1(void *arg) {
    printf("child 1: before\n");

    // what goes here?
    sleep(1);
    sem_post(&s2);
    
    sem_wait(&s1);

    printf("child 1: after\n");
    return NULL;
}

void *child_2(void *arg) {
    printf("child 2: before\n");

    // what goes here?
    sem_post(&s1);
    sleep(1);
    sem_wait(&s2);

    printf("child 2: after\n");
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("parent: begin\n");

    // init semaphores here
    sem_init(&s1, 1, 0);
    sleep(1);
    sem_init(&s2, 1, 0);

    Pthread_create(&p1, NULL, child_1, NULL);
    Pthread_create(&p2, NULL, child_2, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("parent: end\n");
    return 0;
}
