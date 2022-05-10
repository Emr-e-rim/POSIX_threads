/*
    COMPILE gcc -g -Wall -o main main.c -lrt -pthread
    RUN: ./main
*/

/*
    NOT FINISHED BECAUSE POSIX MESSAGE QUEUES ARE NOT ARE IMPLEMENTED IN WSL
*/

/*
Schrijf een C-programma dat 2 pthreads aanmaakt en dmv een
(posix)message queue 50 integers overstuurt van thread 1 naar
thread 2.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <mqueue.h>

void *sendThread(void *args)
{
    mqd_t mqd;

    mqd = mq_open("/OpenCSF_MQ", O_CREAT | O_EXCL | O_WRONLY, 0600, NULL);
    if (mqd == -1)
    {
        printf("failed to send: HELLO\n");
        perror("mq_open");
        exit(1);
    }
    printf("send: HELLO\n");
    mq_send(mqd, "HELLO", 6, 10);
    mq_close(mqd);

    pthread_exit(NULL);
    return NULL;
}

void *receiveThread(void *args)
{
    mqd_t mqd;

    mqd = mq_open("/OpenCSF_MQ", O_RDONLY);
    //struct mq_attr attr;
    //char *buffer = calloc(attr.mq_msgsize, 1);
    printf("receive: HELLO\n");
    unsigned int priority = 0;
    char in_buffer[266];
    if (mq_receive(mqd, in_buffer, 266, NULL) == -1)
        printf("Failed to receive message\n");
    else
        printf("Received [priority %u]: '%s'\n", priority, in_buffer);

    //free(in_buffer);
    //in_buffer = NULL;
    mq_close(mqd);

    pthread_exit(NULL);
    return NULL;
}

int main()
{
    pthread_attr_t tattr;
    pthread_t thread1, thread2;

    pthread_attr_init(&tattr);

    pthread_create(&thread1, &tattr, sendThread, NULL);
    pthread_create(&thread2, &tattr, receiveThread, NULL);

    pthread_exit(NULL);

    return 0;
}