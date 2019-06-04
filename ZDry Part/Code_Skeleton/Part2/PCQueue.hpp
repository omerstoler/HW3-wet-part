#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"
#include "Semaphore.hpp"
// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:
	// default constructor
	PCQueue() : available_items(), producers_waiting(0) {
		pthread_mutex_init(&queue_lock, NULL);
		pthread_cond_init(&pop_prohibited, NULL);
	};

	// Blocks while queue is empty. When queue holds items, allows for a single
	// thread to enter and remove an item from the front of the queue and return it.
	// Assumes multiple consumers.
	T pop(){
		T item;
		available_items.down();
	  pthread_mutex_lock(&queue_lock);

		while(producers_waiting > 0)
			pthread_cond_wait(&pop_prohibited, &queue_lock);

	  item = q.front();
	  q.pop();
	  pthread_mutex_unlock(&queue_lock);
	  return item;
	};

	// Allows for producer to enter with *minimal delay* and push items to back of the queue.
	// Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.
	// Assumes single producer
	void push(const T& item){

		producers_waiting++; //==== safe only when single-producer

		pthread_mutex_lock(&queue_lock);
		q.push(item);
		available_items.up();

		producers_waiting--;
		pthread_cond_broadcast(&pop_prohibited);
		pthread_mutex_unlock(&queue_lock);
	};


private:
	// Add your class memebers here
	std::queue<T> q;
	//Semaphore free_space;
	Semaphore available_items;
	pthread_mutex_t  queue_lock;

	int producers_waiting;
	pthread_cond_t pop_prohibited;
};
// Recommendation: Use the implementation of the std::queue for this exercise
#endif
