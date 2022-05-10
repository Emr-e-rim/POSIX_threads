/*
    COMPILE: gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED, BUT ONLY WORKS AS ROOT (https://websiteforstudents.com/how-to-login-as-root-on-ubuntu-with-windows-wsl/)
*/

/*
    Gelijk aan opgave 1B, maar los dit probleem nu op door de juiste prioriteiten aan de taken te geven en niet dmv pthread_join().
*/

/*
    NOTITIE: Gebruikt nog steeds pthread_join() maar de threads worden uitgevoerd op basis van hun prioriteit ipv op basis van wanneer
    pthread_join() ze aanroept.
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <sched.h>

void* taskOne(void *arg)
{
    int i,j,m,n;
    while(1)
    {
        for(i=0; i<5; i++)
        {
            for(j=1; j<=8; j++)
            {
                printf("taak 1 %i\n",j);
                for (m=0; m<=1000; m++)
                    for(n=0; n<=10000; n++);
            }
        }
    }
}

void* taskTwo(void *arg)
{
    int i,j,m,n;
    while(1)
    {
        for(i=0; i<5; i++)
        {
            for(j=1; j<=8; j++)
            {
                printf("taak 2 %i\n",j);
                for (m=0; m<=1000; m++)
                    for(n=0; n<=10000; n++);
            }
        }
    }
}

void* taskThree(void *arg)
{
    int i,j,m,n;
    for(i=0; i<5; i++)
    {
        for(j=1; j<=8; j++)
        {
            printf("taak 3 %i\n",j);
            for (m=0; m<=1000; m++)
                for(n=0; n<=10000; n++);
        }
    }
}

void* taskFour(void *arg)
{
    int i,j,m,n;
    for(i=0; i<5; i++)
    {
        for(j=1; j<=8; j++)
        {
            printf("taak 4 %i\n",j);
            for (m=0; m<=1000; m++)
                for(n=0; n<=10000; n++);
        }
    }
}

int main()
{
    /* Initialized with default attributes */
    struct sched_param param;
    pthread_attr_t tattr1, tattr2;
    pthread_t tid[4], main_id;

    // Run de taken op core nr 0
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    sched_setaffinity(0, sizeof(mask), &mask);

    int policy=SCHED_RR;
    int priority_min, priority_max;

    /* Min and max priorities */
    priority_max = sched_get_priority_max(policy);
    priority_min = sched_get_priority_min(policy);
    
    main_id = pthread_self();
    param.sched_priority=priority_max;
    pthread_setschedparam(main_id, policy, &param);
    
    /* Thread 1 */
    pthread_attr_init(&tattr1);
    pthread_attr_setschedpolicy(&tattr1,policy);
    pthread_attr_setschedparam(&tattr1,&param);
    param.sched_priority = priority_min;
    pthread_create(&tid[0], &tattr1, taskOne, NULL);
    pthread_setschedparam(tid[0], policy, &param);
        
    /* Thread 2 */
    pthread_attr_init(&tattr1);
    pthread_attr_setschedpolicy(&tattr1,policy);
    pthread_attr_setschedparam(&tattr1,&param);
    param.sched_priority = priority_min;
    pthread_create(&tid[1], &tattr1, taskTwo, NULL);
    pthread_setschedparam(tid[1], policy, &param);

    /* Thread 3 */
    pthread_attr_init(&tattr2);
    pthread_attr_setschedpolicy(&tattr2,policy);
    pthread_attr_setschedparam(&tattr2,&param);
    param.sched_priority = priority_max;
    pthread_create(&tid[2], &tattr2, taskThree, NULL);
    pthread_setschedparam(tid[2], policy, &param);

    /* Thread 4 */
    pthread_attr_init(&tattr2);
    pthread_attr_setschedpolicy(&tattr2,policy);
    pthread_attr_setschedparam(&tattr2,&param);
    param.sched_priority = priority_max;
    pthread_create(&tid[3], &tattr2, taskFour, NULL);
    pthread_setschedparam(tid[3], policy, &param);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    
}
