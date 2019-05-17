//#include "Semaphore.hpp"
#include "PCQueue.hpp"


#define NUM_PUSHES 10000
#define NUM_THREADS 31
#define NUM_POPS 1


void *PushPrint(void *given_q) {
  PCQueue<int> *q = (PCQueue<int>*)given_q;
  for (int i = 0; i < NUM_PUSHES; i++) {
    cout << "Current push: " << i << " , by thread: " << pthread_self() << endl;
    q->push(i);
  }
  pthread_exit(NULL);
}


void *PopPrint(void *given_q) {
   PCQueue<int> *q = (PCQueue<int>*)given_q;
   int head;
   for (int i = 0; i < NUM_POPS; i++) {
     head = q->pop();
     cout << "Current pop: " << head << " , by thread: " << pthread_self() << endl;
   }

   pthread_exit(NULL);
}

int main () {
   PCQueue<int> pcq;

   pthread_t threads[NUM_THREADS];
   int thread_error;
   int i;

   thread_error = pthread_create(&threads[0], NULL, PushPrint, (void *)&(pcq));
   if (thread_error) {
      cout << "Error:unable to create thread," << thread_error << endl;
      exit(-1);
   }
   for( i = 1; i < NUM_THREADS; i++ ) {

      cout << "main() : creating thread " << i << endl;
      thread_error = pthread_create(&threads[i], NULL, PopPrint, (void *)&(pcq));

      if (thread_error) {
         cout << "Error:unable to create thread," << thread_error << endl;
         exit(-1);
      }
   }


   pthread_exit(NULL);
}
