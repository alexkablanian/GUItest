#ifndef QUEUE_H
#define QUEUE_H

template <class T>
struct Node{
	T object;

	struct Node *next;
};

template <class T>
class Queue{
public:
	Queue();

	~Queue();

	void enqueue (const T & item);
	//adds item to end of queue, same item can be added many times

	void dequeue();
	//removes from top of queue
	//throw empty queue exception if nothing in queue (inherit from std:: exception)
	
	const T & peekfront();
	//returns front element of queue, otherwise throws empty exceptions

	bool isEmpty();
	//returns whether empty or not

private:
	Node<T> *head, *tail;
	int size;
};

#include "QueueImpl.h"
#endif