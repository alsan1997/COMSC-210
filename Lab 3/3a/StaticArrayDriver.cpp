// Lab 3a, Write A Static Array Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <iostream>
using namespace std;

#include <cassert>

#include "StaticArray.h"
#include "StaticArray.h" // testing ifndef

void outputMe();

int main()
{
  // call identifying output function
  outputMe();

  StaticArray<int, 10> a;
  a[9] = 2;
  a[2] = 4;
  a[3] = 511;

  // testing all functions
  cout << "======Testing setter function======\n";
  cout << "Expected: a[9] == 2" << endl;
  if(a[9] == 2)
    cout << "Result: a[9] == 2" << endl << endl;
  else
    cout << "Result: a[9] != 2" << endl << endl;
  assert(a[9] == 2);

  cout << "Expected: a[2] == 4" << endl;
  if(a[2] == 4)
    cout << "Result: a[2] == 4" << endl << endl;
  else
    cout << "Result: a[2] != 4" << endl << endl;
  assert(a[2] == 4);

  cout << "Expected: a[3] == 511" << endl;
  if(a[3] == 511)
    cout << "Result: a[3] == 511" << endl << endl;
  else
    cout << "Result: a[3] != 511" << endl << endl;
  assert(a[3] == 511);

  cout << "======Testing size function======\n";
  cout << "Expected: Size is 3" << endl;
  if(a.size() == 3)
    cout << "Result: Size is " << a.size() << endl << endl;
  else
    cout << "Result: Size is not " << a.size() << endl << endl;
  assert(a.size() == 3);

  cout << "======Testing capacity function======" << endl;
  cout << "Expected: Capacity is 10" << endl;
  if(a.capacity() == 10)
    cout << "Result: Capacity is 10" << endl << endl;
  else
    cout << "Result: Capacity is not 10" << endl << endl;
  assert(a.capacity() == 10);

  cout << "======Testing containsKey function======" << endl;
  cout << "Expected: containsKey a[9] is true" << endl;
  if(a.containsKey(9))
    cout << "Result: containsKey a[9] is true " << endl << endl;
  else
    cout << "Result: containsKey a[9] is false " << endl << endl;
  assert(a.containsKey(9) == true);

  a.deleteKey(9);
  cout << "======Testing deleteKey function======" << endl;
  cout << "Expected: deleteKey a[9] is false" << endl;
  if(a.containsKey(9))
    cout << "Result: deleteKey a[9] is true " << endl << endl;
  else
    cout << "Result: deleteKey a[9] is false " << endl << endl;
  assert(a.containsKey(9) == false);

  cout << "======Testing vector<int> keys function======" << endl;
  vector<int> keys = a.keys();
  for (int i = 0; i < keys.size(); i++)
  cout << "a[" << keys[i] << "] = " << a[keys[i]] << endl << endl;

  a.clear();
  cout << "=====Testing clear function======" << endl;
  cout << "Expected: Size is 0" << endl;
  if(a.size() == 0)
    cout << "Result: Size is 0" << endl << endl;
  else
    cout << "Result: Size is not 0" << endl << endl;
  assert(a.size() == 0);

  cout << "=======Testing Main Object======" << endl;
  for(int i = 0; i < a.capacity(); i++)
  cout << "a[" << i << "] = " << a[i] << endl;
  cout << endl;

  // testing copy assignment
  {
    const StaticArray<int, 10> copy = a;
    cout << "======Testing Copy Assignment Object======" << endl;
    for(int i = 0; i < copy.capacity(); i++)
    cout << "copy[" << i << "] = " << copy[i] << endl;
    cout << endl;
  }

  // testing reading assignment
  {
    StaticArray<int, 10> copy2;
    copy2 = a;

    cout << "======Testing Reading Assignment Object======" << endl;
    for(int i = 0; i < copy2.capacity(); i++)
    cout << "copy2[" << i << "] = " << copy2[i] << endl;
  }
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 3a, Write A Static Array Class Template \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
