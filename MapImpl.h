#include <iostream>
#include <cstring>
#include <cstdlib>
#include "NoSuchElementException.h"

using namespace std;

//constructor of an empty map
template <class keyType, class valueType>
Map<keyType, valueType>::Map(){
	//empty map means declare pointer to head and tail = null
	head = NULL; 
	tail = NULL;
}

//copy constructor = deep copy (works)
template <class keyType, class valueType>
Map <keyType, valueType>::Map (const Map<keyType, valueType> & other){
	//copy constructor
	MapItem <keyType, valueType> *temp = other.head;

	while (temp -> next != NULL){
		//deep copy here
		//go to head and scroll through until reach null then add to that end
		//add function for each new node we want to create 
		this -> add(temp->key, temp -> value);
		temp = temp -> next;
	}
	//if there is only one item in map, then it will not even enter the while loop
	//because temp -> next is NULL so must ensure that it adds at least that one element
	//same will apply if it gets to the last element
	this -> add(temp->key, temp -> value);
}


//destructor statement must delete linked list memory
template <class keyType, class valueType>
Map<keyType, valueType>::~Map(){
	//declaring Mapitem pointers to head value and to a null value
	MapItem <keyType, valueType> *p = head, *q = NULL;
	while (p!= NULL){
		//while there is still something in the list go to the next node and deallocate memory
		q = p -> next;
		delete p;
		//switch pointers and continue until p is null
		p = q;
	}
}

//counter for how many nodes there are in a given map
template <class keyType, class valueType>
int Map<keyType, valueType>::size()const{
	//declare a counter and look through Map until reach null pointer
	int counter = 0; 

	//if head is null, means nothing in the map so returns 0
	if (head == NULL){
		counter = 0;
	}
	else{
		//assign temporary pointer that equals head
		MapItem <keyType, valueType> *temp;
		temp = head;
		//shuffle through map and increment counter every go around
		while (temp != NULL){
			counter++;
			//must reassign pointer to next and continue loop until temp -> next = NULL
			temp = temp -> next;
		}
	}
	return counter;
}

//add function
template <class keyType, class valueType>
void Map<keyType, valueType>::add(const keyType &key, const valueType &value){
	//declares a new MapItem called newNode
	MapItem <keyType, valueType> *newNode = new MapItem <keyType, valueType>;
	//inputs value of key and value into newNode and initiates next/prev to NULL
	newNode -> key = key;
	newNode -> value = value;
	newNode -> next = NULL;
	newNode -> prev = NULL;
	
	//if the map is empty, set head to newNode (beginning of list)
	if (head == NULL){
		head = newNode;
		return;
	}
	//otherwise, find the end of the list and point next to newnode
	else{
		MapItem <keyType, valueType> *temp;
		temp = head;
		
		while (temp -> next !=NULL){
			temp = temp -> next;
		}
		newNode -> prev = temp;
		temp -> next = newNode;
	}
	return;
}

//get function that finds a key and returns the value associated with it
template <class keyType, class valueType>
const valueType & Map <keyType, valueType>::get (const keyType &key) const{
	MapItem <keyType, valueType> *temp = head;

	//if head = null means the list is empty so cannot have the node you're looking for
	//throw exception and exit function
	if (head == NULL){
		//cout << "nothing there" << endl;
		throw NoSuchElementException();
	} 
	//if the head is the node you are looking it for, head -> value is returned
	else if (head->key == key){
		return head -> value;
	}
	//otherwise shuffle through the entire map until you find a key equal to the one that is passed in
	//once found return the value associated with that key and change bool value to true
	else {
		//cout << "Enter else loop" << endl;
		while (temp->next != NULL){
			temp = temp -> next;
			if(temp->key == key){
				return temp -> value;
			}
		}
		//throw an exception to exit function because the key was not found
		throw NoSuchElementException();
	}
}

//remove function deletes a node with a given key input
template <class keyType, class valueType>
void Map <keyType, valueType>::remove (const keyType &key){
	MapItem <keyType, valueType> *temp = head;

	//if head= null means there is nothing in the list so just end the function here
	if (head == NULL){
		return;
	} 

	//if head is equal to key then change the pointer of head to the next variable and delete the node
	else if (head->key == key){
		if (head -> next != NULL){
			head = temp -> next;
		}
		else{
			head = NULL;
		}
	}

	else {
		//run through the entire map, as long as next node is not null, look for key
		while (temp->next != NULL){
			temp = temp ->next;
			if(temp->key == key){
				//change pointers if you found key based on which side of the map is null
				if (temp -> next != NULL){
					temp -> next-> prev = temp -> prev;
				}
				if (temp -> prev != NULL){
					temp -> prev -> next = temp -> next;
				}
				delete temp;
			}
		}
	}
	return;	
}

