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

void *sending()
{
    int *data =
        (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    printf("sender mapped address: %p\n", data);
    printf("SENDING \n");

    for (int i = 0; i < NUM; ++i)
    {
        data[i] = i;
    }

    munmap(data, SIZE);
    pthread_exit(NULL);
}

int main()
{
    fd = shm_open(NAME, O_CREAT | O_EXCL | O_RDWR, 0600);
    if (fd < 0)
    {
        perror("shm_open()");
        return EXIT_FAILURE;
    }

    ftruncate(fd, SIZE);

    pthread_attr_t tattr;
    pthread_t thread1;

    pthread_attr_init(&tattr);
    pthread_create(&thread1, &tattr, sending, NULL);
    pthread_join(thread1, NULL);

    close(fd);

    pthread_exit(NULL);
}