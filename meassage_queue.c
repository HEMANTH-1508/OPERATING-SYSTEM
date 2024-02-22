#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define MAX_TEXT 512

// Define a structure for message queue
struct msg_buffer 
{
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() 
{
    int msgid;
    struct msg_buffer message;
    key_t key;

    // Generate a unique key for the message queue
    if ((key = ftok("msg_queue_key", 'B')) == -1) 
    {
        perror("ftok");
        exit(1);
    }

    // Create a message queue
    if ((msgid = msgget(key, 0644 | IPC_CREAT)) == -1) 
    {
        perror("msgget");
        exit(1);
    }

    printf("Message Queue ID: %d\n", msgid);

    // Send a message
    message.msg_type = 1; // Message type (can be any positive number)
    strcpy(message.msg_text, "Hello, this is a message from process 1!");

    if (msgsnd(msgid, (void *)&message, MAX_TEXT, 0) == -1) 
    {
        perror("msgsnd");
        exit(1);
    }

    printf("Message sent: %s\n", message.msg_text);

    // Receive a message
    if (msgrcv(msgid, (void *)&message, MAX_TEXT, 0, 0) == -1) 
    {
      
        perror("msgrcv");
        exit(1);
    }

    printf("Message received: %s\n", message.msg_text);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) 
    {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
