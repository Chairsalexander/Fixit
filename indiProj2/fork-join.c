#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "common_threads.h"
#include <semaphore.h>
#include <time.h>

sem_t s;

void *child(void *arg) {
    printf("child\n");
    sem_post(&s);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    // init semaphore here
    sem_init(&s, 0, 0);
    printf("parent: begin\n");
    Pthread_create(&p, NULL, child, NULL);
    // use semaphore here
    sem_wait(&s);
    Pthread_join(p, NULL);
    printf("parent: end\n");
    return 0;
}
