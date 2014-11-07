#ifndef SET_H
#define SET_H

//includes all map functionality to be implemented by set
#include "Map.h"

template <class T>
class Set
{
public: 
//	friend class Map<keyType, valueType>;

	//constructor for a new empty set
	Set();

	//copy constructor for sets
	Set(const Set<T> &other);

	//destructor
	~Set();

	// returns the number of elements in the set
	int size () const;

	// Adds the item to the set
	//If the item is already in the set, it should do nothing.
	void add (const T &item);

	// Removes the item from the set
	//If the item is already in the set, it should do nothing.	
	void remove (const T &item);

	//Returns whether the item is in the set
	bool contains (const T &item) const;

	//Adds all the elements of other to this set
	// However, will not create duplicates
	//i.e. it ignores elements already in the set
	void merge (const Set <T> & other);

	Set<T> operator= (const Set <T> & other);

	Set <T>* setUnion(const Set<T> &other) const;
	//returns union of this set and other (does not alter this)

	Set <T>* setIntersection (const Set<T> &other) const;
	//returns intersection of this set and other (does not alter this)
	//maybe declare a new set within this and populate it with the intersection of this and other?

	class Iterator{
	public:
		friend class Set <T>;

		T operator* () const{
			return ((*current).first);
		}
		//returns the item the iterator is at

		Set <T> ::Iterator operator ++ (){
			++current;
			return *this;
		}

		Set <T> ::Iterator operator= (const Set <T> ::Iterator & other){
			this->current = other.current;
			this -> whoIbelongto = other.whoIbelongto;
			return *this;
		}

		bool operator == (const Set <T>::Iterator & other) const{
			return ((this ->current == other.current) && (this->whoIbelongto == other.whoIbelongto));
		}

		bool operator != (const Set <T>::Iterator & other) const{
			return (this ->current != other.current);
		}		

	private:
		Iterator (const Set<T> *thisSet, typename Map <T,T>::Iterator i):current(i){
			whoIbelongto = thisSet;
		}	

		//pointer to the set this iterator belongs to
		const Set<T> *whoIbelongto;

		//map iterator ( a pointer to a map)
		typename Map <T, T>::Iterator current;
	};

	Set <T>::Iterator begin() const{
		Set<T>::Iterator it (this, internalStorage.begin());
		return it;
	}

	Set <T>::Iterator end() const{
		Set<T>::Iterator it (this, internalStorage.end());
		return it;
	}

private:
	//as a relationship with Map
	Map <T, T> internalStorage;
};

#include "SetImpl.h"
#endif 