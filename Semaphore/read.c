#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_READERS 5
#define MAX_WRITERS 2

sem_t mutex, wrt;
int readers_count = 0;

void *reader(void *arg) {
    FILE *file = (FILE *)arg;
    while(1) {
        sem_wait(&mutex);
        readers_count++;
        if(readers_count == 1) {
            sem_wait(&wrt);
        }
        sem_post(&mutex);

        // Read from file
        fseek(file, 0, SEEK_SET); // Rewind file
        char buffer[256];
        while(fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("Reader %ld: %s", pthread_self(), buffer);
        }

        sem_wait(&mutex);
        readers_count--;
        if(readers_count == 0) {
            sem_post(&wrt);
        }
        sem_post(&mutex);

        usleep(rand() % 1000000); // Sleep for random time
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    FILE *file = (FILE *)arg;
    while(1) {
        sem_wait(&wrt);

        // Write to file
        fseek(file, 0, SEEK_END); // Move file pointer to the end
        fprintf(file, "Data written by Writer %ld\n", pthread_self());
        fflush(file);

        sem_post(&wrt);

        usleep(rand() % 1000000); // Sleep for random time
    }
    pthread_exit(NULL);
}

int main() {
    FILE *file = fopen("data.txt", "a+"); // Open file for appending and reading

    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    pthread_t readers[MAX_READERS];
    pthread_t writers[MAX_WRITERS];

    srand(time(NULL));

    // Create reader threads
    for(int i = 0; i < MAX_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void *)file);
    }

    // Create writer threads
    for(int i = 0; i < MAX_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void *)file);
    }

    // Join threads
    for(int i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for(int i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    fclose(file);
    sem_destroy(&mutex);
    sem_destroy(&wrt);
    return 0;
}

