// Lab 14b, Applying A Data Structure To A Database Program
// Programmer: Axel Hugo
// Editor(s) used: Code Blocks
// Compiler(s) used: Code Blocks

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <algorithm>
#include <cstring>

// call header
#include "DynamicArray.h"
#include "SortableDynamicArray.h"

using namespace std;

void identification()
{
  cout << "Lab 14b, Applying A Data Structure To A Database Program" << endl;
  cout << "Programmer: Axel Hugo " << endl;
  cout << "Editor(s) used: Code Blocks " << endl;
  cout << "Compiler(s) ised : Code Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__<<" at " << __TIME__ << endl << endl;
}

struct Check
{
  string TERM;
};

struct Section
{
  DynamicArray<Check> terms; // an array of struck Check
};

struct Subject
{
  string subjectCode;
  int counts;
  bool operator<(const Subject& a) const {return subjectCode < a.subjectCode;}
};

int main()
{
  identification(); // call identifying output

  SortableDynamicArray<Subject> a(300);
  DynamicArray<Section> b(10000);

  // start timer
  clock_t startTime = clock();

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  //create an integer
  int n = 0, duplic = 0, indexSection = 0;

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  // read the input file
  while (fin.good())
  {
    // count the number of lines read from the file for every 1000 lines read.
    if(++n % 1000 == 0) {cout << '.'; cout.flush();}

    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if (buf[0] == 0) continue;

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    // checking for duplicates
    bool checkingdata = false;
    indexSection = atoi(section.c_str());
    int checkSize = b[indexSection].terms.size();
    for(int i = 0; i < checkSize; i++)
    {
      if(b[indexSection].terms[i].TERM == term)
        {
          checkingdata = true;
          duplic++;
        }
    }

    if(checkingdata) continue;

    // append new term or new section
    if(!checkingdata)
    {
      Check check;
      check.TERM = term;
      b[indexSection].terms[checkSize] = check;
      checkSize++;
    }

    // process to create array of subject
    bool checking = false;
    int x = a.size();
    for(int i = 0; i < x; i++)
    {
      if(a[i].subjectCode == subjectCode)
      {
        a[i].counts++;
        checking = true;
        break;
      }
    }

    if(!checking)
    {
      Subject subject;
      subject.subjectCode = subjectCode;
      subject.counts = 1;
      a[x] = subject;
    }
  }

  // to close the file
  fin.close();

  // output number of duplicates and sort them
  cout << "There are " << duplic << " duplicates data" << endl;

  a.sort(a.size());

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC; // stop timer
  int x = a.size();
  // output all data
  for(int i = 0; i < x; i++)
    cout << a[i].subjectCode << ", " << a[i].counts << " sections" << endl;

  // output program total time
  cout << "Program's Runtime: " << elapsedSeconds << "second" << endl;
}
