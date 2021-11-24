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

//structs 
struct Thing{
    string sayThis;
    Thing *yes;
    Thing *no;
};


// Declaring function prototypes.
void print_id(string lab_desc);

//tree layout
/*
                                     is it a concrete noun?
                        /                                                                              \
                     yes                                                                                no
                    /                                                                                    \
                    is it alive?                                                                                is it a feeling?
               /                         \                                                          /                                         \
              yes                         no                                                       yes                                         no
             /                              \                                                     /                                              \
does it live on land?                      is it in the sky?                                is it a good feeling?                                 can it be a characteristic?
          /      \                        /                   \                                /                 \                                /                   \
        yes      no                      yes                   no                             yes                 no                             yes                  no 
       /           \                    /                        \                           /                      \                           /                       \
    can it fly?   can it swim?  does it fall down to earth?    can you climb it?       is it for another person?     associated w red?       good to be/have?         can it be an action?        
    /      \       /     \            /      \                   /       \                 /       \                    /       \            /     \                    /        \
  yes      no     yes    no         yes      no                yes       no               yes        no                yes       no        yes     no                 yes        no
  /         \     /        \         /        \               /            \             /            \                /          \        /        \                 /            \
pidgeon    bear  salmon   seaweed  rain      cloud          mountain       lake        love          joy             anger    loneliness   charity   insomnia      movement        future
*/


int main() {
  print_id("Lab 8: Artificial Intelligence with Innate Knowledge");

  //answers
  Thing a = {"It's a pidgeon"};
  Thing b = {"It's a bear"};
  Thing c = {"It's salmon"};
  Thing d = {"It's seaweed"};
  Thing e = {"It's rain"};
  Thing f = {"It's a cloud"};
  Thing g = {"It's a mountain"};
  Thing h = {"It's a lake"};
  Thing i = {"It's love"};
  Thing j = {"It's joy"};
  Thing k = {"It's anger"};
  Thing l = {"It's loneliness"};
  Thing m = {"It's charity"};
  Thing n = {"It's insomnia"};
  Thing o = {"It's movement"};
  Thing p = {"It's the future"};

  //questions : bottom level / level 4
  Thing ab = {"Can it fly?", &a, &b};
  Thing cd = {"Can it swim?", &c, &d};
  Thing ef = {"Does it fall down to earth?", &e, &f};
  Thing gh = {"Can you climb it?", &g, &h};
  Thing ij = {"Is it for another person?", &i, &j};
  Thing kl = {"Is it associated with the color red?", &k, &l};
  Thing mn = {"Is it good to be/have?", &m, &n};
  Thing op = {"Can it be an action?", &o, &p};

  //questions: level 3
  Thing abcd = {"Does it live on land?", &ab, &cd};
  Thing efgh = {"Is it in the sky?", &ef, &gh};
  Thing ijkl = {"Is it a good feeling?", &ij, &kl};
  Thing mnop = {"Can it be a characteristic?", &mn, &op};

  //questions: level 2
  Thing one  =  {"Is it alive?", &abcd, &efgh};
  Thing two = {"Is it a feeling?" , &ijkl, &mnop};

  //questions: top level / level 1
  Thing first = {"Is it a concrete noun?", &one, &two};
  Thing *top = &first; //full tree

  //user explanation
  cout << "Answer my questions and I'll guess what noun you're thinking about." << endl;

  //loop through tree
  Thing *temp = top;
  string buffer;
  while(true){
      cout << temp->sayThis << endl;
      if(temp->yes == 0 && temp->no == 0) break;
      cout << "[yes / no] ";

      getline(cin, buffer); //input validation
      if(buffer == "yes") temp = temp->yes;
      else if(buffer == "no") temp = temp->no;
  }
  

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
