#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10
#define ITERATIONS 10

int counter = 0; // Shared resource

void* increment_counter(void* arg) {
    for (int i = 0; i < ITERATIONS; i++) {
        counter++;
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

    return 0;
}
