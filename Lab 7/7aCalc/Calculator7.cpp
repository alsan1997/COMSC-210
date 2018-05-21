// Lab 7a: Write And Apply A Stack Template
// Programmer: Axel Hugo
// Editor(s) used : Code::Blocks
// Compiler(s) used : Code::Blocks

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
using namespace std;

#include "Stack.h"

int main ()
{
 // print my name and this assignment's title.
  cout << "Lab Lab 7a: Stacks and Queues " << endl;
  cout << "Programmer: Axel Hugo " << endl;
  cout << "Editor(s) used: Code Blocks " << endl;
  cout << "Compiler(s) ised : Code Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__<<" at " << __TIME__ << endl << endl;

  Stack<double> s;
  char buf[100];
  double random;
  double peekvalue;

  // loop start
  while(true)
  {
     cout << "Enter: ";

     // output all number in stack
     for(Stack<double> copy = s; !copy.empty(); copy.pop(random))
     {
       copy.peek(peekvalue); // get data of peek value in stack list
       cout << peekvalue << " ";
     }

     //input number or operator
     cin >> buf;

    // if Q or q, break from loop
    if(buf[0] == 'q' || buf[0] == 'Q') break;

    // check all symbol and append them to stack linkedlist
    else if(buf[0] == '+' && s.size() >= 2)
    {
      double a; s.peek(a); s.pop(random);
      double b; s.peek(b); s.pop(random);
      double c; a + b; s.push(c);
    }

    else if(buf[0] == '-' && s.size() >= 2)
    {
      double a; s.peek(a); s.pop(random);
      double b; s.peek(b); s.pop(random);
      double c; b - a; s.push(c);
    }

    else if(buf[0] == '/' && s.size() >= 2)
    {
      double a; s.peek(a); s.pop(random);
      double b; s.peek(b); s.pop(random);
      double c; b / a;
      s.push(c);
    }

    else if(buf[0] == '*' && s.size() >= 2)
    {
      double a; s.peek(a); s.pop(random);
      double b; s.peek(b); s.pop(random);
      double c = b * a; s.push(c);
    }

    else
    {
      double a = atof(buf); s.push(a);
    }
  }
}
