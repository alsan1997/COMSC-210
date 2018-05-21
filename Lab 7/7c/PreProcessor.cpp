// Lab 7c, Use A Stack
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Block

#include <iostream>
using namespace std;

#include <fstream>
#include <cstring>
#include <stack>

struct Track
{
  int numLine;
  char sym;
};

void outputMe();

int main()
{
  outputMe();

  stack<Track> s;
  int linenumber = 0;
  bool isNotMatch = false;
  bool ignoringQuotes = false;
  bool ignoringStar = false;

  // prompt user
  string file;
  cout << "Enter filename (H, CPP, JAVA, HTML, or JS): ";
  getline(cin, file);

  // opening file
  ifstream fin;
  fin.open(file.c_str());
  if(!fin.good())
    throw "I/O Error";

  // read input file
  while(!fin.eof())
  {
    // read per line
    string line;
    getline(fin, line);
    int n = line.length();
    linenumber++;

    for(int i = 0; i < n; i++)
    {
      if(!ignoringStar)
      {
        if('\"' == line[i])
        {
          ignoringQuotes = !ignoringQuotes;
        }
      }

      if(ignoringQuotes) continue;

      // if slash slash
      if(line[i] == '/' && line[i+1] == '/' && i+1 < n) break;

      // if slash star
      if(line[i] == '/' && i+1 < n && line[i+1] == '*')
      {
        Track track;
        track.sym = '/';
        track.numLine = linenumber;
        s.push(track);
        ignoringStar = true;
      }

      // if star slash
      if(line[i] == '*' && i+1 < n && line[i+1] == '/')
      {
        ignoringStar = false;

        if(s.empty()) isNotMatch = true;

        else if(s.top().sym == '/') s.pop();

        else isNotMatch = true;

        if(isNotMatch)
        {
          cout << "Closing star slash found in line " << linenumber << " of " << file << endl;
          cout << "But no opening slash star found" << endl;
          break;
        }
      }

      if(ignoringStar) continue;

      // if open bracket append
      if(line[i] == '(')
      {
        Track track;
        track.numLine = linenumber;
        track.sym = line[i];
        s.push(track);
      }

      // if open curly brace
      if(line[i] == '{')
      {
        Track track;
        track.numLine = linenumber;
        track.sym = line[i];
        s.push(track);
      }

      // if open square bracket
      if(line[i] == '[')
      {
        Track track;
        track.numLine = linenumber;
        track.sym = line[i];
        s.push(track);
      }

      // if close bracket
      if(line[i] == ')')
      {
        if(s.empty()) isNotMatch = true;

        else if(s.top().sym == '(') s.pop();

        else isNotMatch = true;

        if(isNotMatch)
        {
          cout << "Closing curly brace found in line " << linenumber <<" of " << file << endl;
          cout << "But no opening curly brace found." << endl;
          break;
        }
      }

      // if close curly brace
      if(line[i] == '}')
      {
        if(s.empty()) isNotMatch = true;

        else if(s.top().sym == '{') s.pop();

        else isNotMatch = true;

        if(isNotMatch)
        {
          cout << "Closing parenthesis found in line " << linenumber <<" of " << file << endl;
          cout << "But no opening parenthesis found." << endl;
          break;
        }
      }

      // if close square bracket
      if(line[i] == ']')
      {
        if(s.empty()) isNotMatch = true;

        else if(s.top().sym == '[') s.pop();

        else isNotMatch = true;

        if(isNotMatch)
        {
          cout << "Closing square bracket found in line " << linenumber <<" of " << file << endl;
          cout << "But no opening square bracket found." << endl;
          break;
        }
      }
    }

    if(ignoringQuotes)
    {
      cout << "Opening quotes found in line " << linenumber << " of " << file << endl;
      cout << "But no matching closing quotes found" << endl;
      break;
    }
  }
  fin.close();

  if(ignoringStar)
  {
    cout << "Opening slash star found in line " << linenumber << " of " << file << endl;
    cout << "But no matching closing star slash" << endl;
  }

  if(!isNotMatch && !ignoringQuotes && !ignoringStar)
  {
    if(!s.empty())
    {
      if(s.top().sym == '(')
      {
        cout << "Opening parenthesis found in line " << s.top().numLine << " of " << file << endl;
        cout << "But no matching closing parenthesis found" << endl;
      }

      if(s.top().sym == '{')
      {
        cout << "Opening curly bracket found in line " << s.top().numLine << " of " << file << endl;
        cout << "But no matching opening curly bracket found" << endl;
      }

      if(s.top().sym == '[')
      {
        cout << "Opening square bracket found in line " << s.top().numLine << " of " << file << endl;
        cout << "But no matching closing bracket found" << endl;
      }
    }

    else
      cout << "No mismatches found by my preprocessor in " << file << endl;
  }
}

void outputMe()
{
  // Print my name and this assignment's title
  cout << "Lab 7c, Use A Stack \n";
  cout << "Programmer: Aldo Sanjoto " << endl;
  cout << "Editor(s) used: Code::Blocks \n";
  cout << "Compiler(s) used: Code::Blocks " << endl;
  cout << "File: " << __FILE__ << endl;
  cout << "Compiled: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
