// Lab 5a, Applying A Data Structure To A Big Data Application
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <algorithm>
#include <cstring>
#include <ctime>
#include "DynamicArray.h"

struct Subject
{
  string subjectCode;
  int counts;
};

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // for parsing the inputfile
  int n = 0;
  int duplicates = 0, inc = 0;
  char* token;
  char buf[1000];
  const char* const tab = "\t";
  DynamicArray<string> seenTerms(100000); // create array of string for terms
  DynamicArray<string> seenSections(100000); // create array of string for sections

  DynamicArray<Subject> a;

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

    bool check2 = false;
    for(int i = 0; i < inc; i++)
    {
      if(seenTerms[i] == term && seenSections[i] == section) // check if term & section the same
      {
        duplicates++;
        check2 = true;
      }
    }

    if(check2) continue;
    if(!check2)
    {
      seenTerms[inc] = term;
      seenSections[inc] = section;
      inc++;
    }

    int x = a.size();
    // process to create array of subject
    bool check = false;
    for(int i = 0; i < x; i++)
    {
      if(a[i].subjectCode == subjectCode)
      {
        a[i].counts++;
        check = true;
        break;
      }
    }

    if(!check)
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

  for (int i = 0; i < a.size(); i++)
    for (int j = i + 1; j < a.size(); j++)
      if (a[j].subjectCode < a[i].subjectCode)
      swap(a[j], a[i]);

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC;

  for(int i = 0; i < a.size(); i++)
  {
    cout << a[i].subjectCode << ", " << a[i].counts << " sections" << endl;
  }

  // cout time taken for the whole program
  cout << "Time taken: " << elapsedSeconds << "s" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 5a, Applying A Data Structure To A Big Data Application \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
