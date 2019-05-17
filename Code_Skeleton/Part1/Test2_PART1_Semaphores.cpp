// Cpp program to demonstrate working of Semaphores
#include "Semaphore.hpp"

Semaphore sem_mutex(1);

void* thread(void* arg)
{
    //wait
    //===sem_mutex.down();
    printf("\nEntered..\n");

    //critical section
    sleep(4);

    //signal
    printf("\nJust Exiting...\n");
    //===sem_mutex.up();
}


int main()
{
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread,NULL);
    sleep(2);
    pthread_create(&t2,NULL,thread,NULL);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
