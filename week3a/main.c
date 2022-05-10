/*
    COMPILE gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED
*/

/*
Schrijf een C-programma dat een binaire semafoor en twee threads aanmaakt (round robin)
en met in beide threads een kritieke sectie behorende bij de binaire semafoor. 
In kritieke sectie 1 (thread 1) moet 5 keer – telkens om de 1 seconde – de tekst “sectie 1” 
worden afgedrukt. In kritieke sectie 2 (thread 2) moet 5 keer – telkens om de 1 seconde –
de tekst “sectie 2” worden afgedrukt.
*/

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *section1()
{
    sem_wait(&sem);
    for (int i = 0; i < 5; i++)
    {
        printf("Sectie 1\n\n");
        sleep(1);
    }
    sem_post(&sem);
}

void *section2()
{
    sem_wait(&sem);
    for (int i = 0; i < 5; i++)
    {
        printf("Sectie 2\n\n");
        sleep(1);
    }
    sem_post(&sem);
}

int main()
{
    pthread_t thread1, thread2;
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);

    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    sem_init(&sem, 0, 1);
    pthread_create(&thread1, &tattr, section1, NULL);
    pthread_create(&thread2, &tattr, section2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    sem_destroy(&sem);
    return 0;
}
