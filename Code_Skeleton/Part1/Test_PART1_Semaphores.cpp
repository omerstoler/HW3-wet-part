#include "Semaphore.hpp"


#define NUM_THREADS 5
#define SEM_COUNT_INIT 1

int x = 0;

typedef struct params{
  long i;
  Semaphore* sem;
} params_t;

void *PrintHello(void *params) {
   long tid;
   params_t *local_params;
   local_params = (params_t*)params;

   tid = (long)(local_params->i);
   printf("Hello World! Thread ID, %d\n", tid);
   x++;
   printf("x = %d\n", x);
   pthread_exit(NULL);
}

int main () {
   Semaphore sem(SEM_COUNT_INIT);
   params_t params;

   pthread_t threads[NUM_THREADS];
   int thread_error;
   int i;
   //Semaphore smp(1); // binary semaphore testing

   params.sem = &sem;

   for( i = 0; i < NUM_THREADS; i++ ) {
      params.i = i;

      cout << "main() : creating thread " << i << endl;
      thread_error = pthread_create(&threads[i], NULL, PrintHello, (void *)&params);

      if (thread_error) {
         cout << "Error:unable to create thread," << thread_error << endl;
         exit(-1);
      }
   }
   //smp.up();


   pthread_exit(NULL);
}
