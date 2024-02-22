#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Function to be executed by each thread
void *thread_function(void *arg) 
{
    int thread_id = *((int *)arg);
    printf("Thread %d is running...\n", thread_id);
    printf("Thread %d is exiting...\n", thread_id);
    pthread_exit(NULL);
}

int main() 
{
    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];
    int rc, t;

    // Create multiple threads
    for (t = 0; t < NUM_THREADS; t++) 
    {
        printf("Creating thread %d\n", t);
        thread_args[t] = t;
        rc = pthread_create(&threads[t], NULL, thread_function, (void *)&thread_args[t]);
        if (rc) 
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    // Wait for all threads to finish
    for (t = 0; t < NUM_THREADS; t++) 
    {
        pthread_join(threads[t], NULL);
    }

    printf("All threads have completed their execution.\n");

    pthread_exit(NULL);
}
