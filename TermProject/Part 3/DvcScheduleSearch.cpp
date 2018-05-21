// Term Project, REQUIREMENTS (Part 3 of 3)
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <algorithm>
#include <cstring>
#include <ctime>
#include <vector>
#include <map>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  // for parsing the inputfile
  char* token;
  char buf[1000];
  const char* const tab = "\t";

  map<string, pair<string, int> > Subject;
  pair<string, int> data;
  string userSearch;

  // open the input file
  ifstream fin;
  fin.open("dvc-schedule.txt");
  if (!fin.good()) throw "I/O error";

  // read the input file
  while(!fin.eof())
  {
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

    // semester and year
    const string semester(term.begin(), term.begin() + term.find(' '));
    const string yearInString(term.begin() + term.find(' '), term.end());
    int year = atoi(yearInString.c_str());

    data.first = semester;
    data.second = year;

    if(Subject[course].first.empty()) Subject[course] = data;
    if(year > Subject[course].second) swap(Subject[course], data);
    if(year == Subject[course].second && semester == "Fall") swap(Subject[course], data);
    if(year == Subject[course].second && semester == "Summer" && Subject[course].first == "Spring")
      swap(Subject[course], data);
  }
  fin.close(); // close file

  map<string, pair<string, int> >:: iterator it1;
  while(true)
  {
    cout << "Please enter Q to quit" << endl;
    cout << "Please enter course to see when it's last offered (ex: COMSC-210): ";
    getline(cin, userSearch);

    if(userSearch == "Q" || userSearch == "q") break;

    it1 = Subject.find(userSearch);
    if(it1 != Subject.end())
      cout << it1->first << " was last offered in " << it1->second.first << " " << it1->second.second << endl;
    else
      cout << "The course you entered was not found and has not been offered since 2000\n\n";

    cout << endl;
  }
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Term Project, REQUIREMENTS (Part 3 of 3) \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
