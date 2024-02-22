#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t room; 
sem_t chopstick[NUM_PHILOSOPHERS];

void *philosopher(void *); 
void eat(int); 

int main() { 
    pthread_t tid[NUM_PHILOSOPHERS]; 
    int philosophers[NUM_PHILOSOPHERS] = {0, 1, 2, 3, 4}; // IDs for philosophers

    sem_init(&room, 0, 4); // There are 4 seats available in the dining room

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
        sem_init(&chopstick[i], 0, 1); // Initialize each chopstick

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
        pthread_create(&tid[i], NULL, philosopher, (void *)&philosophers[i]); // Create philosopher threads

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) 
        pthread_join(tid[i], NULL); // Wait for all philosopher threads to finish

    return 0; 
} 

void *philosopher(void *num) { 
    int phil = *(int *)num; 

    while (1) {
        sem_wait(&room); // Try to enter the dining room
        printf("\nPhilosopher %d has entered the dining room", phil);

        sem_wait(&chopstick[phil]); // Pick up left chopstick
        sem_wait(&chopstick[(phil + 1) % NUM_PHILOSOPHERS]); // Pick up right chopstick

        eat(phil); // Philosopher is eating

        sem_post(&chopstick[(phil + 1) % NUM_PHILOSOPHERS]); // Release right chopstick
        sem_post(&chopstick[phil]); // Release left chopstick
        sem_post(&room); // Leave the dining room
    }
} 

void eat(int phil) { 
    printf("\nPhilosopher %d is eating", phil); 
    sleep(2); // Simulate eating time
}
