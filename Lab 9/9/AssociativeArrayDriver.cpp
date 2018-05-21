// Lab 9, Write, Test, and Apply The AssociativeArray Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <iostream>
using namespace std;

#include <fstream>
#include <cstring>
#include <cassert>
#include <string>

#include "AssociativeArray.h"
#include "AssociativeArray.h" // testing ifndef

struct TermSection
{
  string term;
  string section;
};

// stand alone
bool operator==(const TermSection& x, const TermSection& y)
{
  // if terms don't match, return false
  if(x.term != y.term) return false;

  // if sections don't match, return false
  if(x.section != y.section) return false;

  return true;
}

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // variables
  AssociativeArray<string, TermSection> a;

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  // open the input file
  ifstream fin;
  int dataNum = 1;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  cout << "Opening and reading 115 data from dvc-schedule.txt\n";
  // read the input file
  while(!fin.eof())
  {
    dataNum++;

    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if(buf[0] == 0) continue;

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line

    TermSection ts = {term, section};
    a[ts] = course;

    if(dataNum == 118) break; // break if dataNum is 118
  }
  fin.close(); // close file

  cout << "======Testing capacity function======\n";
  cout << "Expected: a.capacity() is 200 (doubled from initial which is 100)\n";
  cout << "Result: a.capacity() is " << a.capacity() << endl << endl;
  assert(a.capacity() == 200);

  cout << "======Testing size function======\n";
  cout << "Expected: a.size() is 115\n";
  cout << "Result: a.size() is " << a.size() << endl << endl;
  assert(a.size() == 115);

  cout << "======Testing vector keys function======" << endl;
  vector<TermSection> keys = a.keys();
  cout << "Expected: vector keys value is 115\n";
  cout << "Result: keys.size() is " << keys.size() << endl;
  cout << endl;

  AssociativeArray<string, TermSection> copy3;
  copy3 = a;
  copy3.clear();
  cout << "=====Testing clear function=====\n";
  cout << "clearing copy3 object\n";
  cout << "Expected: copy3.size() is 0\n";
  cout << "Result: copy3.size() is " << copy3.size() << endl << endl;
  assert(copy3.size() == 0);

  // testing object copy
  {
    cout << "=====Testing object copy=====\n";
    const AssociativeArray<string, TermSection> copy1 = a;

    cout << "Expected: copy1.capacity() is 200\n";
    cout << "Result: copy1.capacity() is " << copy1.capacity() << endl << endl;
    assert(copy1.capacity() == a.capacity());

    cout << "Expected: copy1.size() is 115\n";
    cout << "Result: copy1.size() is " << copy1.size() << endl << endl;
    assert(copy1.size() == a.size());
  }

  // testing object assignment
  {
    cout << "=====Testing object assignment=====\n";
    AssociativeArray<string, TermSection> copy2;
    copy2 = a;

    cout << "Expected: copy2.capacity() is 200\n";
    cout << "Result: copy2.capacity() is " << copy2.capacity() << endl << endl;
    assert(copy2.capacity() == a.capacity());

    cout << "Expected: copy2.size() is 115\n";
    cout << "Result: copy2.size() is " << copy2.size() << endl << endl;
    assert(copy2.size() == a.size());
  }

  dataNum = 1;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  cout << "Reopen dvc-schedule.txt to ensure data stored matches\n";

  // read the input file
  while(!fin.eof())
  {
    dataNum++;

    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if(buf[0] == 0) continue;

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line

    TermSection ts = {term, section};
    TermSection duplicate = {"Fall 2002", "9034"}; // duplicate data

    // if found duplicate data, delete and continue
    if(ts == duplicate)
    {
      a.deleteKey(duplicate);
      continue;
    }

    // if found match, delete
    if(a.containsKey(ts) == true)
      a.deleteKey(ts);

    // else error and break
    else
    {
      cout << "Error! Array not found!\n";
      break;
    }

    assert(a.containsKey(ts) == false);

    if(dataNum == 118) break; // break if dataNum is 118
  }
  fin.close(); // close file

  cout << "To confirm that all data is match and deleted, by testing size function\n";
  cout << "=====Testing size function=====\n";
  cout << "Expected: a.size() is 0\n";
  cout << "Result: a.size() is " << a.size() << endl;
  assert(a.size() == 0);
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 9, Write, Test, and Apply The AssociativeArray Template\n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
