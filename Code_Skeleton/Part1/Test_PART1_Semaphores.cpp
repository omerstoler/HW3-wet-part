#include "Semaphore.hpp"


#define NUM_THREADS 5
#define SEM_COUNT_INIT 1

void *PrintHello(void *threadid) {
   long tid;
   tid = (long)threadid;
   printf("Hello World! Thread ID, %d\n", tid);
   pthread_exit(NULL);
}

int main () {
   Semaphore sem(SEM_COUNT_INIT);

   pthread_t threads[NUM_THREADS];
   int thread_error;
   int i;
   //Semaphore smp(1); // binary semaphore testing

   for( i = 0; i < NUM_THREADS; i++ ) {
      cout << "main() : creating thread " << i << endl;
      thread_error = pthread_create(&threads[i], NULL, PrintHello, (void *)i);

      if (thread_error) {
         cout << "Error:unable to create thread," << thread_error << endl;
         exit(-1);
      }
   }
   //smp.up();


   pthread_exit(NULL);
}
