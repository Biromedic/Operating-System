#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include<unistd.h>
#include <stdlib.h>


# define N 10                                      //Number of elements in Buffer
# define True 1
typedef int semaphore; 	     //Semaphores are defined as an int.
sem_t mutex; 		  //mutual exclusion of critical part
sem_t empty; 		//The number of empty space in the buffer
sem_t full; 		//The number of filled places in Buffer
int buffer[N] = {0};          // Shared buffer

int item = 0; // next produce  
int out = 0; // next consume

void print_buffer() {
    for (int i = 0; i < N; i++) {
        printf("%d\t", buffer[i]);
    }
    printf("\n");
}

void* producer() {
    while (True) {
        //item = rand() % N;
        
        sem_wait(&empty);	//Wait if the buffer is full, or reduce the number of empty spaces by 1.
        sem_wait(&mutex);     //Get permission to enter the critical section.
        
        buffer[item] = 1;  // Enter the data in Buffer.
        printf("Producer produced item, placed on %d.shelf\n", item + 1);
        item = (item + 1) % N;
        print_buffer();
        
        sem_post(&mutex);    //Indicate that it exits the Critical Section.
        sem_post(&full);       //If there are any consumers waiting, wake up, or increase the number of full places  in Buffer by 1.
        sleep(1);
    }
}

void* consumer(){
    //int item;   ->>>> it does not work since one variable not handle produce and consume at the same time. 
    
    while (True) { 
        sem_wait(&full); 	//Wait if the buffer is empty, or reduce the number of full places by 1
        sem_wait(&mutex);     //Get permission to enter the critical section
        
        buffer[out] = 0;  // Get data from Buffer
        printf("Consumer consumed item from %d.shelf\n", out + 1);
        print_buffer();
        out = (out + 1) % N;
        
        sem_post(&mutex); 		//Indicate that it exits the Critical Section
        sem_post(&empty); 	//If there is a manufacturer waiting, wake up, or increase the number of empty    spaces in Buffer by 1.
        
        sleep(1);
    }
}

void main(){
    
    sem_init(&empty,0,10);
    sem_init(&full,0,0);
    sem_init(&mutex,0,1);

    //pthread_t producer_thread, consumer_thread; does not work?
    pthread_t producer_threads[N], consumer_threads[N];
    
    // Create producer threads
    for(int i = 0; i < N; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL);
    }
    
    // Create consumer threads
    for(int i = 0; i < N; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }
    
    // Join producer threads
    for(int i = 0; i < N; i++) {
        pthread_join(producer_threads[i], NULL);
    }
    
    // Join consumer threads
    for(int i = 0; i < N; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex); 
    
}