// Lab 0c, Console Programming Basics
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <string>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

void outputMe();

int main()
{
  char buf[100];
  int age;
  string name, city;
  float temp, cel;

  // Call identifying output
  outputMe();

  // Prompt user to enter their age
  cout << "Enter your age: ";
  cin >> buf;
  cin.ignore(1000, 10);
  age = atoi(buf);

  // Prompt user to enter their name
  cout << "Enter your name: ";
  getline(cin, name);

  // Prompt user to enter the temperature in F
  cout << "Enter the temperature outside right now (degrees F): ";
  cin >> buf;
  cin.ignore(1000, 10);
  temp = atof(buf);

  // Prompt user to enter the city
  cout << "What city are you in right now ?: ";
  getline(cin, city);
  cout << endl;

  // Convert to celsius
  cel = ((temp - 32) * 5) / 9;

  // Output result, and round celsius to 1 decimal.
  cout << name << " is " << age << " years old now, and will be " << age + 1 << " a year from now. " << endl;
  cout << "It's " << temp << " degrees F in " << city;

  cout.setf(ios::fixed|ios::showpoint);
  cout << setprecision(1);
  cout << " -- that's " << cel << " degrees C. " << endl;
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 0c, Console Programming Basics \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
