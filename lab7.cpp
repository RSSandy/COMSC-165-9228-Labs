/*********************************************************************
* Name: Sandhya Nayar
* Lab 7: Queue Data Structure
* Editor(s) used: replit
* Compiler(s) used: replit
**********************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::ios;
using std::fixed;
using std::endl;
using std::swap;
using std::atoi;
using std::left;
using std::right;

#include <fstream>
using std::ifstream;
using std::ofstream;


#include <string>
using std::string;

//data types
struct Movie{
  string name;
  int year;
  int rating;
  Movie *next;
};

//this is a queue struct
struct Queue{
    Movie *front;
    Movie *rear;

    Queue(){
        front = rear = NULL;
    }
};

// Declaring function prototypes.
void fileInput(Queue &q, int &nMovies);
void fileOutput(Queue q, int nMovies);
char chooseMenu();
bool menuValid(string input);
void addMovie(Queue &q, int &nMovies);
bool integerValid(string buffer, int min, int max);
bool movieNameInput(string buffer);
void updateMovie(Queue q, int nMovies);
void deleteMovie(Queue &q, int &nMovies);
void listMovies(Queue q, int nMovies);
void sortTitle(Queue q);
void sortYear(Queue q);
void sortRating(Queue q);
void print_id(string lab_desc);
void showData(Queue q, int nMovies);



int main(){
  print_id("Lab 7: Queue Data Structure");

  //DATA
  Queue q; //declares a queue
  int nMovies = 0; //tracks number of movies
  bool quit = false;

  //get file input
  fileInput(q,nMovies);

  //menu
  while(true){
    char choice = chooseMenu();
    switch(choice){
      case 'A': 
        addMovie(q, nMovies); 
        break;
      case 'U':
        updateMovie(q, nMovies); 
        break;
      case 'D':
        deleteMovie(q, nMovies); 
        break;
      case 'L':
        listMovies(q, nMovies);
        break;
      case 'T':
        sortTitle(q);
        break;
      case 'Y':
        sortYear(q);
        break;
      case 'R':
        sortRating(q);
        break;
      case 'Q':
        quit = true;
        break;
    }
    if(quit == true) break;
  }

  //output movie data to file
  fileOutput(q,nMovies);

  //deallocate all nodes
  for(int i = 0; i < nMovies; i++){
      Movie *p = q.front;
      q.front = q.front->next;
      delete p;
  }

  return 0;
}

/*********************************************************************
*Function: takes input from file and puts it into queue
*Parameters: NONE
*Return: NONE
*********************************************************************/
void fileInput(Queue &q, int &nMovies){
  //open input file
  ifstream fin;
  fin.open("movies.txt");

  //get input from file
  while (fin.good()){

    //check if end of file
    string buf;
    getline(fin,buf); 
    if(buf == "EOF") break; 

    //if not end of file, get data
    else{
      //make new movie
      Movie* temp = new Movie; 
      temp->next = nullptr;

      //add data
      temp->name = buf; 
      fin >> temp->year; 
      fin >> temp->rating;
      fin.ignore(1000,10); 

      //add to list
      if (!q.front) q.front = temp;
      if (q.rear) q.rear->next = temp;
      q.rear = temp;
      nMovies++;
    }//else
  }//file loop
  fin.close();
}//fileInput

/*********************************************************************
*Function: outputs queue into output file 
*Parameters: NONE
*Return: NONE
*********************************************************************/
void fileOutput(Queue q, int nMovies){
  //open output file
  ofstream outputFile("movies.txt");

  //loop to output movies
  if(outputFile.good()){ 
    Movie *p =  q.front;

    //iterate through movies list and output to file
    for(int i = 0; i < nMovies; i++){
      outputFile << p->name << endl;
      outputFile << p->year << endl;
      outputFile << p->rating << endl;
      p = p->next;
    }
    outputFile << "EOF" << endl;
  }
  outputFile.close();
}//fileOutput

/*********************************************************************
*Function: displays all menu options, prompts user for choice and returns choice
*Parameters: none
*Return: returns user's choice for menu options (CHAR)
*********************************************************************/
char chooseMenu(){
  cout << endl;
  string input;

  //prompt user for choice from menu options
  while (true){
    cout << "MENU" << endl;
    cout << "A: Add a movie" << endl;
    cout << "U: Update a movie" << endl;
    cout << "D: Delete a movie" << endl;
    cout << "L: List all movies" << endl;
    cout << "T: Sort by Title" << endl;
    cout << "Y: Sort by most recent Year viewed" << endl;
    cout << "R: Sort by Rating" << endl;
    cout << "Q: Quit" << endl;
    cout << "Your choice: " ;
    cin >> input;
    cin.ignore(1000,10);
    if(menuValid(input) == true) break; //check if input valid
    else cout << "Invalid input: must be one of the specified characters (ex: A, T)" << endl;
  }
  cout << endl;

  char choice = toupper(input[0]);
  return choice;
}//chooseMenu

