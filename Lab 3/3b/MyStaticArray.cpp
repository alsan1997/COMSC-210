// Lab 3b, Write A Static Array Application
// Programmer: Aldo Sanjoto
// Editor(s) used: Code Blocks
// Compiler(s) used: Code Blocks

#include <iostream>
using namespace std;

#include "StaticArray.h"
#include <cstdlib>

void outputMe();

int main()
{
  // print identifying output
  outputMe();

  char buf[100];
  double index, value, look;
  StaticArray<double, 100> a;

  // while loop for prompting index and value
  while(true)
  {
    cout << "Input an index and a value [Q to quit]: ";
    cin >> buf;

    if(buf[0] == 'q' || buf[0] == 'Q')break;
    index = atof(buf);

    cin >> buf;
    value = atof(buf);

    a[index] = value;
  }

  // cout the value in inUse array
  cout << "\nI stored this many value: " << a.size();
  cout << "\nThe values are:\n";

  vector<int> keys = a.keys();
  for(int i = 0; i < keys.size(); i++)
  cout << keys[i] << " " << a[keys[i]] << endl;

  // while loop to search wanted index
  while(true)
  {
    cout << "\nInput an index for me to look up [Q to quit]: ";
    cin >> buf;
    look = atof(buf);

    if(buf[0] == 'q' || buf[0] == 'Q')break;

    if(a.containsKey(look))
      cout << "Found it -- the value stored at " << look << " is " << a[look] << endl;
    else
      cout << "I didn't find it" << endl;
  }

  cout << "Goodbye!" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 3b, Write A Static Array Application \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
