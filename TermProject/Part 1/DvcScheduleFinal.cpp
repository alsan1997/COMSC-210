// Term Project, REQUIREMENTS (Part 1 of 3)
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
#include <set>

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // for parsing the inputfile
  int n = 0;
  int duplicates = 0;
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  set<string> Duplicates;
  map<string, map<string, int> > Subject;

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

    if(Duplicates.find(term+section) != Duplicates.end())
    {
      duplicates++;
      continue;
    }

    else
      Duplicates.insert(term+section);

    Subject[subjectCode][course]++;
  }

  // close file
  fin.close();

  double elapsedSeconds = (double)(clock() - startTime) / CLOCKS_PER_SEC; // stop timer

  map<string, map<string,int> >::iterator it1;
  map<string, int>::iterator it2;
  for(it1 = Subject.begin(); it1 != Subject.end(); it1++)
  {
    cout << it1->first << ", " << it1->second.size() << " course(s)" << endl;
    for(it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
      cout << " " << it2->first << ", " << it2->second << " class(es)" << endl;
  }

  // output number of duplicates and time taken
  cout << "\nThere are " << duplicates << " duplicates data" << endl;
  cout << "Time taken: " << elapsedSeconds << "s" << endl;
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Term Project, REQUIREMENTS (Part 1 of 3) \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
