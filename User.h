#ifndef USER_H
#define USER_H

#include "Movie.cpp"
#include "Queue.h"

class User
{
public:
	//constructor that creates a new user object with id and name
	User(string id, string name);
	
	//copy constructor that creates a user name equal to a passed in user name
	User(const User & other);
	
	~User();

	//return function that returns ID associated with user
	string getID() const;

	//return function that returns name associated with user
	string getName() const;

	//checker to see if the user id already exists
	bool idChecker(string id);

	//new ads 
	Queue <Movie*> *movieQueue();
	// returns a pointer to the users movie queue (so have a private variable called movie queue?)

	void rentMovie (Movie *m);

	void returnMovie ();

	Movie* currentMovie();
	//returns users current checked out movie 
	void stringMovie (string m);

	string getMovieString();

private:
	//private variables name and id
	string userID;
	string userFullName;
	
	Movie *checkedOutMovie; // movie pointer that corresponds to a movie if checked out 
	Queue <Movie*> *userQueue; 
	
	string rentedMovie; 
};

#endif