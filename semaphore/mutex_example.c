#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;

void *thread_function(void *arg)
{
    // ANSI escape codes for colors
    const char* green = "\033[32m";
    const char* red = "\033[31m";
    const char* reset = "\033[0m";

    double time_taken;

    pthread_mutex_lock(&lock);
    // Critical section starts
    printf("%sThread %ld has entered the critical section.%s\n", green, (long)arg, reset);
    // Simulating critical section work
    usleep(50000);
    printf("%sThread %ld is leaving the critical section.%s\n", red, (long)arg, reset);
    // Critical section ends
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t threads[100];
    int threads_num[100];

    for (int i = 0; i < 100; i++)
    {
        threads_num[i] = i + 1;
    }
    

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create threads
    for (int i = 0; i < 100; i++)
    {
        pthread_create(&threads[i], NULL, thread_function, (void *)(long)threads_num[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 100; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
