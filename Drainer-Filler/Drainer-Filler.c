#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int water_level = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* filler(void *arg) {
    if(water_level <= 20) {
        while(water_level < 100) {
        pthread_mutex_lock(&lock);
        water_level += 10;
        printf("Filling: Water Level = %d\n", water_level);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(NULL);
    }
}

void *drainer() {
    //printf("buraya girdim");   
    pthread_mutex_lock(&lock);
    if (water_level > 0) {
    water_level -= 10;
    printf("Draining: Water Level = %d\n", water_level);
    }
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

int main() { 
    pthread_t filler_thread, drainer_thread;
    
    for(int i = 0; i < 100; i++) {
    pthread_create(&filler_thread, NULL, filler, NULL);
    pthread_create(&drainer_thread, NULL, drainer, NULL);
    pthread_join(filler_thread, NULL);
    pthread_join(drainer_thread, NULL);
    }   

    return 0;
}

