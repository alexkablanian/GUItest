#include "Netflix.h"

Netflix::Netflix(){}

Netflix::Netflix(string datafile){
	readIn(datafile);
}

Netflix::~Netflix(){
	//default destructor 
}

void Netflix::printUserMenu(){
	cout << "Welcome to Netflix!" << endl;
	cout << "1. Log In" << endl;
	cout << "2. Create a New User" << endl;
	cout << "3. Quit" << endl;
	cout << "Enter a command (1-3) to run Netflix!" << endl;
}

void Netflix::readIn(string filename){
	//nead the input as the first element in argv[1] = datafile.txt then alloate arrays and access 
	ifstream dataFile;
	dataFile.open (filename.c_str());
	string userFileName, movieInfoFileName;
	getline (dataFile, userFileName);
	getline (dataFile, movieInfoFileName);	
	cerr <<  userFileName << endl;
	cerr << movieInfoFileName << endl;

	writeOutFile = userFileName;

	dataFile.close();

	existingUsers = new Set <string> ();	
	allUsers = new Map <string, User*> ();
	titles = new Map <string, Movie*> ();
	setOfMovies = new Set <Movie*> ();
	movieKeywords = new Map <string, Set<Movie*>*> ();

	ifstream userFile, movieFile;	

	//open movie information file 
	movieFile.open (movieInfoFileName.c_str());

	//declare input variables
	string movieLine, movieCommand, movieName, keywords, keywordLine;	

	while(!movieFile.eof()){
		movieFile >> movieCommand;
		
		//if first line is BEGIN then the rest of the line will be the movie name
		//create a movie object and add that movie object to the map of all movies
		if(movieCommand == "BEGIN"){
			getline(movieFile, movieLine);
			movieName = movieLine.substr(1);
			//add this in to enter all movies in lower case into array so that we can search 
			int movieNameSize = (int) movieName.size();
				for (int i = 0; i< movieNameSize; i++){
					movieName[i] = tolower(movieName[i]);
				}
				cerr << "Movie Name is " << movieName << endl;
				cerr << movieName.size() << endl;
				Movie *movieObject = new Movie (movieName);
				titles -> add (movieName, movieObject);
				setOfMovies->add(movieObject);
		}
		//if the line starts with KEYWORD, then go to the movie object and add the keywords to the set within
		//each movie object 
		else if (movieCommand == "KEYWORD:"){
			getline(movieFile, keywordLine);
			keywords = keywordLine.substr(1);
			int keywordsSize = (int) keywords.size();
			for(int i = 0; i < keywordsSize; i++){
				keywords[i] = tolower(keywords[i]);
			}
			cerr << "keyword to be entered is " << keywords << endl;
			titles->get(movieName)->addKeyword(keywords);
			//add all relevant movies to id type keyword
			//check to see if the keyword already has a map ID corresponding to it
			//if it does, add the movieName to the set of movies and if not, create a new 
			if (movieKeywords->checker(keywords)==true){
				movieKeywords->get(keywords)-> add(titles ->get(movieName));
			}
			if (movieKeywords->checker(keywords) == false){
				//create a new set of movies for this keyword?
				Set <Movie*> *newSet = new Set <Movie*> ();
				newSet->add(titles->get(movieName));
				cerr << "This is a new keyword!" << endl;
				movieKeywords->add(keywords, newSet);
			} 
		}
		//if command == "END" keep going
		else if (movieCommand == "END"){
			cerr << "Moving on to next movie" << endl;
		}	
		else{//do nothing
		}
	}
	//close out movie file
	movieFile.close();	

	//start read in user file 
	userFile.open(userFileName.c_str());
	
	//string declaration for inputs 
	string command, firstLine, username, firstName, lastName;	

	while(!userFile.eof()){
		//get the first word of the line to see what commands to do next
		userFile >> command;
		//cout << command << endl;

		//if line starts with BEGIN, the next word should be assigned to string username
		if(command == "BEGIN"){
			//splitUp >> username;
			//cout << "make it here?" << endl;
			getline(userFile, firstLine);
			if (firstLine != " QUEUE"){
				username = firstLine.substr(1);
				cerr << "Username is " << username << endl;
			} 
			else if (firstLine == "QUEUE" || firstLine == " QUEUE"){
					string nextLine;
					getline(userFile, nextLine);
					//cout << nextLine << endl;
					bool flag = true; 
					if (nextLine == "END QUEUE"){flag = false;}
					//string keepGoing;
					while (flag){
						cout << "top of while loop" <<  nextLine << endl;
						if (nextLine == "END QUEUE"){ 
							flag = false;
						}
						else{
							string movieQueueAdd = nextLine;
							int movieQueueAddSize = (int) movieQueueAdd.size();
							for (int i = 0; i< movieQueueAddSize; i++){
								movieQueueAdd[i] = tolower (movieQueueAdd[i]);
							}

							try{
								allUsers -> get(username) -> movieQueue() -> enqueue (titles -> get(movieQueueAdd));
							}
							catch (NoSuchElementException e){
								cout << "oops" << endl;
							}
							getline (userFile, nextLine);
						}
					}
			}
			else{
				//do nothing
			}
		}
		//if line starts with NAME: then assign the next two words to fullname and create a user object 
		//add the user object (username and fullname) to the map of all users
		//adds username to lsit of existing users to make sure there are no duplicates
		else if (command == "NAME:"){
			getline(userFile, firstLine);
			string fullName = firstLine.substr(1);
			cerr << "User's full name is " << fullName << endl;
			User *userObject = new User (username, fullName);
			allUsers -> add (username, userObject);
			existingUsers->add(username);
		}
		else if (command == "MOVIE:"){
			getline (userFile, firstLine);
			string rentedMovie;
			//if (firstLine.size() > 1){
			if (firstLine != " " && firstLine != ""){
				rentedMovie = firstLine.substr(1);
			}
			cerr << "User's rented movie is " << rentedMovie << endl;
			allUsers->get(username) -> stringMovie (rentedMovie);
		}
		//if line starts with END, you are moving on to another user 
		else if (command == "END"){
			cerr << "Moving on to next user" << endl;
		}
		else{//do nothing
		}
	}
	//closes user file
	userFile.close();		

	cerr << "Size of Map titles is: " << titles->size() << endl;

	cerr << "Size of Map allUsers is: " << allUsers -> size() << endl;	

	//change this to do at readin
	//adding rented movies to users
	//setting iterator to beginning of user list
	Map <string, User*>::Iterator allUsersIter = allUsers->begin();
	//create for loop of size all users
	for (int i = 0; i < allUsers->size(); i++){
		//setting up a comparison string 
		string rentedMovie;
		if (((*allUsersIter).second) -> getMovieString() != "no movie"){
			rentedMovie = ((*allUsersIter).second) -> getMovieString();
			//}
			//now shuffle through all of movie objects and assign movie object to that users rented movie if applicabale
			//titles iterator to shuffle through all movies
			Map <string, Movie*>::Iterator titlesIter2 = titles -> begin();
			for (int i = 0; i < titles->size(); i++){
				//if the string rented movie within private variable user = the title of any movies
				if (rentedMovie == ((*titlesIter2).second)->getTitle()){
					//then rent movie object that corresponds
					(*allUsersIter).second -> rentMovie((*titlesIter2).second);
				}
				//update iterators
				++titlesIter2;
			}
		}
		cout << "do i make it here" << endl;
		++allUsersIter;
	}
}

