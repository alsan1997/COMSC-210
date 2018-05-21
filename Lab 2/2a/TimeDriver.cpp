// Lab 2a, Writing Overloading Operators
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Block

#include <iostream>
using namespace std;

#include <cassert>

#include "Time.h"
#include "Time.h" // testing ifndef

void outputMe();

int main()
{
  // print my name and assignment's title
  outputMe();

  Time time;
  Time time2;

  float hour1 = 1;
  float minute1 = 40;
  float second1 = 30;

  float hour2 = 1;
  float minute2 = 40;
  float second2 = 30;

  // setting datas
  time.setHour(hour1);
  time.setMinute(minute1);
  time.setSecond(second1);

  time2.setHour(hour2);
  time2.setMinute(minute2);
  time2.setSecond(second2);

  // testing operator functions
  cout << "========Testing operator functions========" << endl;
  cout << "Expected is time object is not less than time2 object" << endl;
  if(time < time2)
    cout << "Result: Test failed, time object is less than time2 object" << endl << endl;
  else
    cout << "Result: time object is not less than time2 object\n\n";
  assert(!(time < time2));

  cout << "Expected is time object is equal to time2 object" << endl;
  if(time == time2)
    cout << "Result: time object is equal to time2 object" << endl << endl;
  else
    cout << "Result: time object is not equal to time2 object\n\n";
  assert(time == time2);

  // test all function
  cout << "========Test main object========" << endl;
  cout << "Expected time in hours is 1.675" << endl;
  cout << "Time in hours is: " << time.timeInHours() << endl << endl;
  assert(time.timeInHours() < 1.6751 || time.timeInHours() > 1.6749);

  cout << "Expected time in minutes is 100.5" << endl;
  cout << "Time in minutes is: " << time.timeInMinutes() << endl << endl;
  assert(time.timeInMinutes() < 100.51 || time.timeInMinutes() > 100.49);

  cout << "Expected time in seconds is 6030" << endl;
  cout << "Time in seconds is: " << time.timeInSeconds() << endl << endl;
  assert(time.timeInSeconds() == 6030);

  // object copy testing
  {
    const Time copy = time;

    // ...confirm that copy's contents match road's
    cout << "========Object copy testing========" << endl;
    cout << "Expected object copy in hours is 1.675" << endl;
    cout << "Object copy time in hours is: " << copy.timeInHours() << endl << endl;
    assert(copy.timeInHours() < 1.6751 || copy.timeInHours() > 1.6749);

    cout << "Expected object copy in minutes is 100.5" << endl;
    cout << "Object copy time in minutes is: " << copy.timeInMinutes() << endl << endl;
    assert(copy.timeInMinutes() < 100.51 || copy.timeInMinutes() > 100.49);

    cout << "Expected object copy in minutes is 6030" << endl;
    cout << "Object copy time in minutes is: " << copy.timeInSeconds() << endl << endl;
    assert(copy.timeInSeconds() == 6030);
  }

  // assignment copy testing
  {
    Time copy;
    copy = time;

    // ...confirm that assignment copy's contents match road's
    cout << "========Assignment copy testing========" << endl;
    cout << "Expected assignment copy in hours is 1.675" << endl;
    cout << "Copy assignment time in hours is: " << copy.timeInHours() << endl << endl;
    assert(copy.timeInHours() < 1.6751 || copy.timeInHours() > 1.6749);

    cout << "Expected assignment copy in minutes is 100.5" << endl;
    cout << "Copy assignment time in minutes is: " << copy.timeInMinutes() << endl << endl;
    assert(copy.timeInMinutes() < 100.51 || copy.timeInMinutes() > 100.49);

    cout << "Expected assignment copy in minutes is 6030" << endl;
    cout << "Copy assignment time in minutes is: " << copy.timeInSeconds() << endl << endl;
    assert(copy.timeInSeconds() == 6030);
  }
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 2a, Writing Overloading Operators \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
