// Lab 2c: Using Templated Classes
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Block

#include <iostream>
using namespace std;

#include <stack>
#include <string>
#include <cstdlib>

void outputMe();

int main()
{
  outputMe();

  stack<double> s;
  char buf[100];

  while(true)
  {
    // prompt user
    cout << "Enter: ";

    // print data
    for(stack<double> copy = s; !copy.empty(); copy.pop())
    {
      cout << copy.top() << " " ;
    }

    cin >> buf;

    // break if q or Q
    if(buf[0] == 'q' || buf[0] == 'Q') break;

    // else if addition
    else if(buf[0] == '+' && s.size() >= 2)
    {
      double a = s.top(); s.pop();
      double b = s.top(); s.pop();
      double c = a + b;
      s.push(c);
    }

    // else if subtraction
    else if(buf[0] == '-' && s.size() >= 2)
    {
      double a = s.top(); s.pop();
      double b = s.top(); s.pop();
      double c = b - a;
      s.push(c);
    }

    // else if division
    else if(buf[0] == '/' && s.size() >= 2)
    {
      double a = s.top(); s.pop();
      double b = s.top(); s.pop();
      double c = b / a;
      s.push(c);
    }

    // else if multiplication
    else if(buf[0] == '*' && s.size() >= 2)
    {
      double a = s.top(); s.pop();
      double b = s.top(); s.pop();
      double c = b * a;
      s.push(c);
    }

    // else, change them to zeros
    else
    {
      double a = atof(buf);
      s.push(a);
    }
  }
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 2c: Using Templated Classes \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