//Map <string, User*>::Iterator Netflix::login(string username){
void Netflix::login(string username){
	//set iterator to this 	
	//Map <string, User*>::Iterator loginIter = allUsers->begin();
	//copy paste and call iterator find
	//for find function return pointer as private variable 
	//cout << "made it here" << endl;
	loginIter = allUsers ->begin();
	for (int i =0; i < allUsers->size(); i++){
		if (username == (*loginIter).first){
			//find username and sit on it as iterator to log in
			//cout << "made it here" << endl;
			return;
		}
		else{
			++loginIter;
		}
	}	
	return;	
}

void Netflix::checker(){
	cout << "beginning of checker" << endl;
	cout << "logged in user is: " << (*loginIter).first << endl;
	cout << "end of checker" << endl;

	return;
}

void Netflix::movieSearch(string movieTitle){
	int titleSizeHolder = (int) movieTitle.size();
	//for (int i = 0; i < movieTitle.size(); i++){
	for (int i = 0 ; i < titleSizeHolder; i++){
		movieTitle [i] = tolower(movieTitle[i]);
	}

	cout <<  "Lower case movie title is: " << movieTitle << endl;

	//exception try catch so that program handles no movie elegantly
	try{
		cout << endl;
		movieHolder = titles->get(movieTitle);
		titles->get(movieTitle)->displayMovie(movieTitle);
		cout << endl;
	}
	catch(NoSuchElementException e){
		cout << "Movie doesn't exist!" << endl;
	}
}

void Netflix::addToQueue(){
	if (movieHolder != NULL){
		cout << endl;
		cout << "1. Add movie to queue" << endl;
		cout << "2. Back to User Menu" << endl;
		string userInput;
		cin >> userInput;

		if (userInput == "1"){
			//add movie to queue
			((*loginIter).second) -> movieQueue() -> enqueue (movieHolder);
		}
		else{
		}
	}	
}

