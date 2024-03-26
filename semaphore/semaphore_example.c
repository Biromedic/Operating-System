#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t my_semaphore;

void* thread_function(void* arg) {
    // ANSI escape codes for colors
    const char* green = "\033[32m";
    const char* red = "\033[31m";
    const char* reset = "\033[0m";

    sem_wait(&my_semaphore);
    // Critical section starts
    printf("%sThread %ld has entered the critical section.%s\n", green, (long)arg, reset);
    // Simulating critical section work
    sleep(5);
    printf("%sThread %ld is leaving the critical section.%s\n", red, (long)arg, reset);
    // Critical section ends
    sem_post(&my_semaphore);
    return NULL;
}

int main() {
    pthread_t threads[100];
    int threads_num[100];

    for (int i = 0; i < 100; i++) {
        threads_num[i] = i + 1;
    }

    // Initialize the semaphore to allow 10 threads at a time
    sem_init(&my_semaphore, 0, 10);

    // Create multiple threads
    for (long i = 0; i < 100; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void *)(long)threads_num[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up semaphore
    sem_destroy(&my_semaphore);

    return 0;
}
