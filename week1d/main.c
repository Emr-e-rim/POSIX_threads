/*
    COMPILE gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED
*/

/*
Schrijf een C-programma dat twee periodieke pthreads
aanmaakt. Thread1 heeft een periodetijd van 0,5 sek en thread
2 heeft een periodetijd van 1,3 sek. Iedere thread drukt per
periode de threadnaam en periodenummer af.
*/

#include <stdio.h>
#include <pthread.h>
#include <time.h>

void *printThread1(void * args)
{
    int i,m,n;
    struct timespec deadline;
    long int period=500000000L;
    clock_gettime(CLOCK_MONOTONIC, &deadline);

    while(1)
    {
        printf("thread 1\n");
        printf("\n");
        deadline.tv_nsec=deadline.tv_nsec+period;
        if (deadline.tv_nsec>=period)
        {
            deadline.tv_nsec-=period;
            ++deadline.tv_sec;
        }
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
    }
    pthread_exit(NULL);

    return NULL;
}

void *printThread2(void * args)
{
    int i,m,n;

    struct timespec deadline;
    long int period=1300000000L;
    clock_gettime(CLOCK_MONOTONIC, &deadline);

    while(1)
    {
        printf("thread 2\n");
        printf("\n");
        deadline.tv_nsec=deadline.tv_nsec+period;
        if (deadline.tv_nsec>=period)
        {
            deadline.tv_nsec-=period;
            ++deadline.tv_sec;
        }
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deadline, NULL);
    }
    pthread_exit(NULL);

    return NULL;
}

int main()
{
    pthread_attr_t tattr;
    pthread_t thread1, thread2;

    pthread_attr_init (&tattr);

    pthread_create(&thread1, &tattr, printThread1, NULL);
    pthread_create(&thread2, &tattr, printThread2, NULL);

    pthread_exit(NULL);
    return 0;
}