void Netflix::keywordSearch(string keywordInput){
	int sizeHolder = (int) keywordInput.size();
	//for (int i = 0; i < keywordInput.size(); i++){
	for (int i =0; i< sizeHolder; i ++){
		keywordInput[i] = tolower(keywordInput[i]);
	}
	bool foundIt = true;
			//returns a movie object
	try{
		int movieSize = (movieKeywords->get (keywordInput))->size();				
		cout << "The number of movies matching this keyword are: ";
		cout << movieSize << endl;
		Set <Movie*>::Iterator keywordIter = (movieKeywords->get (keywordInput)) -> begin();
		cout << endl;
		cout << (*keywordIter) -> getTitle() << endl;
			
		//output the name of the first movie then output option to do next 
		
		if (movieSize !=0){
			//number of times to run for loop?
		//while (movieSize>0)	{
			bool checker = true;
			while (checker){					
					cout << endl;
					cout << "Click 1 to see the next movie that matches this keyword." << endl;
					cout << "Click 2 to Add movie to Queue." << endl;
							//}
					cout << "Click 3 to return to the menu." << endl;
					cout << endl;
					int input;
					cin >> input;	

					if(input == 1){
						movieSize--;
						try{	
							++keywordIter;
							cout << (*keywordIter) -> getTitle() << endl;
						}
						catch(NoSuchElementException e){
							cout << "No more movies matching this keyword!" << endl;
							cout << "Back to menu!" << endl;
							}
						}

					else if (input ==2){
						//input enqueue functionality for users queue  
						//adds current movie (keyword Iter) to the queue 
						((*loginIter).second) -> movieQueue() -> enqueue((*keywordIter));
					}
					else if (input ==3){
						checker = false;
					}
					else{
						cout << "Invalid input. Try again." << endl;
					}		
			}
		}
	}

	catch (NoSuchElementException e){
	//try searching in movies
		try{
			keywordInput[0] = toupper(keywordInput[0]);
			for (int i = 0; i < sizeHolder; i++){
				if (keywordInput[i] == ' '){
					keywordInput[i+1] = toupper(keywordInput[i+1]);
				}
			}
			Map <string, Movie*>::Iterator titlesIter1 = titles->begin();	
			for (int i = 0; i< titles->size(); i++){
				if (keywordInput == ((*titlesIter1).second)->getTitle()){
					cout << ((*titlesIter1).second)->getTitle() << endl;
					foundIt = false;
				}
				++titlesIter1;
			}
		}
		catch(NoSuchElementException e){
			if (!foundIt){}
			else{
				cout << "No matches. Sorry!" << endl;
			}
		}
	}
}

void Netflix::returnCurrentMovie(){
	cout << endl;
	cout << "current user is " << ((*loginIter).first) << endl;
	if (((*loginIter).second) -> currentMovie() != NULL){
		cout << "Current rented movie is " << ((*loginIter).second) -> currentMovie() -> getTitle() << endl;
		((*loginIter).second) -> returnMovie();
		cout << "movie returned" << endl;
		cout << endl;
	}
	else{
		cout << "No Movie checked out!" << endl;
		cout << endl;
	}
}

void Netflix::printQueueMenu(){
	cout << endl;
	if (!((*loginIter).second)-> movieQueue() -> isEmpty()){
		cout << "Top of queue is: ";	
		cout << ((*loginIter).second)-> movieQueue() -> peekfront() -> getTitle()<< endl; //display top of queue 
	}
	else{
		cout << "Queue is currently Empty!" << endl;
	}
	cout << endl;

	cout << "1. Order Movie" << endl;
	// will check out a movie if the user has no movie already checked out 
	//checking out movie removes it form top of queue 
	cout << "2. Remove Movie from Queue" << endl;
	//deletes top movie from queue and returns top movie in queue 
	cout << "3. Move Movie to back of Queue" << endl;
	//movie removed from front but immediately requeued at back --> back to queue menu 
	cout << "4. Return to User Menu" << endl; //boolean flag = false
	cout << endl;	
}

void Netflix::OrderMovie(){
	if (((*loginIter).second) -> currentMovie() != NULL){
		cout << "Sorry you already have a movie checked out" << endl;
		cout << "you're checked out movie is: " << ((*loginIter).second) -> currentMovie() -> getTitle() << endl;
		cout << "You can only order a movie once you've returned yours" << endl;
		cout << endl;
	}
	else{
		//check out movie from top of queue 
		((*loginIter).second) -> rentMovie(((*loginIter).second)-> movieQueue() -> peekfront());
		cout << "looks like you can check out a movie" << endl;
		//deletes movie from top of queue 
		((*loginIter).second)-> movieQueue()-> dequeue();
	}
}

void Netflix::RemoveFromQueue(){
	((*loginIter).second)-> movieQueue()-> dequeue();
}

