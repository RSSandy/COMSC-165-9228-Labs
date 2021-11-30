/*********************************************************************
* Name: Sandhya Nayar
* Lab 8: Artificial Intelligence with Innate Knowledge
* Editor(s) used: replit
* Compiler(s) used: replit
**********************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::ios;
using std::fixed;
using std::endl;


#include <string>
using std::string;

#include <cstring>
using std::strcpy;

#include <cctype>
using std::tolower;

#include <fstream>
using std::ofstream;
using std::ifstream;

//structs 
struct Thing{
    string sayThis;
    Thing *yes;
    Thing *no;
};


// Declaring function prototypes.
void print_id(string lab_desc);
bool inputValid(string &buffer);
void fileOutput(ofstream &fout, Thing *p);
void deallocate(Thing *p);
Thing *serializeUp(ifstream& fin);

//tree layout

/*
                                                              is it a concrete noun?
                           /                                                                                 \
                          yes                                                                                 no
                         /                                                                                      \
                       is it alive?                                                                              is it a feeling?
               /                         \                                                          /                                         \
              yes                         no                                                       yes                                         no
             /                              \                                                     /                                              \
    does it live on land?                    is it in the sky?                                is it a good feeling?                                 can it be a characteristic?
          /      \                         /                   \                                /                 \                                /                       \
        yes       no                      yes                   no                             yes                 no                             yes                       no 
       /            \                    /                        \                           /                     \                            /                            \
    can it fly?   can it swim?  does it fall down to earth?    can you climb it?       is it for another person?     associated w red?       good to be/have?           can it be an action?        
    /     \         /    \             /    \                   /       \                 /       \                   /     \                   /     \                     /        \
  yes     no       yes    no         yes     no                yes       no              yes       no               yes      no                yes     no                  yes        no
  /         \     /        \         /        \               /            \            /           \               /         \               /         \                 /             \
pidgeon    bear salmon   seaweed  rain      cloud          mountain       lake        love          joy            anger   loneliness      charity   insomnia          movement        future
*/


int main() {
  print_id("Lab 8: Artificial Intelligence with Innate Knowledge");

  //get nodes from file
  Thing *top;
  ifstream fin;
  fin.open("ai.txt");
  if (fin.good())
  {  
    // create a node and fill with line from file, and attach all descendent nodes
    top = serializeUp(fin);
    fin.close();
  }
  else
  {
    top = new Thing;
    top->sayThis = "It's a bunny";
    top->yes = top->no = 0;
  }


  //user explanation
  cout << "Answer my questions and I'll guess what noun you're thinking about." << endl;

  //loop through tree
  Thing *temp = top;
  string buffer;
  string answer;
  while(true){
      if(temp->yes == 0 && temp->no == 0){
          answer = temp->sayThis;
          break;
      }
      
      //input validation loop
      while(true){
        cout << temp->sayThis ;
        cout << " [y / n] ";
        getline(cin, buffer); 
        if(inputValid(buffer)) break;
        else cout << "please enter [y / n]" << endl;
      }

      if(buffer == "y") temp = temp->yes;
      else if(buffer == "n") temp = temp->no;
  }
  cout << "I have my guess!" << endl;
  cout << answer << endl;

  //file output
  ofstream fout;
  fout.open("ai.txt");
  fileOutput(fout, top);
  fout.close();
  top = nullptr;

  
  // Deallocate all nodes
  deallocate(top);

  return 0;
}//main

/*********************************************************************
*Function: checks if user input is 'y' or 'n', converts to lowercase
*Parameters: 
  *string buffer: user input into a string variable
*Return: returns whether or not buffer is valid input [BOOL]
*********************************************************************/
bool inputValid(string &buffer){
    if(buffer.length() != 1) return false;
    else{
        //convert to lowercase
        buffer[0] = tolower(buffer[0]);
        if(buffer == "y" || buffer == "n") return true;
        else return false;
    }   
}//inputValid

/*********************************************************************
*Function: iterates through tree and outputs content into file
*Parameters: 
  *ofstream &fout: edit file within function
  *Thing *p: pointer to top of binary tree
*Return: NONE
*********************************************************************/
void fileOutput(ofstream &fout, Thing *p){
    if(p == nullptr) fout << "EOF" << endl;
    else {
        fout << p->sayThis << endl;
        fileOutput(fout, p->yes);
        fileOutput(fout, p->no);
    } 
}//outputFile

/*********************************************************************
*Function: takes input from file and puts it into tree
*Parameters: 
  *ifstream &fin: open and read from file within function
*Return: pointer to top of binary tree
*********************************************************************/
Thing *serializeUp(ifstream& fin){
  string buf;
  getline(fin, buf);
  if (buf == "EOF") return nullptr;
  Thing* p = new Thing;
  p->sayThis = buf;
  p->yes = serializeUp(fin);
  p->no = serializeUp(fin);
  return p;
}///serializeUp

/*********************************************************************
*Function: deallocates nodes of binary tree
*Parameters: 
  *Thing *temp: pointer to top of binary tree
*Return: NONE
*********************************************************************/
void deallocate(Thing *temp){
  if (temp == 0) return;
  deallocate(temp->yes);
  deallocate(temp->no);
  delete temp;
}//deallocate

void print_id(string lab_desc) {
  cout << "Sandhya Nayar\n";
  cout << lab_desc + "\n";
  cout << "Editor(s) used: replit\n";
  cout << "Compiler(s) used: replit\n";
  cout << "File: " << __FILE__ << "\n";
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}
