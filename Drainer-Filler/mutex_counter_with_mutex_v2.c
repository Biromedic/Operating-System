#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10
#define ITERATIONS 1000000

int counter = 0; // Shared resource
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for protecting the counter

void* increment_counter(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        pthread_mutex_lock(&counter_mutex); // Lock the mutex before accessing the shared resource
        counter++;
        pthread_mutex_unlock(&counter_mutex); // Unlock the mutex after accessing the shared resource
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NTHREADS];
    
    // Create threads
    for (int i = 0; i < NTHREADS; i++) {
        pthread_create(&threads[i], NULL, increment_counter, NULL);
    }

    // Join threads
    for (int i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter value: %d\n", NTHREADS * ITERATIONS);
    printf("Actual counter value: %d\n", counter);

    // Clean up the mutex
    pthread_mutex_destroy(&counter_mutex);

    return 0;
}
