#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Define states for philosophers
#define THINKING 0
#define HUNGRY 1
#define EATING 2

// Mutex to control access to shared resources
pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];

// Array to store the states of each philosopher
int state[NUM_PHILOSOPHERS];

// Function prototypes
void *philosopher(void *arg);
void grab_forks(int philosopher_number);
void put_forks(int philosopher_number);
void test(int philosopher_number);

int main() 
{
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int i;

    // Initialize mutex and conditions
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_cond_init(&condition[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        int *philosopher_number = (int *)malloc(sizeof(int));
        *philosopher_number = i;
        pthread_create(&philosophers[i], NULL, philosopher, philosopher_number);
    }

    // Join philosopher threads
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex and conditions
    pthread_mutex_destroy(&mutex);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) 
    {
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}

void *philosopher(void *arg) 
{
    int philosopher_number = *((int *)arg);
    free(arg);

    while (1) {
        printf("Philosopher %d is thinking.\n", philosopher_number);

        grab_forks(philosopher_number);

        printf("Philosopher %d is eating.\n", philosopher_number);

        sleep(2); // Simulate eating time

        put_forks(philosopher_number);
    }

    pthread_exit(NULL);
}

void grab_forks(int philosopher_number) 
{
    pthread_mutex_lock(&mutex);
    state[philosopher_number] = HUNGRY;
    test(philosopher_number);
    while (state[philosopher_number] != EATING) {
        pthread_cond_wait(&condition[philosopher_number], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void put_forks(int philosopher_number) 
{
    pthread_mutex_lock(&mutex);
    state[philosopher_number] = THINKING;
    printf("Philosopher %d has finished eating.\n", philosopher_number);
    test((philosopher_number + 4) % NUM_PHILOSOPHERS);
    test((philosopher_number + 1) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&mutex);
}

void test(int philosopher_number) 
{
    if (state[philosopher_number] == HUNGRY &&
        state[(philosopher_number + 4) % NUM_PHILOSOPHERS] != EATING &&
        state[(philosopher_number + 1) % NUM_PHILOSOPHERS] != EATING) 
    {
        state[philosopher_number] = EATING;
        pthread_cond_signal(&condition[philosopher_number]);
    }
}
