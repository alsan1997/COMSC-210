// Lab 2b, Writing Templates And Overloading Operators
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <iostream>
using namespace std;

#include <cassert>

#include "Road.h"
#include "Road.h" // testing ifndef

void outputMe();

int main()
{
  // print my name and this assignment's title
  outputMe();

  Road<float> road;
  Road<float> road2;
  Road<float> road3;
  Road<float> road4;

  road.setWidth(250);
  road.setLength(25);
  road2.setWidth(300);
  road2.setLength(30);

  // object in doubles
  road3.setWidth(12.31);
  road3.setLength(3.21);
  road4.setWidth(12.31);
  road4.setLength(3.21);

  // Operator function testing
  cout << "========Testing operator functions========\n";
  cout << "Expected is road object has smaller length than road2 object length" << endl;
  if(road < road2)
    cout << "Result: road object has smaller length than road2 object length" << endl << endl;
  else
    cout << "Result: road object has bigger length than road2 object length " << endl << endl;
  assert((road < road2));

  cout << "Expected is road and road2 object is not equal in length and width" << endl;
  if(road == road2)
    cout << "Result: road and road2 object has equal length and width" << endl << endl;
  else
    cout << "Result: road and road2 object length and width is not equal" << endl << endl;
  assert(!(road == road2));

  cout << "In doubles, expected is road3 length is not smaller than road4 object length" << endl;
  if(road3 < road4)
    cout << "Result: road3 object has smaller length than road4 object length" << endl << endl;
  else
    cout << "Result: road3 object length is not smaller than road4 object length\n\n";
  assert(!(road3 < road4));

  cout << "In doubles, expected is road3 and road4 object has equal length and width" << endl;
  if(road3 == road4)
    cout << "Result: road3 and road4 object has equal length and width" << endl << endl;
  else
    cout << "Result: road3 and road4 object length and width is not equal" << endl << endl;
  assert((road3 == road4));


  cout << "========Testing main object========\n";
  cout << "Expected width is 250" << endl;
  cout << "Testing setter for width: " << road.getWidth() << endl << endl;
  assert(road.getWidth() == 250);

  cout << "Expected length is 25" << endl;
  cout << "Testing setter for length: " << road.getLength() << endl << endl;
  assert(road.getLength() == 25);

  cout << "Expected volume is 275000000" << endl;
  cout << "The volume for the road is " << road.asphalt(100) << endl << endl;
  assert(road.asphalt(100) == 275000000);


  // object copy testing
  {
    const Road<float> copy = road; // a read-only copy

    // ...confirm that copy's contents match road's
    cout << "========Object copy testing========\n";
    cout << "Expected copy testing width is 250" << endl;
    cout << "Object copy length is: " << copy.getWidth() << endl << endl;
    assert(copy.getWidth() == road.getWidth());

    cout << "Expected copy testing length is 25" << endl;
    cout << "Object copy length is: " << copy.getLength() << endl << endl;
    assert(copy.getLength() == road.getLength());

    cout << "Expected copy testing volume is 275000000" << endl;
    cout << "Object copy length is: " << copy.asphalt(100) << endl << endl;
    assert(copy.asphalt(100) == road.asphalt(100));
  }

  // object assignment testing
  {
    Road<float> copy;
    copy = road;

    //...confirm that copy's contents match road's
    cout << "========Object assignment testing========\n";
    cout << "Expected assignment testing width is 250" << endl;
    cout << "Object assignment length is: " << copy.getWidth() << endl << endl;
    assert(copy.getWidth() == road.getWidth());

    cout << "Expected assignment testing length is 25" << endl;
    cout << "Object assignment length is: " << copy.getLength() << endl << endl;
    assert(copy.getLength() == road.getLength());

    cout << "Expected assignment testing volume is 275000000" << endl;
    cout << "Object assignment length is: " << copy.asphalt(100) << endl;
    assert(copy.asphalt(100) == road.asphalt(100));
  }
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 2b, Writing Templates And Overloading Operators \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
