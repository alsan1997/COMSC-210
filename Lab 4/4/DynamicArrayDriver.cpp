// Lab 4a, Write A Dynamic Array Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <iostream>
using namespace std;

#include <cassert>

#include "DynamicArray.h"

void outputMe();

int main()
{
  // call identifying output function
  outputMe();

  // initialize
  DynamicArray<int> a;
  DynamicArray<int> b(1000);

  // set arrays
  a[9] = 2;
  a[2] = 4;
  a[3] = 511;

  b[984] = 172;
  b[1005] = 23;

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

  cout << "Expected: b[984] == 172" << endl;
  if(b[984] == 172)
    cout << "Result: b[984] == 172" << endl << endl;
  else
    cout << "Result: b[984] != 172" << endl << endl;
  assert(b[984] == 172);

  cout << "Expected: b[1005] == 23" << endl;
  if(b[1005] == 23)
    cout << "Result: b[1005] == 23" << endl << endl;
  else
    cout << "Result: b[1005] != 23" << endl << endl;
  assert(b[1005] == 23);

  cout << "======Testing size function======\n";
  cout << "Expected: Size a is 3" << endl;
  if(a.size() == 3)
    cout << "Result: Size a is " << a.size() << endl << endl;
  else
    cout << "Result: Size a is not " << a.size() << endl << endl;
  assert(a.size() == 3);

  cout << "Expected: Size b is 2" << endl;
  if(b.size() == 2)
    cout << "Result: Size b is " << b.size() << endl << endl;
  else
    cout << "Result: Size b is not " << b.size() << endl << endl;
  assert(b.size() == 2);

  cout << "======Testing capacity function======" << endl;
  cout << "Expected: Capacity a is 100" << endl;
  if(a.capacity() == 100)
    cout << "Result: Capacity a is 100" << endl << endl;
  else
    cout << "Result: Capacity a is not 100" << endl << endl;
  assert(a.capacity() == 100);

  cout << "Expected: Capacity b is now 1006" << endl;
  if(b.capacity() == 1006)
    cout << "Result: Capacity b is 1006" << endl << endl;
  else
    cout << "Result: Capacity b is not 1006" << endl << endl;
  assert(b.capacity() == 1006);

  cout << "======Testing containsKey function======" << endl;
  cout << "Expected: containsKey a[9] is true" << endl;
  if(a.containsKey(9))
    cout << "Result: containsKey a[9] is true " << endl << endl;
  else
    cout << "Result: containsKey a[9] is false " << endl << endl;
  assert(a.containsKey(9) == true);

  cout << "Expected: containsKey b[1005] is true" << endl;
  if(b.containsKey(1005))
    cout << "Result: containsKey b[1005] is true " << endl << endl;
  else
    cout << "Result: containsKey b[1005] is false " << endl << endl;
  assert(b.containsKey(1005) == true);


  cout << "======Testing deleteKey function======" << endl;
  a.deleteKey(9);
  cout << "a[9] is deleted" << endl;
  cout << "Expected: containsKey a[9] is false" << endl;
  if(a.containsKey(9))
    cout << "Result: containsKey a[9] is true " << endl << endl;
  else
    cout << "Result: containsKey a[9] is false " << endl << endl;
  assert(a.containsKey(9) == false);

  b.deleteKey(1005);
  cout << "b[1005] is deleted" << endl;
  cout << "Expected: containsKey b[1005] is false" << endl;
  if(b.containsKey(1005))
    cout << "Result: containsKey b[1005] is true " << endl << endl;
  else
    cout << "Result: containsKey b[1005] is false " << endl << endl;
  assert(b.containsKey(1005) == false);

  cout << "======Testing vector<int> keys function======" << endl;
  vector<int> keys = a.keys();
  for (int i = 0; i < keys.size(); i++)
  cout << "a[" << keys[i] << "] = " << a[keys[i]] << endl;
  cout << endl;

  vector<int> keys2 = b.keys();
  for (int i = 0; i < keys2.size(); i++)
  cout << "b[" << keys2[i] << "] = " << b[keys2[i]] << endl;
  cout << endl;

  // testing copy assignment
  {
    cout << "======Testing Copy Assignment Object======" << endl;
    const DynamicArray<int> copya = a;
    const DynamicArray<int> copyb = b;

    cout << "copya[2] == 4" << endl;
    assert(copya[2] == 4);
    cout << "copya[3] == 511" << endl;
    assert(copya[3] == 511);

    cout << "\ncopyb[984] = 172" << endl << endl;
    assert(copyb[984] == 172);
  }

  // testing reading assignment
  {
    DynamicArray<int> copy2a; copy2a = a;
    DynamicArray<int> copy2b; copy2b = b;

    cout << "======Testing Reading Assignment Object======" << endl;
    cout << "copy2a[2] == 4" << endl;
    assert(copy2a[2] == 4);
    cout << "copy2a[3] == 511" << endl;
    assert(copy2a[3] == 511);

    cout << "\ncopy2b[984] = 172" << endl << endl;
    assert(copy2b[984] == 172);
  }

  a.clear();
  cout << "=====Testing clear function======" << endl;
  cout << "Expected: Size a is 0" << endl;
  if(a.size() == 0)
    cout << "Result: Size a is 0" << endl << endl;
  else
    cout << "Result: Size a is not 0" << endl << endl;
  assert(a.size() == 0);

  b.clear();
  cout << "Expected: Size b is 0" << endl;
  if(b.size() == 0)
    cout << "Result: Size b is 0" << endl << endl;
  else
    cout << "Result: Size b is not 0" << endl << endl;
  assert(b.size() == 0);
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 4a, Write A Dynamic Array Class Template \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
