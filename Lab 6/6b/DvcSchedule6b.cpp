// Lab 6b, Big Data Solutions
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
#include "LinkedArray.h"

struct Subject
{
  string subjectCode;
  int counts;
};

struct Check
{
  string TERM;
};

struct Section
{
  DynamicArray<Check> terms;
};

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  int n = 0; // dots
  int duplicates = 0; // number of duplicates
  int indexSection; // store int data type of section

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  LinkedArray<Subject> a;
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

  // close file
  fin.close();

  cout << "\nThere are " << duplicates << " duplicates data" << endl;
  int x = a.size();
  for (int i = 0; i < x; i++)
    for (int j = i + 1; j < x; j++)
      if (a[j].subjectCode < a[i].subjectCode)
      swap(a[j], a[i]);

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;

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
  cout << "Lab 6b, Big Data Solutions \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
