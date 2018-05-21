// Lab 11a, Write And Test A Priority Queue Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <cassert>
#include <iostream>
using namespace std;

#include "PriorityQueue.h"
#include "PriorityQueue.h" // testing ifndef

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // create an object
  PriorityQueue<int> a(10);

  cout << "=====Testing enqueue function=====" << endl;
  cout << "Inserting data: 50, 83, 9, 15, and 5" << endl;
  a.enqueue(50);
  a.enqueue(83);
  a.enqueue(9);
  a.enqueue(15);
  a.enqueue(5);
  cout << endl;

  cout << "=====Testing size function=====" << endl;
  cout << "Expected: size is 5\n";
  cout << "Result: size is " << a.size() << endl << endl;
  assert(a.size() == 5);

  cout << "=====Testing front function======" << endl;
  cout << "Expected: front is 83 " << endl;
  cout << "Result: front is " << a.front() << endl << endl;
  assert(a.front() == 83);

  cout << "=====Testing back function======" << endl;
  cout << "Expected: back is 5 " << endl;
  cout << "Result: back is " << a.back() << endl << endl;
  assert(a.back() == 5);

  cout << "=====Testing dequeue function======" << endl;
  cout << "Dequeueing\n";
  a.dequeue();
  cout << "Expected: front now is 50\n";
  cout << "Result: front is " << a.front() << endl << endl;
  assert(a.front() == 50);

  cout << "=====Testing empty function=====" << endl;
  cout << "Expected: empty function should return false\n";
  cout << "Result: a.empty() is " << a.empty() << endl << endl;
  assert(a.empty() == false);

  // object copy testing
  {
    const PriorityQueue<int> copy = a; // read-only copy
    assert(copy.size() == a.size());
    assert(copy.empty() == a.empty());
  }

  // object assignment testing
  {
    PriorityQueue<int> copy;
    copy = a; // assignment copy

    assert(copy.size() == a.size());
    assert(copy.empty() == a.empty());
  }

  cout << "=====Testing clear function=====" << endl;
  a.clear();
  cout << "Expected: siz function is 0\n";
  cout << "Result: a.size() is " << a.size() << endl << endl;
  assert(a.size() == 0);

  cout << "Expected: empty function return true\n";
  cout << "Result: a.empty() is " << a.empty() << endl << endl;
  assert(a.empty() == 1);
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 11a, Write And Test A Priority Queue Template\n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