void Netflix::MoveToBack(){
	((*loginIter).second)-> movieQueue() -> enqueue(((*loginIter).second)-> movieQueue() -> peekfront());
	((*loginIter).second)-> movieQueue()-> dequeue();
}

void Netflix::printMovieMenu(){
	cout << endl;
	if (((*loginIter).second)-> currentMovie() != NULL){
		cout << "Current Checked out movie is: " << ((*loginIter).second)-> currentMovie() -> getTitle () << endl;
	}
	else{
		cout << "No Movie checked out" << endl;
	}
	cout << endl; 

	cout << "Search Menu" << endl;
	cout << "1. Search for a movie by title" << endl;
	cout << "2. Search for a movie by keyword" << endl;
	cout << "3. Return the current movie" << endl;
	cout << "4. View Queue" << endl;
	cout << "5. Log Out" << endl;
	cout << endl;
	cout << "Enter a command to run this program:" << endl;	
}

//returns whether a user exists or not 
bool Netflix::checkUser(string username){
	bool checker = false;
	Set <string>::Iterator existingUsersIter = existingUsers->begin();
	for (int i =0; i < existingUsers->size(); i++){
		if (username == *existingUsersIter){
			//	cout << "This ID already exists! Back to main menu screen to choose another option!" << endl;
			checker = true;
			return checker;
		}
		//try catch loop to keep shuffling through elements 
		try{
			++existingUsersIter;
		}
		catch (NoSuchElementException e){
		}
	}	

	return checker;
}

void Netflix::createUser(string username, string fullname){
	//if you successfully entered a valid username then you are prompted to enter your fullname
	ofstream addUser;
	addUser.open (writeOutFile.c_str(), std::ios_base::app);
	addUser << endl << "BEGIN " << username << endl;

	//a new user object is created with your id and full name and this is added to the map of users
	User *userObject = new User (username, fullname);
	//add to the map of all users
	allUsers->add (username, userObject);
	//add to the set of all users (checks to see if user exists already)	
	existingUsers->add(username);	
	//reads in user fullname
	addUser << "NAME: " << fullname << endl << "END";
	addUser.close();	
	cout << "You've created your username. Now log in back at main menu!" << endl;		
}

void Netflix::writeOut(){
	ofstream myFile;
	//write it out to the correct file 
	myFile.open(writeOutFile.c_str());

	Map <string, User*>::Iterator allUsersIter = allUsers->begin();
	for (int i = 0; i < allUsers->size(); i++){
		myFile << "BEGIN " << (*allUsersIter).second->getID() << endl;
		myFile << "NAME: " << (*allUsersIter).second->getName() << endl;
		if ((*allUsersIter).second-> currentMovie() != NULL){
			myFile << "MOVIE: " << (*allUsersIter).second-> currentMovie()-> getTitle() << endl;
		}
		else{
			myFile << "MOVIE: " << endl;
		}
		myFile << "BEGIN QUEUE" << endl;
		while(!((*allUsersIter).second)->movieQueue()->isEmpty()){
			myFile << ((*allUsersIter).second)->movieQueue() -> peekfront() -> getTitle() << endl;
			((*allUsersIter).second)->movieQueue() -> dequeue();
		}
		myFile << "END QUEUE" << endl;
		myFile << "END" << endl;
		++allUsersIter;
	}

	myFile.close();	
}

void Netflix::memoryDeallocate(){
	Map <string, Movie*>::Iterator titlesIter = titles -> begin();
	for (int i = 0; i < titles->size(); i++){
		delete ((*titlesIter).second);
		try{
			++titlesIter;
		}
		catch(NoSuchElementException){} 
	}
	delete titles;
	cerr << "titles" << endl;

	Map <string, User*>::Iterator allUsersIter = allUsers ->begin();
	for (int i = 0; i < allUsers->size(); i++){
		//delete user object located at eachiterator then update iterator
		delete ((*allUsersIter).second);
		try{
			++allUsersIter;
		}
		catch(NoSuchElementException){} 
	}
	delete allUsers;
	cerr << "allUsers" << endl;

	//run nested for loop and delete sets of movies
	Map<string, Set<Movie*>*>::Iterator movieKeywordsIter = movieKeywords -> begin();
	for (int i = 0; i < movieKeywords->size(); i++){
		try{
			delete ((*movieKeywordsIter).second);
			++movieKeywordsIter;
		}
		catch (NoSuchElementException e){}
	}
	delete movieKeywords;
	cerr << "moviekeywords" << endl;

	//dont need to change these 
	delete setOfMovies;
	cerr << "setofMovies" << endl;	

	delete existingUsers;
	cerr << "existingUsers" << endl;		
}