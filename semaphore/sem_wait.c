// The following example retrieves the value of 
//a semaphore before and after it is decremented by sem_wait().

#include <stdio.h>
#include <semaphore.h>

main() {
  sem_t my_semaphore;
  int value;

  sem_init(&my_semaphore, 0, 10);
  sem_getvalue(&my_semaphore, &value);
  printf("The initial value of the semaphore is %d\n", value);
  sem_wait(&my_semaphore);
  sem_getvalue(&my_semaphore, &value);
  printf("The value of the semaphore after the wait is %d\n", value);

}

/*

Output:

The initial value of the semaphore is 10
The value of the semaphore after the wait is 9

*/