/*********************************************************************
*Function: checks if user input for menu choice is valid 
*Parameters: 
*  string input (IN): user input for menu choice
*Return: returns bool for whether user input is valid (BOOL)
*********************************************************************/
bool menuValid(string input){
  if(input.length() > 1) return false;
  else{
    char check = toupper(input[0]); //check if valid letter
    if(check != 'A' && check != 'U' && check!= 'D' && check!= 'L' && check != 'T' && check!= 'Y' && check!= 'R' && check != 'R' && check!= 'Q') return false;
    else return true;
  }
}//menuValid

/*********************************************************************
*Function: prompts user to enter movie data, adds movie to linked list
*Parameters: 
*   Movie *start (INOUT): pointer to start of linked list
*   int nMovies (INOUT): tracker for number of movies in list
*Return: NONE
*********************************************************************/
void addMovie(Queue &q, int &nMovies){
  Movie* aMovie = new Movie();
  nMovies++;


  //movie name
  string buffer;
  while(true){ //input validation loop for movie name 
    cout << "Enter a movie name: " ;
    getline(cin, buffer);
    if(movieNameInput(buffer)) break;
    else cout << "Please enter a movie name" << endl;
  }
  aMovie->name = buffer;
  cout << endl;

  //movie year
  string temp;
  while(true){ //input validation loop for movie year 
    cout << "Enter the year you watched " << aMovie->name << " : " ;
    getline(cin,temp);
    if(integerValid(temp, 0, 2022)) break;
    else cout << "Please enter a valid year" << endl;
  }
  aMovie->year = atoi(temp.c_str());
  cout << endl;

  //movie rating
  string buf;
  while(true){ //input validation loop for movie rating
    cout << "Enter your rating for " << aMovie->name << "[1-5] : " ;
    getline(cin, buf);
    if(integerValid(buf, 1, 5)) break;
    else cout << "Please enter a number in between 1-5" << endl;
  }
  aMovie->rating = atoi(buf.c_str());
  cout << endl;


  //add node to queue
  if(q.rear == NULL) q.front = q.rear = aMovie;
  q.rear -> next = aMovie; //TO-DO: literally what does this do
  q.rear = aMovie;

}//addMovie

/*********************************************************************
*Function: checks if a given number in a string variable is an int between the min and max
*Parameters:
*  string buffer (IN): user input stored in string variable
*  int min(IN): minimum for user input
*  int max(IN): maximum for user input
*Return: returns whether user input is valid (BOOL)
*********************************************************************/
bool integerValid(string buffer, int min, int max){
  
  //check if all values are numbers
  bool isNumber = true;
  for(int i = 0; i < buffer.length(); i++){
    if(buffer[i] != '1' && buffer[i] != '2' && buffer[i] != '3' && buffer[i] != '4' && buffer[i] != '5' && buffer[i] != '6' && buffer[i] != '7' && buffer[i] != '8' && buffer[i] != '9' && buffer[i] != '0') isNumber = false;
  }
  if(isNumber == false) return false;

  //check if integer is between min and max
  else{
    int input = atoi(buffer.c_str());
    if(input > max || input < min) return false;
    else return true;
  }
}//integerValid

/*********************************************************************
*Function: checks if user movie name input isn't an empty sting
*Parameters:
*  string buffer (IN): user input stored in string variable
*Return: returns whether user input is valid (BOOL)
*********************************************************************/
bool movieNameInput(string buffer){
  if(buffer.length() == 0) return false;
  else return true;
}//movieNameInput

/*********************************************************************
*Function: gets movie of user's choice, updates movie info
*Parameters:
*   Movie *start (INOUT): pointer to start of linked list
*   int nMovies (IN): tracker for number of movies in list
*Return: NONE
*********************************************************************/
void updateMovie(Queue q, int nMovies){
  if(nMovies == 0) cout << "You don't have any movies to update." << endl;
  else{
    //choose movie to update 
    int index = 0;
    string buf;
    while(true){ //input validation loop for movie index choice
      cout << "What movie do you want to update? Choose an index from 1-" << nMovies << " : " << endl;
      getline(cin,buf);
      if(integerValid(buf,1,nMovies)) break;
      else cout << "Please choose an index from 1-" << nMovies << ": ";
    }
    index = atoi(buf.c_str());

    //find node
    Movie *ptr = q.front;
    int i = 1;
    while(true){
      if(i == index) break;
      else{
        ptr = ptr->next;
        i++;
      }
    }

    //output movie to change
    cout << "You are changing " << ptr->name << "." << endl;

    //choose what to update
    int choice = 0;
    string temp;
    while(true){ //input validation loop for what movie info to change
      cout << "What do you want to change?\n 1: Movie name\n 2: Year you watched movie\n 3: Movie's rating " << endl;
      getline(cin, temp);
      if(integerValid(temp,1,3)) break;
      else cout << "Please choose a number between 1 and 3." << endl;
    }
    choice = atoi(temp.c_str());

    //update movie data
    switch(choice){
      case 1: { //change movie title
        string newTitle;
        while(true){
          cout << "Enter new movie name for Movie #" << index << " : " << endl;
          getline(cin, newTitle);
          if(movieNameInput(newTitle)) break;
          else cout << "Please enter a movie name" << endl;
        }
        ptr->name = newTitle;
        break;
      }
      case 2: { //change movie year
        string newYear;
        while(true){
          cout << "Enter new year for " << ptr->name << ": " << endl;
          getline(cin,newYear);
          if(integerValid(newYear,0,2022)) break;
          else cout << "Please enter a valid year" << endl; 
        }
        ptr->year = atoi(newYear.c_str());
        break;
      }
      case 3: { //change movie rating 
        string newRating;
        while(true){
          cout << "Enter new movie rating for " << ptr->name << ": " << endl; 
          getline(cin, newRating);
          if(integerValid(newRating,1,5)) break;
          else cout << "Please enter a number in between 1-5" << endl;
        }
        ptr->rating = atoi(newRating.c_str());
        break;
      }
      default: {
        cout << "input error" << endl;
        break;
      }
    }
  }//else 
}//updateMovie

