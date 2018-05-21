// Lab 15a, Breadth First Search, BFS
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
using namespace std;

struct Vertex
{
  string name;

  bool isVisited;
  list<int> adjacentVertices;
};

queue<int> doBreadthFirstSearch(int iOriginVertex, vector<Vertex>& database)
{
  // TO DO -- write this function

  // create an empty result queue to return at end of function call
  queue<int> searchOrder; // return this queue of indices
  queue<int> ToDoList; // create another queue to store the "to do list"

  // initialize each vertex in database: set to "not visited"
  for(int i = 0; i < database.size(); i++) database[i].isVisited = false;

  database[iOriginVertex].isVisited = true; // mark starting vertex as "visited"

  searchOrder.push(iOriginVertex); // push start vertex's index onto the result queue
  ToDoList.push(iOriginVertex); // push start vertex's index onto the "to do list"

  while(!ToDoList.empty()) // while the "to do list" is not empty
  {
    // peek/pop a vertex from the "to do list"
    int vertex = ToDoList.front();
    ToDoList.pop();

   // for each of that vertex's "neighbors"
   list<int>::iterator it;
   for(it = database[vertex].adjacentVertices.begin(); it != database[vertex].adjacentVertices.end(); it++)
   {
     // if neighbor has not yet been visited
     if(database[*it].isVisited == false)
     {
       database[*it].isVisited = true; // mark neighbor as visited
       searchOrder.push(*it); // push neighbor onto the result queue
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
    cout << "BFS";
    queue<int> q = doBreadthFirstSearch(i, database);
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
  cout << "Lab 15a, Breadth First Search, DFS \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
