// Lab 1a, Class Programming And Testing
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

  Road road;

  cout << "========Testing main object========\n";
  road.setWidth(250);
  cout << "Expected width is 250" << endl;
  cout << "Testing setter for width: " << road.getWidth() << endl << endl;
  assert(road.getWidth() == 250);

  road.setLength(25);
  cout << "Expected length is 25" << endl;
  cout << "Testing setter for length: " << road.getLength() << endl << endl;
  assert(road.getLength() == 25);


  cout << "Expected volume is 275000000" << endl;
  cout << "The volume for the road is " << road.asphalt(100) << endl << endl;
  assert(road.asphalt(100) == 275000000);


  // object copy testing
  {
    const Road copy = road; // a read-only copy

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
    Road copy;
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
  cout << "Lab 1a, Class Programming And Testing \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
