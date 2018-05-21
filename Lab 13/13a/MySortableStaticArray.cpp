// Lab 13a, Write A Sortable Array Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <cstdlib>
#include <iostream>
using namespace std;

#include "SortableStaticArray.h"

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

  // output sorted data
  cout << "\nI sorted this many value: " << a.size();
  cout << "\nThe sorted values are:\n";
  a.sort();

  vector<int> keys2 = a.keys();
  for(int i = 0; i < keys2.size(); i++)
  cout << keys2[i] << " " << a[keys2[i]] << endl;

  cout << "\nGoodbye!" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 13a, Write A Sortable Array Class Template\n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
