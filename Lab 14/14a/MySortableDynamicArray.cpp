// Lab 14a, Write A Sortable Array Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code Blocks
// Compiler(s) used: Code Blocks

#include <iostream>
using namespace std;

#include "SortableDynamicArray.h"
#include <cstdlib>

void outputMe();

int main()
{
  // print identifying output
  outputMe();

  char buf[100];
  double index, value, look;
  SortableDynamicArray<int> a;

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

  cout << "\nInput the amount of value to be included in sorting and binary searching: ";
  cin >> buf;
  int numOfSearch = atoi(buf);
  cout << endl;

  cout << "The sorted values are: " << endl;
  a.sort(numOfSearch);

  for(int i = 0; i < numOfSearch; i++)
  {
    if(a.containsKey(i) == true)
      cout << "  " << i << "  " << a[i] << endl;
  }
  cout << endl;

  while(true)
  {
    cout << "Input a value for me to look up [Q to quit]: ";
    cin >> buf;
    look = atoi(buf);

    if(buf[0] == 'q' || buf[0] == 'Q') break;
    index = a.bsearch(numOfSearch, look);

    if(index == -1)
      cout << "I didn't find it" << endl;
    else
      cout << "Found it -- the value " << look << " is stored at index " << index << endl << endl;
  }

  cout << "Goodbye!" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 14a, Write A Sortable Array Class Template \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
