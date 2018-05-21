// Lab 7a, Write And Apply A Stack Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <iostream>
using namespace std;

#include <vector>
#include <cassert>
#include "Stack.h"
#include "Stack.h" // ifndef testing

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // initialize
  Stack<int> a;

  int value1 = 20, value2 = 40, value3 = 60, value4 = 70;

  cout << "=========Testing push function========\n";
  a.push(value1);
  a.push(value2);
  a.push(value3);
  a.push(value4);
  cout << "Data inserted is: 20, 40, 60, 70\n";
  cout << "Data in stack now is: 20, 40, 60, 70\n\n";

  cout << "=========Testing peek function========\n";
  int peekValue;
  a.peek(peekValue);
  cout << "Expected: peekValue should be 70\n";
  cout << "Result: peekValue is " << peekValue << endl << endl;
  assert(peekValue == value4);

  cout << "=========Testing pop function========\n";
  cout << "Popping peekValue\n";
  a.pop(value1);
  int newpeekValue;
  a.peek(newpeekValue);
  cout << "Expected: Peek now is 60\n";
  cout << "Result: Peek is " << newpeekValue << endl << endl;
  assert(newpeekValue == 60);

  cout << "======Testing size function======\n";
  cout << "Expected: Size a is 3" << endl;
  cout << "Result: Size a is " << a.size() << endl << endl;
  assert(a.size() == 3);

  // testing copy assignment
  {
    cout << "======Testing Copy Assignment Object======" << endl;
    const Stack<int> copya = a;
    int testing;
    for(Stack<int> copy = copya; !copy.empty(); copy.pop(testing))
    {
      copy.peek(testing);
      cout << testing << " ";
    }

    cout << endl << endl;
  }

  // testing reading assignment
  {
    cout << "======Testing Copy Assignment Object======" << endl;
    Stack<int> copyb;
    copyb = a;
    int testing;
    for(Stack<int> copy = copyb; !copy.empty(); copy.pop(testing))
    {
      copy.peek(testing);
      cout << testing << " ";
    }

    cout << endl << endl;
  }

  a.clear();
  cout << "=====Testing clear function======" << endl;
  cout << "Expected: Size a is 0" << endl;
  cout << "Result: Size a is 0" << endl << endl;
  assert(a.size() == 0);

  a.empty();
  cout << "=====Testing empty function=====" << endl;
  cout << "Expected: a.empty() should return true\n";
  cout << "Result: a.empty is " << a.empty() << endl << endl;
  assert(a.empty() == 1);
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 7a, Write And Apply A Stack Template \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
