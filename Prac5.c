#include <stdio.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

char avbuff[10];
sem_t mutex, empty, full;

void *produce(void *arg)
{
    int i;
    printf("\nInside Producer");
    for (i = 0; i < 10; i++)
    {
        sem_wait(&empty);
        sem_wait(&mutex);

        avbuff[i] = i;
        printf("\nItem produced is %d", avbuff[i]);

        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg)
{
    int j;
    printf("\nInside Consumer");
    for (j = 0; j < 10; j++)
    {
        sem_wait(&full);
        sem_wait(&mutex);

        j = avbuff[j];
        printf("\nItem consumed is %d", j);

        sem_post(&mutex);
        sem_post(&empty);
        sleep(5);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t tid1, tid2;
    void *status;

    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&tid1, NULL, produce, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, &status);
    printf("\nThe exited status %s\n", (char *)status);

    pthread_join(tid2, &status);
    printf("\nThe exited status %s\n", (char *)status);

    return 1;
}
