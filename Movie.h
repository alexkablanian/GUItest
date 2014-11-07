#ifndef MOVIE_H
#define MOVIE_H

#include "Set.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>

class Movie{
public:
	//constructor 
	Movie(string title);

	//destructor 
	~Movie();

	//size checker
	int sizeSet();

	//copy constructor that creates a new movie object with title = title of the movie obejct you pass in 
	Movie(const Movie & other);

	//returns the title of a given movie object
	string getTitle() const;

	//adds key words to a set of keywords
	void addKeyword(string keyword);

	//returns a set of all keywords associated with the movie 
	Set <string> getAllKeywords() const;

	void displayMovie(string movieTitle);

private:
	string movieTitle;
	Set <string> keywordSet;
};

#endif