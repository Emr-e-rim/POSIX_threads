/*
    COMPILE: gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED
*/

/*
Onderstaand is gegeven de code van 4 pthreads (4 taken).
Schrijf een c-programma dat de 4 taken met de posix-api in
round robin schedult.
*/

#include <stdio.h>
#include <pthread.h>
#include <sched.h>

void *taskOne(void *arg)
{
    int i, j, m, n;
    while (1)
    {
        for (i = 0; i < 5; i++)
        {
            for (j = 1; j < 8; j++)
            {
                printf("taak 1 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    ;
                for (n = 0; n <= 10000; n++)
                    ;
                /* De for-lussen dienen om een vertraging te
                realiseren, zodater een aantal keer een context
                switch naar taak 2 optreedt */
            }
        }
    }
}

void *taskTwo(void *arg)
{
    int i, j, m, n;
    while (1)
    {
        for (i = 0; i < 5; i++)
        {
            for (j = 1; j <= 8; j++)
            {
                printf("taak 2 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    ;
                for (n = 0; n <= 10000; n++)
                    ;
                /* De for-lussen dienen om een vertraging te
                realiseren, zodat er een aantal keer een context
                switch naar taak 4 optreedt */
            }
        }
    }
}

void *taskThree(void *arg)
{
    int i, j, m, n;
    while (1)
    {
        for (i = 0; i < 5; i++)
        {
            for (j = 1; j <= 8; j++)
            {
                printf("taak 3 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    ;
                for (n = 0; n <= 10000; n++)
                    ;
                /* De for-lussen dienen om een vertraging te
                realiseren, zodat er een aantal keer een context
                switch naar taak 4 optreedt */
            }
        }
    }
}

void *taskFour(void *arg)
{
    int i, j, m, n;
    while (1)
    {
        for (i = 0; i < 5; i++)
        {
            for (j = 1; j <= 8; j++)
            {
                printf("taak 4 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    ;
                for (n = 0; n <= 10000; n++)
                    ;
                /* De for-lussen dienen om een vertraging te
                realiseren, zodat er een aantal keer een context
                switch naar taak 3 optreedt */
            }
        }
    }
}

int main()
{
    pthread_t tid[4];
    pthread_attr_t tattr;
    pthread_attr_init(&tattr); //tattr init met defaultwaarden

    pthread_attr_setschedpolicy(&tattr, SCHED_RR); //sched policy aanpassen

    pthread_create(&tid[0], &tattr, taskOne, NULL);
    pthread_create(&tid[1], &tattr, taskTwo, NULL);
    pthread_create(&tid[2], &tattr, taskThree, NULL);
    pthread_create(&tid[3], &tattr, taskFour, NULL);

    pthread_exit(NULL);

    return 0;
}
