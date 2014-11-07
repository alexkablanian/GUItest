#include <iostream>
#include <cstring>
#include <cstdlib>
//#include "EmptyQueueException.h"

using namespace std;

//implement as a linked list 

//default consttructor is fine
template <class T>
Queue<T>::Queue(){
	this->size = 0;
	head = NULL;
	tail = NULL;
}

//queue destructor 
template <class T>
Queue<T>::~Queue(){
	//need to delete like in map 
	Node <T> *holder = head, *q = NULL;
	while (holder!= NULL){
		//while there is still something in the list go to the next node and deallocate memory
		q = holder -> next;
		delete holder;
		//switch pointers and continue until p is null
		holder = q;
	}	
}

//enqueue function adds 
template <class T>
void Queue<T>::enqueue (const T & item){
	size ++;
	Node <T> *holder = new Node <T> ();
	holder -> object = item;
	holder -> next = NULL;

	if (head == NULL){
		head = holder;
		tail = holder;
	}
	else{
		tail -> next = holder;
		tail = holder;
	}
	//set tail pointer to find end if need be 
}

//dequue functions deletes top node
//memory leak somewhere in here 
template <class T>
void Queue<T>::dequeue (){
	size --; //delete one from size
	//check to make sure queue is full 
	if (head == NULL){
		cout << "Queue is empty" << endl;
	}
	else{
		//memory leak somewhere in here 	
		Node <T> *holder = new Node<T> (); //declare new holder ptr
		//Node <T> *holder;
		//if queue has top object, set new node pointer to it
		holder= head;
		//set head pointer to the next object
		head = head -> next;
		//delete holder pointer 
		delete holder;
	}
}

//will return the object associated with head pointer (i.e. front of list)
template <class T>
const T & Queue<T>::peekfront (){
	//if (isEmpty()){
		//throw EmptyQueueException (); 

	//}
	//else{
		return head -> object;
	//}
}

//use private variable size to check if there are or are not nodes in queue 
template <class T>
bool Queue<T>::isEmpty (){
	if (size > 0){
		return false; //if size of queu is greater than 0 then queue is not empty
	}
	else{
		return true;
	}
}