/*
    COMPILE gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED
*/

/*
Schrijf een C-programma dat een mutex en twee threads aanmaakt (round robin)
en met in beide threads een kritieke sectie behorende bij de mutex. 
In kritieke sectie 1 (thread 1) moet 5 keer – telkens om de 1 seconde – de tekst “sectie 1” 
worden afgedrukt. In kritieke sectie 2 (thread 2) moet 5 keer – telkens om de 1 seconde –
de tekst “sectie 2” worden afgedrukt.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

void *section1()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5; i++)
    {
        printf("Sectie 1\n\n");
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *section2()
{
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < 5; i++)
    {
        printf("Sectie 2\n\n");
        sleep(1);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    pthread_mutex_init(&mutex, NULL);

    pthread_attr_t tattr;

    pthread_attr_init(&tattr);
    pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    pthread_create(&thread1, &tattr, section1, &mutex);
    pthread_create(&thread2, &tattr, section2, &mutex);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_mutex_destroy(&mutex);

    return 0;
}