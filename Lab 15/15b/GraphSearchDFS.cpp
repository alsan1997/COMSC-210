// Lab 15b, Breadth First Search, DFS
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

struct Vertex
{
  string name;

  bool isVisited;
  list<int> adjacentVertices;
};

queue<int> doDepthFirstSearch(int iOriginVertex, vector<Vertex>& database)
{
  // TO DO -- write this function
  queue<int> searchOrder; // create an empty result queue for returning at the end
  stack<int> ToDoList; // create a stack to store the "to do list"

  // initialize each vertex in database: set to "not visited"
  for(int i = 0; i < database.size(); i++) database[i].isVisited = false;

  ToDoList.push(iOriginVertex); // push start vertex's index onto the "to do list"

  while(!ToDoList.empty()) // while the "to do list" is not empty
  {
    // peek/pop a vertex from the "to do list"
    int vertex = ToDoList.top();
    ToDoList.pop();

    if(database[vertex].isVisited == false) // if that vertex has not yet been visited
    {
      database[vertex].isVisited = true; // mark the vertex as visited
      searchOrder.push(vertex); // push vertex onto the result queue

      // for each of that vertex's "neighbors" (in reverse order)
      list<int>::reverse_iterator it;
      for(it = database[vertex].adjacentVertices.rbegin(); it != database[vertex].adjacentVertices.rend(); it++)
      {
        if(database[*it].isVisited == false) // if neighbor has not yet been visited
          ToDoList.push(*it); // push neighbor onto the "to do list"
      }
    }
  }

  return searchOrder;
}

void outputMe();

int main()
{
  outputMe(); // call identifying output

  ifstream fin;
  fin.open("cities.txt");
  if (!fin.good()) throw "I/O error";

  // process the input file
  vector<Vertex> database;
  while (fin.good()) // EOF loop
  {
    string fromCity, toCity;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    fin.ignore(1000, 10); // skip the line with distance
    fin.ignore(1000, 10); // skip the separator

    // TO DO -- code to eliminate whitespace
    fromCity.erase(remove_if(fromCity.begin(), fromCity.end(), ::isspace), fromCity.end());
    toCity.erase(remove_if(toCity.begin(), toCity.end(), ::isspace), toCity.end());

    // add vertices for new cities included in the edge
    int iToVertex = -1, iFromVertex = -1, i;
    for (i = 0; i < database.size(); i++) // seek "to" city
      if (database[i].name == fromCity)
        break;
    if (i == database.size()) // not in database yet
    {
      // store the vertex if it is new
      Vertex fromVertex;
      fromVertex.name = fromCity;
      database.push_back(fromVertex);
    }
    iFromVertex = i;

    for (i = 0; i < database.size(); i++) // seek "from" city
      if (database[i].name == toCity)
        break;
    if (i == database.size()) // not in vector yet
    {
      // store the vertex if it is new
      Vertex toVertex;
      toVertex.name = toCity;
      database.push_back(toVertex);
    }
    iToVertex = i;

    // store bi-directional edges
    database[iFromVertex].adjacentVertices.push_back(iToVertex);
    database[iToVertex].adjacentVertices.push_back(iFromVertex);
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    // get the start city for the search
    string startCity;
    cout << "\nEnter the start city [blank to exit]: ";
    getline(cin, startCity);
    if (startCity.length() == 0) break;

    // find the start city
    int i;
    for (i = 0; i < database.size(); i++)
      if (database[i].name == startCity)
        break;

    // TO DO -- skip the next code blocks if no matching city is found
    if(i == database.size()) continue;

    // BFS result
    cout << "DFS";
    queue<int> q = doDepthFirstSearch(i, database);
    while(!q.empty())
    {
      cout  << '-'<< database[q.front()].name;
      q.pop();
    }
    cout << endl;
  }
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 15b, Depth First Search, DFS \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
