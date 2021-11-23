/*********************************************************************
* Name: Sandhya Nayar
* Lab 5: Track Expenses Using Array
* Editor(s) used: replit
* Compiler(s) used: replit
**********************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::ios;
using std::fixed;
using std::endl;

#include <iomanip>
using std::setprecision;

#include <string>
using std::string;

#include <cstring>
#include <cctype>

//Progammer-defined data-types
struct Expense{
  double amt;
  string dsc;
};

// Declaring function prototypes
void print_id(string lab_desc);
int openMenu();
void showAll(Expense expenseList[], int counter);
Expense spend();
void searchString(Expense expenseList[], int counter);
void searchAmount(Expense expenseList[], int counter);
bool checkInputAmount(string buffer);
bool checkInputDescription(string buffer);
bool findInString(string buffer, string dsc);


int main() {
  print_id("Lab 5: Track Expenses Using Array");

  //introduction
  cout << "Welcome to your expense tracker" << endl;

  //DATA
  int choice = 0; //user meny choice
  bool quit = false; //used to break the menu loop
  Expense *expenseList = new Expense[100]; //array of struct Expense with all expenses
  int counter = 0; //counts the number of structs in expenseList

  
  //loop that allows user to go through the different choices of menu 
  while(true){
    choice = openMenu();
    switch(choice){
      case 1:
        cout << "Expenses: " << endl;
        showAll(expenseList,counter);
      break;
      case 2: 
        expenseList[counter++] = spend();
      break;
      case 3:
        searchString(expenseList,counter);
      break;
      case 4:
        searchAmount(expenseList,counter);
      break;
      case 5:
        quit = true;
      break;
      default:
      cout << "error" << endl;
      break; 
    }
    if(quit == true) break;
  }//end of menu loop

  return 0;
}//end of main

/*********************************************************************
*Function: displays all menu options, promtps user for choice and returns it
*Parameters: none
*Return: returns user's choice for menu options (INT)
*********************************************************************/
int openMenu(){
  int rv = 0;
  string buffer;

  //loop shows all menu options, breaks if user input is valid
  while(true){
    cout << endl;
    cout << "Menu: " << endl;
    cout << "1. Show all " << endl;
    cout << "2. Spend " << endl;
    cout << "3. Search expenses containing this string" << endl;
    cout << "4. Search expenses with greater than or equal to this amount" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your option: ";
    cin >> buffer; 
    if(buffer != "1" && buffer != "2" && buffer != "3" && buffer != "4" && buffer != "5") cout << "Invalid input, must choose a number between 1-5 from the menu. Try again." << endl;
    else break; 
  }//end of menu options loop

  rv = atoi(buffer.c_str());
  cin.ignore(1000,10);
  cout  << endl;

  return rv;
}//openMenu


/*********************************************************************
*Function: displays all elements of Expense expenseList[] array
*Parameters: 
*  Expense expenseList (IN): list of all user-inputted expenses
*  int counter (IN): number of elements inside expenseList[]
*Return: none
*********************************************************************/
void showAll(Expense expenseList[], int counter){
  if(counter == 0) cout << "There is no expense entry available." << endl;
  else{ //if size of expenseList is greater than 0, show all elements
    cout.setf(ios::fixed|ios::showpoint);
    cout <<setprecision(2); //set the number of digits after the decimal to 2

    //loop cycles through all elements in expenseList and outputs amount and description of each
    for (int i = 0; i < counter; i++){
      if(expenseList[i].amt != 0)
      cout << "AMOUNT: (" << expenseList[i].amt << ")     DESCRIPTION: (" << expenseList[i].dsc << ")" << endl;
    } 
  }
}//showAll 

/*********************************************************************
*Function: allows user to input attributes of a single Expense 
object, returns object
with filled-in attributes
*Parameters: none
*Return: Expense object with filled-in attributes
*********************************************************************/
Expense spend(){
  Expense temp;
  string buffer;
  cout << endl;

  //prompts user for expense description, breaks if input is valid
  while(true){
    cout << "Please enter the description for the expense: ";
    getline(cin, buffer);
    if(checkInputDescription(buffer) == true) break;
  }
  temp.dsc = buffer;

  //prompts user for expense amount, breaks if input is valid
  while(true){
    cout << "Please enter the amount:";
    cin >> buffer;
    if(checkInputAmount(buffer) == true) break;
    cin.ignore(1000,10);
  }
  temp.amt = atof(buffer.c_str()); 

  return temp;
}//spend

