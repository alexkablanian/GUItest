#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include "Movie.h"

using namespace std;

//constructor that creates a movie object that has title passed in
Movie::Movie(string title){
	this -> movieTitle = title;
}

//copy constructor that creates a new movie object with title = title of the movie obejct you pass in 
Movie::Movie(const Movie & other){
	this -> movieTitle = other.movieTitle;
}

//default destructor 
Movie::~Movie(){
}

//returns an int that is the size of the set of keywods associate with this-> movie
int Movie::sizeSet(){
	return keywordSet.size();
}

//get title just returns the movie objects title
string Movie::getTitle() const{
	string upperCase = this -> movieTitle;
	upperCase[0] = toupper(upperCase[0]);
	int upperCaseSize = (int) upperCase.size();

	for (int i = 0; i< upperCaseSize; i++){
		if(upperCase[i] == ' '){
			upperCase[i+1] = toupper(upperCase[i+1]);
		}
	}	
	return upperCase;
}

void Movie::addKeyword(string keyword){
	//add keyword to set of movie keywords
	if (keywordSet.contains(keyword)==false){
		keywordSet.add (keyword);
	}
	return;
}

Set <string> Movie::getAllKeywords() const{
	// return set of keywords
	return keywordSet;
}

//function to display set of keys if given a movie title
void Movie::displayMovie(string movieTitle){
	//set keyword set to head
	Set<string>::Iterator firstKey = keywordSet.begin();
	//capitalize the right letters for movie title
	movieTitle[0] = toupper(movieTitle[0]);
	int movieTitleSize = (int) movieTitle.size();

	for (int i = 0; i< movieTitleSize; i++){
		if(movieTitle[i] == ' '){
			movieTitle[i+1] = toupper(movieTitle[i+1]);
		}
	}

	cout << movieTitle << endl;
	//call a for loop that shuffles through keywordset.size numbers of times and outputs the current element
	//set traverser to the next element or throw an exception if done
	for (int i =0; i < keywordSet.size(); i++){
		//string holder = keywordSet.getCurrent();
		string holder = *firstKey;
		holder[0] = toupper(holder[0]);

		int holderSize = (int) holder.size();
		for (int j = 0; j < holderSize; j++){
			if (holder[i]== ' '){
				holder[i+1] = toupper(holder[i+1]);
			}
		}
		cout << holder << endl;
		try{
			//keywordSet.next();
			++firstKey;
		}
		catch (NoSuchElementException e){
		}
	}
}
