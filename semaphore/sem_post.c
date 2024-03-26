//The following example initializes an unnamed semaphore 
//and posts to it, incrementing its value by 1.
#include <stdio.h>
#include <semaphore.h>

main() {
  sem_t my_semaphore;
  int value;

  sem_init(&my_semaphore, 0, 10);
  sem_getvalue(&my_semaphore, &value);
  printf("The initial value of the semaphore is %d\n", value);
  sem_post(&my_semaphore);
  sem_getvalue(&my_semaphore, &value);
  printf("The value of the semaphore after the post is %d\n", value);

}

/*
Output:

The initial value of the semaphore is 10
The value of the semaphore after the post is 11

*/
