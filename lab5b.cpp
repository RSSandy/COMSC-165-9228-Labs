/*********************************************************************
* Name: Sandhya Nayar
* Lab 5b: Track Expenses Using Dynamic Arrays
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

//Progammer-defined data-types
struct Expense{
  double amt;
  char dsc[100];
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
bool findInString(char buffer[], char dsc[], int searchLength, int descLength);
int numberOfCharsInArray(char *array);
void doubleArrayCapacity(Expense **array, int *capacity);



int main() {
  print_id("Lab 5b: Track Expenses Using Dynamic Arrays");

  //introduction
  cout << "Welcome to your expense tracker" << endl;

  //DATA
  int choice = 0; //user menu choice
  bool quit = false; //used to break the menu loop
  int capacity = 2;//capacity of array
  Expense *expenseList = new Expense[capacity]; //array of struct Expense with all expenses
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
        if(counter == capacity) doubleArrayCapacity(&expenseList, &capacity);
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
*Function: displays all menu options, prompts user for choice and returns it
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
      if(expenseList[i].amt != 0){
        string buff;
        int descLength = numberOfCharsInArray(expenseList[i].dsc);
        cout << "AMOUNT: (" << expenseList[i].amt << ")     DESCRIPTION: (";
        for(int j = 0; j < descLength; j++){
          cout << expenseList[i].dsc[j];
        }
        cout << ")" << endl;
      }
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
  strcpy(temp.dsc, buffer.c_str());

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
  string buffer;

  //prompts user for search ubstring, breaks if input is valid
  while(true){
    cout << "Please enter the search string: ";
    getline(cin,buffer);
    if(checkInputDescription(buffer) == true) break;
  }

  //change buffer into char array
  int searchLength = buffer.length();
  char search[searchLength];
  strcpy(search, buffer.c_str());

  //search
  Expense *resultList = new Expense[counter];
  int resultCounter = 0;
  bool resultFound = false;

  //cycles through expenseList, adds element to resultList if resultFound is true
  for(int i = 0; i < counter; i++){
    int descLength = numberOfCharsInArray(expenseList[i].dsc);
    resultFound = findInString(search, expenseList[i].dsc, searchLength, descLength);
    if(resultFound == true) resultList[resultCounter++] = expenseList[i];
  }//loop through expense list descriptions

  if(resultCounter > 0) showAll(resultList, resultCounter);
  else cout << "There are no expenses with that description" << endl;

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
  int check = stoi(buffer);
  char checkArray[buffer.length() + 1];
  strcpy(checkArray, buffer.c_str());

  //checks if every digit of input amount is an integer or a decimal 
  for(int i = 0; i < buffer.length(); i++){
    if(checkArray[i] != '1' && checkArray[i] != '2' && checkArray[i] != '3' && checkArray[i] != '4' && checkArray[i] != '5' && checkArray[i] != '6' && checkArray[i] != '7' && checkArray[i] != '8' && checkArray[i] != '9' && checkArray[i] != '.' && checkArray[i] != '0') isValid = false;
  }
  if(check <= 0) isValid = false;
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
bool findInString(char search[], char desc[], int searchLength, int descLength){
  bool resultFound; //return true if search substring is found within desc

  //cycle through each element of search and make it lowercase
  for(int i = 0; i < searchLength; i++){
    char c = search[i];
    search[i] = (tolower(c));
  }

  //cycle through each element of check and make it lowercase
  for(int i = 0; i < descLength; i++){
    char c = desc[i];
    desc[i] = (tolower(c));
  }

  //loop through arrays to look for starting pt of find
  for(int i = 0; i < descLength; i++){
    if(desc[i] == search[0]){
      
      /*loop through each element of check starting from the starting pt of search
      to see if all letters match up*/
      for(int j = 0; j < searchLength; j++){
        if(desc[i + j] == search[j]) resultFound = true;
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

/*********************************************************************
*Function: finds the number of chars in a char array
*Parameters: 
*  char array (IN): the array that gets checked
*Return: int numberOfChars: the number of chars in the char array
*********************************************************************/
int numberOfCharsInArray(char* array){
  int numberOfChars = 0;

  //loop to go through array and count whenever theres a char there
  while (*array++){
    numberOfChars++;
  }
  return numberOfChars;
}//numberOfCharsInArray

/*********************************************************************
*Function: doubles capacity of an array
*Parameters: 
*  Expense expenseList (IN): array that gets doubled by the function
*  int capacity (IN): capacity of first array that gets changed 
*Return: Expense expenseList with doubled array capacity 
*********************************************************************/
void doubleArrayCapacity(Expense **array, int *capacity){
  Expense *temp = new Expense[2 * *capacity]; 
  for(int i = 0; i < *capacity; i++) 
    temp[i] = (*array)[i]; 
  delete [] *array; 
  *array = temp; 
  *capacity *= 2; 
}//doubleArrayCapacity

void print_id(string lab_desc) {
  cout << "Sandhya Nayar\n";
  cout << lab_desc + "\n";
  cout << "Editor(s) used: replit\n";
  cout << "Compiler(s) used: replit\n";
  cout << "File: " << __FILE__ << "\n";
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}//print_id