//merge class puts two maps together
template <class keyType, class valueType>
void Map<keyType, valueType>::merge (const Map <keyType, valueType> & other){
	
	//declare two mapitems to point at the heads of eahc file
	MapItem <keyType, valueType> *temp2 = other.head;

	//as long as the second file has someting in it run this statement
	if (temp2 != NULL){
		//run through the entire second array and check for duplicates
		//if duplicates exist then skip over them
		for (int i = 0; i < other.size(); i++){
			if (this->checker(temp2->key)){
			}

			else{
				this -> add (temp2 -> key, temp2 ->value);
			}
			//as long as the map continues, change the pointer to continue the loop
			if (temp2 -> next !=NULL){
				temp2 = temp2 -> next;
			}
		}
	}
	return;
}

//this is my own helper function that checks for duplicates within a set
template <class keyType, class valueType>
bool Map<keyType, valueType>::checker (const keyType & key) const{

	//true means that a duplicate was found 
	MapItem <keyType, valueType> *temp = head;

	//if the list is empty then can't have duplicates, deallocate memory and return false
	if (head ==NULL){
		return false;
	}
	//if the head of the list is the same as the value you're looking for, deallocate memory and return true
	else if (head -> key == key){
		return true;
	}

	//otherwise huffle through the list, if you find the key then deallocate the memory and 
	//return true, otherwise deallocate memory and return false
	else{
		while (temp->next != NULL){
			temp = temp -> next;
			if (temp -> key == key){
				return true;
			}
		}
		return false;
	}
}

template <class keyType, class valueType>
Map<keyType, valueType> & Map<keyType, valueType>::operator= (const Map <keyType, valueType> & other){

	MapItem <keyType, valueType> *temp = other.head;
	//check to see if map is equal already to the other map
	if (this == &other){
		return *this;
	}

	else{
		if (temp == NULL){
			//delete memory and then set head = null to return an empty set
			MapItem <keyType, valueType> *p = head, *q = NULL;
			while (p->next != NULL){
				q = p->next;
				delete p;
				p = q;
			}
			this -> head = NULL;
			return *this;
		}

		else{
			//need to delete what's left over first in case there is something already there?
			//delete this;
			MapItem <keyType, valueType> *p = head, *q = NULL;
			while (p->next != NULL){
				q = p->next;
				delete p;
				p = q;
			}
			this -> head = NULL;

			while (temp -> next != NULL){
				//deep copy here
				//go to head and scroll through until reach null then add to that end
				//add function for each new node we want to create 
				this -> add(temp->key, temp -> value);
				temp = temp -> next;
			}
			//if there is only one item in map, then it will not even enter the while loop
			//because temp -> next is NULL so must ensure that it adds at least that one element
			//same will apply if it gets to the last element
			this -> add(temp->key, temp -> value);
			return *this;
		}
	}
}

//merge class puts two maps together
template <class keyType, class valueType>
Map<keyType, valueType>* Map<keyType, valueType>::mapIntersection (const Map <keyType, valueType> & other) const{
	
	Map <keyType, valueType> *intersectionMap = new Map <keyType, valueType> ();
	//declare a new map and return the pointer
	MapItem <keyType, valueType> *temp = head;
	MapItem <keyType, valueType> *temp2 = other.head;
	cout<<temp2<<" "<<temp<<" just checking pointers"<<endl;
	//as long as the second file has someting in it run this statement
	if (temp2 != NULL && temp != NULL){
		//run through the entire second array and check for duplicates
		//if duplicates exist then skip over them
		cout << "made it past first if" << endl;
		for (int i = 0; i < other.size(); i++){
			if (other.checker(temp->key)){
				intersectionMap -> add (temp2 -> key, temp2 ->value);			
			}

			else{
			}
			//as long as the map continues, change the pointer to continue the loop
			if (temp2 -> next !=NULL){
				temp2 = temp2 -> next;
				temp = temp -> next;
			}
		}
	}
	temp=NULL;
	temp2=NULL;
	return intersectionMap;
}

//union class puts two maps together
template <class keyType, class valueType>
Map<keyType, valueType>* Map<keyType, valueType>::mapUnion (const Map <keyType, valueType> & other) const{
	
	Map <string, string> *unionReturn = new Map <string, string> (*this);

	//declare two mapitems to point at the heads of eahc file
	MapItem <keyType, valueType> *temp2 = other.head;

	//as long as the second file has someting in it run this statement
	if (temp2 != NULL){
		//run through the entire second array and check for duplicates
		//if duplicates exist then skip over them
		for (int i = 0; i < other.size(); i++){
			if (unionReturn->checker(temp2->key)){
			}

			else{
				unionReturn -> add (temp2 -> key, temp2 ->value);
			}
			//as long as the map continues, change the pointer to continue the loop
			if (temp2 -> next !=NULL){
				temp2 = temp2 -> next;
			}
		}
	}
	return unionReturn;
}

template <class keyType, class valueType>
MapItem <keyType, valueType>* Map<keyType, valueType>::returnHead()
{
	return head;
}