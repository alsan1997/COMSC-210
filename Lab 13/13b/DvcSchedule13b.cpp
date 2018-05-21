// Lab 13b, Applying A Data Structure To A Database Program
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <ctime>
using namespace std;

#include "DynamicArray.h"
#include "SortableStaticArray.h"

struct Subject
{
  string subjectCode;
  int counts;
  bool operator<(const Subject&) const;
};

struct Check
{
  string TERM;
};

struct Section
{
  DynamicArray<Check> terms;
};

bool Subject::operator<(const Subject& a) const
{
  return subjectCode < a.subjectCode;
}

void outputMe();

int main()
{
  outputMe(); // call identifying output

  int n = 0; // dots
  int duplicates = 0; // number of duplicates
  int indexSection; // store int data type of section

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  StaticArray<Subject, 300> a;
  DynamicArray<Section> b(10000);

  clock_t startTime = clock(); // start timer

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  // read the input file
  while (fin.good())
  {
    if(++n % 1000 == 0) {cout << '.'; cout.flush();} // cout '.' every 1000 data processed

    // read the line
    string line;
    getline(fin, line);
    strcpy(buf, line.c_str());
    if(buf[0] == 0) continue;

    // parse the line
    const string term(token = strtok(buf, tab));
    const string section(token = strtok(0, tab));
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line
    const string subjectCode(course.begin(), course.begin() + course.find('-'));

    // if I get this far, then it's a valid record
    // cout << term << '|' << section << '|' << course << '|' << instructor << '|' << whenWhere << '|' << subjectCode << endl;

    // checking for duplicates
    bool check2 = false;
    indexSection = atoi(section.c_str());
    int checkSize = b[indexSection].terms.size();
    for(int i = 0; i < checkSize; i++)
    {
      if(b[indexSection].terms[i].TERM == term)
        {
          check2 = true;
          duplicates++;
        }
    }

    if(check2) continue;

    // append new term or new section
    if(!check2)
    {
      Check check;
      check.TERM = term;
      b[indexSection].terms[checkSize] = check;
      checkSize++;
    }

    // process to create array of subject
    bool check1 = false;
    int x = a.size();
    for(int i = 0; i < x; i++)
    {
      if(a[i].subjectCode == subjectCode)
      {
        a[i].counts++;
        check1 = true;
        break;
      }
    }

    if(!check1)
    {
      Subject subject;
      subject.subjectCode = subjectCode;
      subject.counts = 1;
      a[x] = subject;
    }
  }
  fin.close(); // close file

  cout << "\nThere are " << duplicates << " duplicates data" << endl;\
  a.sort(); // call sort function

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;

  int x = a.size();
  for(int i = 0; i < x; i++)
  {
    cout << a[i].subjectCode << ", " << a[i].counts << " sections" << endl;
  }

  // cout time taken for the whole program
  cout << "Time taken: " << elapsedSeconds << "s" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 13b, Applying A Data Structure To A Database Program \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
