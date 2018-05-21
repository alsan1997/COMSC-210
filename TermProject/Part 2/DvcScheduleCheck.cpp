// Term Project, REQUIREMENTS (Part 2 of 3)
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
#include <map>

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // for parsing the inputfile
  int n = 0;
  int invalid = 0;
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  map<string, string> compare;
  map<string, string> invalidData;

  clock_t startTime = clock(); // start timer

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

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

    string termSection = term + " Section: " + section;

    if(compare[termSection].empty()) compare[termSection] = course;
    else
    {
      if(compare[termSection] == course) continue;
      invalidData[termSection] = course;
      invalid++;
    }
  }
  fin.close(); // close file

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC; // stop timer

  map<string, string>::iterator it1;
  cout << "\nThere are " << invalid << " data of section number that repeats in the same term:" << endl;
  for(it1 = invalidData.begin(); it1 != invalidData.end(); it1++)
  {
    cout << it1->first << endl;
    cout << it1->second << " and " << compare[it1->first] << endl << endl;
  }

  if(invalidData.size() == 0)
    cout << "No repeating section is found" << endl;

  cout << "Time taken: " << elapsedSeconds << "s" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Term Project, REQUIREMENTS (Part 2 of 3) \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
