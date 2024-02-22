#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];

enum { THINKING, HUNGRY, EATING } state[NUM_PHILOSOPHERS];

void *philosopher(void *arg);
void grab_forks(int philosopher_number);
void put_forks(int philosopher_number);
void test(int philosopher_number);

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];

    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&condition[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        int *arg = (int *)malloc(sizeof(int));
        *arg = i;
        pthread_create(&philosophers[i], NULL, philosopher, arg);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}

void *philosopher(void *arg) {
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

void grab_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);
    state[philosopher_number] = HUNGRY;
    test(philosopher_number);
    while (state[philosopher_number] != EATING) {
        pthread_cond_wait(&condition[philosopher_number], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void put_forks(int philosopher_number) {
    pthread_mutex_lock(&mutex);
    state[philosopher_number] = THINKING;
    printf("Philosopher %d has finished eating.\n", philosopher_number);
    test((philosopher_number + 4) % NUM_PHILOSOPHERS);
    test((philosopher_number + 1) % NUM_PHILOSOPHERS);
    pthread_mutex_unlock(&mutex);
}

void test(int philosopher_number) {
    if (state[philosopher_number] == HUNGRY &&
        state[(philosopher_number + 4) % NUM_PHILOSOPHERS] != EATING &&
        state[(philosopher_number + 1) % NUM_PHILOSOPHERS] != EATING) {
        state[philosopher_number] = EATING;
        pthread_cond_signal(&condition[philosopher_number]);
    }
}
