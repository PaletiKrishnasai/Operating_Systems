#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define READ_COUNT 5
#define WRITE_COUNT 7

sem_t writer;
pthread_mutex_t mutex;
int count = 1, reader = 0;

void *writer_f(void *wno)
{
    sem_wait(&writer);
    count = count * 2;
    printf("[W]Writer %d changed the content to %d\n\033[0m", (*((int *)wno)), count);
    sem_post(&writer);
}

void *reader_f(void *rno)
{
    pthread_mutex_lock(&mutex);
    reader += 1;
    if (reader == 1)
    {
        sem_wait(&writer); // Block the writer if its the first reader
    }

    pthread_mutex_unlock(&mutex);
    printf("[R]Reader %d Read the content as %d\n\033[0m", *((int *)rno), count);

    pthread_mutex_lock(&mutex);
    reader -= 1;
    if (reader == 0)
    {
        sem_post(&writer); // Wake up the writer if its the last reader
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{
    printf("\n");
    pthread_t read[READ_COUNT], write[WRITE_COUNT];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&writer, 0, 1);

    int readers[READ_COUNT];
    for (int i = 0; i < READ_COUNT; i++)
        readers[i] = i + 1;

    int writers[WRITE_COUNT];
    for (int i = 0; i < WRITE_COUNT; i++)
        writers[i] = i + 1;

    for (int i = 0; i < WRITE_COUNT; i++)
        pthread_create(&write[i], NULL, (void *)writer_f, (void *)&writers[i]);

    for (int i = 0; i < READ_COUNT; i++)
        pthread_create(&read[i], NULL, (void *)reader_f, (void *)&readers[i]);

    for (int i = 0; i < READ_COUNT; i++)
        pthread_join(read[i], NULL);

    for (int i = 0; i < WRITE_COUNT; i++)
        pthread_join(write[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&writer);

    printf("\n");
    return 0;
}