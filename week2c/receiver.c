/*
    COMPILE: 
        gcc -o sender sender.c -lrt -lpthread 
        gcc -o receiver receiver.c -lrt -lpthread
    RUN: 
        ./sender
        ./receiver
*/

/*
    FINISHED
*/

/*
    Schrijf een C-programma dat 2 pthreads aanmaakt en dmv shared
    memory 50 integers overstuurt van thread 1 naar thread 2.
*/

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>

#define NAME "/sharedMemory"
#define NUM 50
#define SIZE (NUM * sizeof(int))

int fd;

void *receiving()
{
    int *data =
        (int *)mmap(0, SIZE, PROT_READ, MAP_SHARED, fd, 0);
    printf("receiver mapped address: %p\n", data);
    printf("RECEIVING \n");

    for (int i = 0; i < NUM; ++i)
    {
        printf("%d\n", data[i]);
    }
    
    munmap(data, SIZE);
    pthread_exit(NULL);
}

int main()
{
    fd = shm_open(NAME, O_RDONLY, 0666);
    if (fd < 0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    pthread_attr_t tattr;
    pthread_t thread2;

    pthread_attr_init(&tattr);
    pthread_create(&thread2, &tattr, receiving, NULL);
    pthread_join(thread2, NULL);

    close(fd);

    shm_unlink(NAME);

    pthread_exit(NULL);
}