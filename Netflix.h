#ifndef NETFLIX_H
#define NETFLIX_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <cctype>
#include "User.h"

using namespace std;

class Netflix {
public:
	//put all functions below this class 
	Netflix();

	Netflix(string datafile);

	~Netflix();
	//done
	void readIn(string filename); //read in both user file and movie file and asign to respective queues 
	
	//done
	void printUserMenu(); //print out original log in menu 

	//Map <string, User*>::Iterator login(string username);
	void login(string username);
	void checker();

	void printMovieMenu();
	void movieSearch(string movieTitle);
	void addToQueue();
	void keywordSearch(string keywordInput);
	void returnCurrentMovie();

	void printQueueMenu();

	void OrderMovie();
	void RemoveFromQueue();
	void MoveToBack();

	bool checkUser(string username);
	void createUser(string username, string fullname);
	
	//done
	void writeOut(); //write out at end of file 
	//done except for queue allocation
	void memoryDeallocate();

private:
//include pointers to all data structures of netflix here --> is this the right way to do it?	
	//pointer to a set of existing users
	Set <string> *existingUsers;
	//pointer to a map of user objects (key = username, value =  user object)
	Map <string, User*> *allUsers;
	
	Map <string, User*>::Iterator loginIter; 
	//pointer to a map of movie objects  (key = movie title, value = movie object)
	Map <string, Movie*> *titles;	
	//pointer to a set of movie objets 
	Set <Movie*> *setOfMovies;
	//pointer to a map of sets of movie objects (key = keyword, value = set of movie objects)	
	Map <string, Set<Movie*>*> *movieKeywords;

	Movie *movieHolder; 

	string writeOutFile;
};

#endif 