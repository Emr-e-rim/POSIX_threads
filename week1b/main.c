/*
    COMPILE: gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED
*/

/*
Onderstaand is gegeven de code van 4 pthreads (4 taken).
Thread 1 en thread 2 bevatten een oneindige while-loop en
thread 3 en 4 zijn aflopend (geen oneindige while-loop).
Schrijf nu een C-programma dat eerst thread 3 en thread 4 in
round robin uitvoert en na het beeindigen van thread 3 en
thread 4 de uitvoer vervolgt met round robin tussen thread 1
en thread 2.
*/

#include <stdio.h>
#include <pthread.h>
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

                /* De for-lussen dienen om een vertraging te
                realiseren, zodater een aantal keer een context
                switch naar taak 2 optreedt */
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
                /* De for-lussen dienen om een vertraging te
                realiseren, zodat er een aantal keer een context
                switch naar taak 4 optreedt */
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
            /* De for-lussen dienen om een vertraging te
            realiseren, zodat er een aantal keer een context
            switch naar taak 4 optreedt */
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
            /* De for-lussen dienen om een vertraging te
            realiseren, zodat er een aantal keer een context
            switch naar taak 3 optreedt */
        }
    }
}

int main()
{
    pthread_attr_t tattr;
    pthread_t tid[4];
    int ret, j;

    /* initialized with default attributes */
    pthread_attr_init (&tattr);

    ret = pthread_attr_setschedpolicy(&tattr, SCHED_RR);

    ret = pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_JOINABLE);

    ret = pthread_create (&tid[0], &tattr, taskThree, NULL);
    ret = pthread_create (&tid[1], &tattr, taskFour, NULL);

    for(j=0; j < 2; j++)
    {
        pthread_join(tid[j], NULL);
    }

    //Show transition to thread 1 and 2
    printf("\n");
    printf("\n");
    printf("\n");

    ret = pthread_create (&tid[2], &tattr, taskOne, NULL);
    ret = pthread_create (&tid[3], &tattr, taskTwo, NULL);

    pthread_exit(NULL);
}
