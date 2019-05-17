#ifndef _QUEUEL_H
#define _QUEUEL_H
#include "Headers.hpp"
#include "Semaphore.hpp"
// Single Producer - Multiple Consumer queue
template <typename T>class PCQueue
{

public:
	// default constructor
	PCQueue() : queue_lock(1), available_items() {};

	// Blocks while queue is empty. When queue holds items, allows for a single
	// thread to enter and remove an item from the front of the queue and return it.
	// Assumes multiple consumers.
	T pop(){
		T item;
		queue_lock.down();
		available_items.down();
		item = q.pop();
		queue_lock.up();
		return item;
	};

	// Allows for producer to enter with *minimal delay* and push items to back of the queue.
	// Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.
	// Assumes single producer
	void push(const T& item){
		queue_lock.down();
		q.push(item);
		available_items.up();
		queue_lock.up();
	};


private:
	// Add your class memebers here
	std::queue<T> q;
	//Semaphore free_space;
	Semaphore available_items;
	Semaphore queue_lock;
};
// Recommendation: Use the implementation of the std::queue for this exercise
#endif
