/*
    COMPILE gcc main.c -o main -pthread
    RUN: ./main
*/

/*
    FINISHED
*/

/*
    Schrijf een C-programma dat 2 pthreads aanmaakt en dmv een
    posix pipe 50 integers overstuurt van thread 1 naar thread 2.
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int fd[2];

void *reading()
{
    int c, result;
    FILE *stream;

    stream = fdopen(fd[0], "r");
    while ((c = fgetc(stream)) != EOF)
        putchar(c);

    fclose(stream);
}

/* Write some random text to the pipe. */

void *writing()
{
    int i, result;
    FILE *stream;
    
    stream = fdopen(fd[1], "w");
    for (i = 0; i < 50; i++)
    {
        fprintf(stream, "%d\n", i);
    }
  
    fclose(stream);
}

int main(void)
{
    pthread_attr_t tattr;
    pthread_t thread1, thread2;

    pthread_attr_init(&tattr);

    pipe(fd);

    /* Create the pipe. */
    
  if (pipe(fd))
    {
      fprintf (stderr, "Pipe failed.\n");
    }
    
    pthread_create(&thread1, &tattr, reading, NULL);
    pthread_create(&thread2, &tattr, writing, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
}