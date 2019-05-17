// #include "PCQueue.hpp"
//
// template <class T> // Add definition in PCQueue.hpp if you need this constructor
// PCQueue<T>::PCQueue(): queue_lock(1), available_items() {
//
// }
//
// // Blocks while queue is empty. When queue holds items, allows for a single
// // thread to enter and remove an item from the front of the queue and return it.
// // Assumes multiple consumers.
// template <class T>
// T PCQueue<T>::pop(){
//   T item;
//   queue_lock.down();
//   available_items.down();
//   item = q.front();
//   q.pop();
//   queue_lock.up();
//   return item;
// }
//
// // Allows for producer to enter with *minimal delay* and push items to back of the queue.
// // Hint for *minimal delay* - Allow the consumers to delay the producer as little as possible.
// // Assumes single producer
// template <class T>
// void PCQueue<T>::push(const T& item){
//   queue_lock.down();
//   q.push(item);
//   available_items.up();
//   queue_lock.up();
// }
