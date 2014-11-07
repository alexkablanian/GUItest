#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

//constructor for a new empty set
template <class T>
Set<T>::Set(){
}

template <class T>
Set<T>::Set(const Set<T> &other){
	//need this to work before i can get set merge/intersection to work
	cout << "Copy constructor for set does not work currently." << endl;
	cout << "Create a new Set and set it equal to an existing set using the '=' operator" << endl;
	cout << "Other size is " << other.size() <<endl;
	//use merge function from map because no data whe creating a set to be copied
	internalStorage.merge(other.internalStorage);
}


//default destructor (uses map destructor to delete allocated memory)
template <class T>
Set<T>::~Set(){
}

// returns the number of elements in the set by using the map.size function
template <class T>
int Set<T>::size () const{
	return this-> internalStorage.size();
}

// Adds the item to the set by utilizing the map.add function
// the key and value are both the item name
template <class T>
void Set<T>::add (const T &item){
	this -> internalStorage.add(item, item); 
}

// Removes the item from the set using the map.remove function
template <class T>
void Set<T>::remove (const T &item){
	this-> internalStorage.remove(item);
}

//Returns a true/false variable depending on if the item already exists in the set
template <class T>
bool Set<T>::contains (const T &item) const{
	bool success = false;
	try{
		if (this -> internalStorage.get(item) == item){
		success = true;
		return success; }
	}
	catch (NoSuchElementException e){
		return success;
	}
	return success;
}

//Adds all the elements of other to this set using the merge function in map.merge
template <class T>
void Set<T>::merge (const Set <T> & other){
	this-> internalStorage.merge(other.internalStorage);
}

//operator equals function that sets this-> set = other.set
template <class T>
Set<T> Set<T>::operator= (const Set <T> & other){
	this -> internalStorage.operator=(other.internalStorage);
	return *this;
}

//works just need to deallocate memory from this set
template <class T>
Set<T>* Set <T>::setUnion(const Set<T> &other) const{
	//create new set
	//run merge fucntion to make the sets the same
	//return pointer to set
	Set <string> *unionSet = new Set<T> ();
	unionSet->internalStorage.merge(this->internalStorage);
	unionSet->internalStorage.merge(other.internalStorage);
	//cout << unionSet->internalStorage.size() << endl;
	return unionSet;
}


//set intersection takes two sets and creates a third
//the third returns the common elements of both sets

template <class T>
Set<T>* Set <T>::setIntersection (const Set<T> &other) const{
	Set <T> *intersectionSet = new Set <T> ();

	Map <T, T> *pointer = internalStorage.mapIntersection(other.internalStorage);
	intersectionSet->internalStorage.merge (*pointer);
	
	cout << pointer->size() << endl;
	delete pointer;

	return intersectionSet;
}