// Lab 5b, Using A Data Structure As A Data Member
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
#include <vector>
#include "DynamicArray.h"

struct Subject
{
  string subjectCode;
  int counts;
};

struct Type
{
  string subjectCode;
  DynamicArray<Subject> courses;
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
  DynamicArray<string> seenTerms(100000); // create array for terms
  DynamicArray<string> seenSections(100000); // create array for sections

  DynamicArray<Type> a;

  clock_t startTime = clock(); // start timer

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  // testing output
  ofstream fout; // requires fstream
  fout.open("dvc-scheduleTest.xls");
  if (!fout.good()) throw "I/O error";

  // read the input file
  while(!fin.eof())
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
      if(seenTerms[i] == term && section == seenSections[i]) // check if term & section the same
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

    // process to create array of subject
    bool check = false;
    bool check3 = false;
    for(int i = 0; i < a.size(); i++)
    {
      if(a[i].subjectCode == subjectCode)
      {
        check = true;
        for(int j = 0; j < a[i].courses.size(); j++)
        {
          if(a[i].courses[j].subjectCode == course)
          {
            a[i].courses[j].counts++;
            check3 = true;
          }
        }

        if(!check3)
        {
          Subject subject;
          subject.subjectCode = course;
          subject.counts = 1;
          a[i].courses[a[i].courses.size()] = subject;
        }
      }
    }

    if(check) continue;

    if(!check)
    {
      Type type;
      type.subjectCode = subjectCode;
      Subject subject;
      subject.subjectCode = course;
      subject.counts = 1;
      type.courses[type.courses.size()] = subject;
      a[a.size()] = type;
    }
  }

  // close file
  fin.close();

  // output number of duplicates
  cout << "\nThere are " << duplicates << " duplicates data" << endl;

  // sorting in alphabetical order
  for (int i = 0; i < a.size(); i++)
    for (int j = i + 1; j < a.size(); j++)
      if (a[j].subjectCode < a[i].subjectCode)
      swap(a[j], a[i]);

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC; // stop timer

  for(int i = 0; i < a.size(); i++)
  {
    fout<< a[i].subjectCode << ", " << a[i].courses.size() << " course(s)" << endl;
    fout << "--------------" << endl;
    cout << a[i].subjectCode << ", " << a[i].courses.size() << " course(s)" << endl;
    cout << "--------------" << endl;
    for(int j = 0; j < a[i].courses.size(); j++)
    {
      fout << a[i].courses[j].subjectCode << ", " << a[i].courses[j].counts << " section(s)" << endl;
      cout << a[i].courses[j].subjectCode << ", " << a[i].courses[j].counts << " section(s)" << endl;
    }
    cout << endl;
  }

  cout << "Time taken: " << elapsedSeconds << "s" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 5b, Using A Data Structure As A Data Member\n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
