/*********************************************************************
* Name: Sandhya Nayar
* Lab 1: Console Programming Basics
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


// Declaring function prototypes.
void print_id(string lab_desc);



int main() {
  print_id("Lab 1: Console Programming Basics");

  //DATA
  

  return 0;
}



void print_id(string lab_desc) {
  cout << "Sandhya Nayar\n";
  cout << lab_desc + "\n";
  cout << "Editor(s) used: replit\n";
  cout << "Compiler(s) used: replit\n";
  cout << "File: " << __FILE__ << "\n";
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << "\n\n";
}
