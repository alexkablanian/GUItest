#include <iostream>
#include <cstring>
#include <cstdlib>
#include "User.h"

using namespace std;

User::User(string id, string name){
	//constructor creates a movie object of type map
	//then adds this element to the map
	this -> userID = id;
	this -> userFullName = name;
	checkedOutMovie = NULL;
	rentedMovie = "no movie";
	//dynamically allocated a queue of movie pointers every time user created 
	userQueue = new Queue <Movie*> ();
}

//copy constructor that creates a user with same values as another user why do we need this?
User::User(const User & other){
	this -> userID = other.userID;
	this -> userFullName = other.userFullName;
}

User::~User(){
	//default destructor
	delete userQueue;
}

//simple string return function to return id name
string User::getID() const{
	return this -> userID;
}

//simple string return function to return full name
string User::getName() const{
	return this -> userFullName;
}

Queue <Movie*> * User::movieQueue(){
	return userQueue;
}
	// returns a pointer to the users movie queue (so have a private variable called movie queue?)

void User::rentMovie (Movie *m){
	checkedOutMovie = m;
}
//set private variable to this pointer

void User::returnMovie (){
	checkedOutMovie = NULL;
}
//set private variable to null

Movie* User::currentMovie(){
	return checkedOutMovie;
}
//returns users current checked out movie 

//helper functions to help add movie objects to user rented movies 
void User::stringMovie(string m){
	rentedMovie = m;
}

string User::getMovieString(){
	return rentedMovie;
}