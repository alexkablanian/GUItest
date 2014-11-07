#ifndef MAP_H
#define MAP_H

#include <cstddef>

//struct for a mapitem that is added to the map class (a node)
template <class keyType, class valueType>
struct MapItem
{
	keyType key;
	valueType value;
	MapItem <keyType, valueType> *prev, *next;
};

//struct for iterators 
template <class FirstType, class SecondType>
struct Pair
{
	FirstType first;
	SecondType second; 

	Pair (FirstType first, SecondType second){
		this -> first =  first;
		this -> second  = second; 
	}
};

template <class keyType, class valueType>
class Map
{
public:
	// constructor for a new empty map
	Map(); 

	// copy construct
	Map (const Map<keyType, valueType> & other);

	MapItem <keyType, valueType>* returnHead();

	//destructor for Map objects
	~Map(); 

	// returns number of key value pairs
	int size() const; 

	//adds a new association between the given key and the given value
	// if the key already has an association, it should do nothing
	void add(const keyType &key, const valueType &value);

	// removes the associations for the given key
	// if the key has no association it should do nothing
	void remove (const keyType &key);

	// returns the value associated with a given key
	// if the key existed in the map, success should be set to true
	// if the key has no association, success = false	
	const valueType & get (const keyType &key) const;

	// adds all the key value associations of other to the current map
	// if both maps (this and other) contain an assocation for the same key,
	// then the one of this is used
	//same as union?
	void merge (const Map <keyType, valueType> & other);

	Map <keyType, valueType>* mapUnion (const Map <keyType, valueType> & other) const;	

	Map <keyType, valueType>* mapIntersection (const Map <keyType, valueType> & other) const;	
	//helper for my set intersection

	//checker to see if a key already exists in a map
	bool checker (const keyType &key) const;

	//operator overload of = to deepcopy
	Map<keyType, valueType> & operator = (const Map <keyType, valueType> & other);

	//find function for iterator 


	//advanced iterator class 
	class Iterator{
	public:
		//add any public or private constructors that might be important
		//need to construcor iterator pointing to head
		//make Map a friend:
		friend class Map<keyType, valueType>;

		//public constructor?
		Iterator(){
			//default
		}

		Pair <keyType, valueType> operator* () const{
			return Pair <keyType, valueType> (currentIteratorPtr->key, currentIteratorPtr-> value); 
		}

		//return the current (key, value) pair where the iterator is
		
		Map <keyType, valueType> ::Iterator operator++(){
			currentIteratorPtr = currentIteratorPtr -> next;
			return *this;
		}
		//advances the iterator (pre-increment)

		Map <keyType, valueType>::Iterator operator= (const Map<keyType, valueType>::Iterator & other){
			this -> currentIteratorPtr = other.currentIteratorPtr;
			this -> whoIbelongTo = other.whoIbelongTo;
			return *this;
		}
		//assigns the other iterator to this and returns this

		bool operator==(const Map<keyType, valueType>::Iterator & other)const{
			return (currentIteratorPtr == other.currentIteratorPtr && whoIbelongTo == other.whoIbelongTo);
		}
		//returns whether this iterator is equal to the iterator of other 

		bool operator!=(const Map<keyType, valueType>::Iterator & other)const{
			return (!this->operator==(other));			
		}	
		//returns whether this iterator is not equal to the other iterator 	 

		// can add copy constructors or other operator overloads if need be

	private:
		// what to add?
		//private constructor that sets private variables of iterator to a map pointer and node 
		//private constructor becuase only the map calss itself should be able to initialize an iterator 
		Iterator (const Map <keyType, valueType> *m, MapItem <keyType, valueType> *item){
			whoIbelongTo = m;
			currentIteratorPtr = item; 
		} 

		//ADT associated with iterator? - pointer 
		//don't think i need it because this will correspond to this-> map
		const Map <keyType, valueType>* whoIbelongTo;

		// current location in collection? - pointer 
		MapItem <keyType, valueType> *currentIteratorPtr;
	};

	Map <keyType, valueType> ::Iterator begin() const{
		return Map <keyType, valueType> :: Iterator (this, head);
	}
	//returns an iterator initialized to the first element of this map
	//will return private variable currentIteratorPtr after setting it to this->head

	Map <keyType, valueType> :: Iterator end() const{
		//returning an iterator pointer that corrresponds to map this and mapitem pointer null 
		return Map <keyType, valueType> :: Iterator (this, NULL);
	}
	//returns an iterator initialized to the last element of this map to designate end of map
	//will return iterator set to this ->tail 

private:
	// the head and tail of the linked list you're using to store all associations
	MapItem <keyType, valueType> *head, *tail;
	//ponter traverser of type mapitem that is used to shuffle through map
	MapItem <keyType, valueType> *traverser;
};

#include "MapImpl.h"
#endif