/*********************************************************************
*Function: takes user substring and looks through all elements 
in expenseList to check if there is an element with a description 
that has the substring
*Parameters: 
*  Expense expenseList (IN): list of all user-inputted expenses
*  int counter (IN): number of elements inside expenseList[]
*Return: none
*********************************************************************/
void searchString(Expense expenseList[], int counter){
  Expense empty = Expense{0, "empty"};
  string buffer;

  //prompts user for search ubstring, breaks if input is valid
  while(true){
    cout << "Please enter the search string: ";
    getline(cin,buffer);
    if(checkInputDescription(buffer) == true) break;
  }

  //search
  Expense *resultList = new Expense[counter];
  int resultCounter = 0;
  bool resultFound = false;

  //cycles through expenseList, adds element to resultList if resultFound is true
  for(int i = 0; i < counter; i++){
    resultFound = findInString(buffer, expenseList[i].dsc);
    if(resultFound == true) resultList[resultCounter++] = expenseList[i];
  }//loop through expense list descriptions

  if(resultCounter > 0) showAll(resultList, resultCounter);
  else cout << "There are no expenses with that description" << endl;

  //clear results array
  for(int i = 0; i < resultCounter; i++){
    resultList[i] = empty;
  }
}//searchString

/*********************************************************************
*Function: takes user's number and looks through all elements in 
expenseList to check if there is an element with an amount greater 
than or equal to the number
*Parameters: 
*  Expense expenseList (IN): list of all user-inputted expenses
*  int counter (IN): number of elements inside expenseList[]
*Return: none
*********************************************************************/
void searchAmount(Expense expenseList[], int counter){
  string buffer;
  int search;
  int results = 0;
  Expense *searchResult = new Expense[counter];

  //prompts user for search amount, breaks if input is valid
  while(true){
    cout << "Please enter the amount: ";
    cin >> buffer;
    if(checkInputAmount(buffer) == true) break;
  }
  search = atoi(buffer.c_str());

  //cycles through expenseList, adds element to resultList if amount is greater than or equal to search amount
  for(int i = 0; i < counter; i++){
    if(expenseList[i].amt >= search) searchResult[results++] = expenseList[i];
  }

  showAll(searchResult, results);

}//searchAmount

/*********************************************************************
*Function: checks if user's input is a positive number above 0 and 
returns true or false
*Parameters: 
*  string buffer(IN): user's input
*Return: bool isValid: whether or not the user input met the 
requirements
*********************************************************************/
bool checkInputAmount(string buffer){
  bool isValid = true;
  char checkArray[buffer.length() + 1];
  strcpy(checkArray, buffer.c_str());

  //checks if every digit of input amount is an integer or a decimal 
  for(int i = 0; i < buffer.length(); i++){
    if(checkArray[i] != '1' && checkArray[i] != '2' && checkArray[i] != '3' && checkArray[i] != '4' && checkArray[i] != '5' && checkArray[i] != '6' && checkArray[i] != '7' && checkArray[i] != '8' && checkArray[i] != '9' && checkArray[i] != '.') isValid = false;
  }
  if(isValid == false) cout << "Invalid input: must be positive number above 0" << endl;
  return isValid;
}//checkInputAmount

/*********************************************************************
*Function: checks if user's input string is empty, returns false if so
*Parameters: 
*  string buffer(IN): user's input
*Return: bool : whether or not hte user input met the requirements
*********************************************************************/
bool checkInputDescription(string buffer){
  if(buffer.length() != 0) return true;
  else{
    cout << "Must include string" << endl;
    return false;
  }
}//checkInputDescription

/*********************************************************************
*Function: checks if one substring is inside another string 
*Parameters: 
*  string search(IN): user's substring converted into a string variable
*  string desc(IN): description attribute of an element converted into
a string variable
*Return: bool resultFound: whether or not the substring is within
the other string variable
*********************************************************************/
bool findInString(string search, string desc){
  bool resultFound; //return true if search substring is found within desc

  //make search into a char array
  int searchLength = search.length();
  char tempFind[searchLength];
  strcpy(tempFind,search.c_str());
  char find[searchLength];

  //cycle through each element of find and make it lowercase
  for(int i = 0; i < searchLength; i++){
    char c = tempFind[i];
    find[i] = (tolower(c));
    cout << find[i];
  }
  cout << endl;

  //make desc into a char array
  int descLength = desc.length();
  char tempCheck[descLength];
  char check[descLength];
  strcpy(tempCheck, desc.c_str());

  //cycle through each element of check and make it lowercase
  for(int i = 0; i < descLength; i++){
    char c = tempCheck[i];
    check[i] = (tolower(c));
    cout << check[i];
  }
  cout << endl;

  //loop through arrays to look for starting pt of find
  for(int i = 0; i < descLength; i++){
    if(check[i] == find[0]){
      
      /*loop through each element of check starting from the starting pt of search
      to see if all letters match up*/
      for(int j = 0; j < searchLength; j++){
        if(check[i + j] == find[j]) resultFound = true;
        else {
          resultFound = false;
          break;
        }
      }
      if(resultFound == true) break;
    }
    else {
      resultFound = false;
    }
  }

  return resultFound;
}//findInString

void print_id(string lab_desc) {
  cout << "Sandhya Nayar\n";
  cout << lab_desc + "\n";
  cout << "Editor(s) used: replit\n";
  cout << "Compiler(s) used: replit\n";
  cout << "File: " << __FILE__ << "\n";
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}//print_id