/*********************************************************************
*Function: gets movie of user's choice, deletes movie 
*Parameters:
*   Movie *start (INOUT): pointer to start of linked list
*   int nMovies (INOUT): tracker for number of movies in list
*Return: NONE
*********************************************************************/
void deleteMovie(Queue &q, int &nMovies){

  //check # of movies
  if(nMovies == 0) cout << "You have no movies to delete." << endl;
  else{
    //choose movie to update 
    int index = 0;
    string buf;
    while(true){
      cout << "What movie do you want to delete? Choose an index from 1-" << nMovies << " : " << endl;
      getline(cin,buf);
      if(integerValid(buf,1,nMovies)) break;
      else cout << "Please choose an index from 1-" << nMovies << ": ";
    }
    index = atoi(buf.c_str());

    //find node
    Movie *prev;
    Movie *ptr = q.front;
    int i = 1;
    while(true){
      if(i == index) break;
      else{
        prev = ptr;
        ptr = ptr->next;
        i++;
      }
    }

    //output movie to change
    cout << "You deleted " << ptr->name << "." << endl;

    //delete node
    if(nMovies == 1){
      q.rear = NULL;
      q.front =  NULL;
    }
    else if(ptr == q.rear) q.rear = prev;
    else if(ptr == q.front) q.front = ptr->next;
    else prev->next = ptr->next;
    delete ptr; 
    nMovies--;
  }
}//deleteMovie

/*********************************************************************
*Function: outputs entire linked list of movies 
*Parameters:
*   Movie *start (IN): pointer to start of linked list
*Return: NONE
*********************************************************************/
void listMovies(Queue q, int nMovies){ 
  if(nMovies == 0) cout << "You have no movies to output" << endl;
  else{
    //start listing 
    cout << "#  Title                  Viewed Rating" << endl; 
    cout << "-- ---------------------- ------ ------" << endl;

    //iterate through linked list
    Movie *ptr = q.front;
    int index = 1;
    while(ptr!= nullptr){ //output data while iterating 
      cout.width(4); cout << left << index;
      cout.width(23); cout << left << ptr->name;
      cout.width(7); cout << left << ptr->year;
      cout.width(10); cout << left << ptr->rating << endl;
      ptr = ptr->next;
      cout << endl;
      if(index == nMovies) break;
      index++;
    }
  }//else
}//listMovies

/*********************************************************************
*Function: sorts linked list based on titles alphabetically 
*Parameters:
*   Movie *start (IN): pointer to start of linked list
*Return: NONE
*********************************************************************/
void sortTitle(Queue q){
  for (Movie *p = q.front; p; p = p->next) //iterate through list
    for (Movie *q = p->next; q; q = q->next) //take node directly after p
      if (q->name < p->name){
      swap(*p, *q);
      swap(p->next, q->next);
    }
}//sortTitle

/*********************************************************************
*Function: sorts linked list based on year from most to least recent
*Parameters:
*   Movie *start (IN): pointer to start of linked list
*Return: NONE
*********************************************************************/
void sortYear(Queue q){
  for (Movie *p = q.front; p; p = p->next) //iterate through list
    for (Movie* q = p->next; q; q = q->next) //take node directly after p
      if (q->year > p->year){
      swap(*p, *q);
      swap(p->next, q->next);
    }
}//sortYear

/*********************************************************************
*Function: sorts linked list based on rating from highest to lowest
*Parameters:
*   Movie *start (IN): pointer to start of linked list
*Return: NONE
*********************************************************************/
void sortRating(Queue q){
  for (Movie *p = q.front; p; p = p->next) //iterate through list
    for (Movie* q = p->next; q; q = q->next) //take node directly after p
      if (q->rating > p->rating){
      swap(*p, *q);
      swap(p->next, q->next);
    }
}//sortRating

void print_id(string lab_desc) {
  cout << "Sandhya Nayar\n";
  cout << lab_desc + "\n";
  cout << "Editor(s) used: replit\n";
  cout << "Compiler(s) used: replit\n";
  cout << "File: " << __FILE__ << "\n";
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}//print_id
