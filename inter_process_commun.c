#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main() 
{
    int shmid;
    key_t key;
    char *shm, *s;

    // Generate a unique key for the shared memory segment
    key = ftok(".", 's');
    if (key == -1) 
    {
        perror("ftok");
        exit(1);
    }

    // Create the shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the address space of the process
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) 
    {
        perror("shmat");
        exit(1);
    }

    // Write a message to the shared memory
    sprintf(shm, "Hello, shared memory!");

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) 
    {
        perror("fork");
        exit(1);
    } 
    else if (pid == 0) 
    {
        // Child process reads from shared memory and prints the message
        printf("Child Process: Message read from shared memory: %s\n", shm);

        // Detach the shared memory segment from the child process
        if (shmdt(shm) == -1) 
        {
            perror("shmdt");
            exit(1);
        }
    } 
    else 
    {
        // Parent process waits for the child process to finish
        wait(NULL);

        // Detach the shared memory segment from the parent process
        if (shmdt(shm) == -1) 
        {
            perror("shmdt");
            exit(1);
        }

        // Delete the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) 
        {
            perror("shmctl");
            exit(1);
        }
    }

    return 0;
}
