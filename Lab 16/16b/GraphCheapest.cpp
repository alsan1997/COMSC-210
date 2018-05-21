// Lab 16b: Write A Function For Cheapest Route
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

#include <cstdlib>

struct Vertex
{
  string name;

  bool isVisited;
  list<pair<int, double> > adjacentVertices;
  int prev;
  double cost;
};

struct Container // vertex container, for multiple ways to get to a vertex
{
  int vertex; // index in database array
  int prev; // index in database array
  double cost;

  bool operator<(const Container& v) const
  {
    return cost > v.cost;
  }
};

pair<stack<int>, double> getCheapestRoute(int iStart, int iEnd, vector<Vertex>& database)
{
  pair<stack<int>, double> result;
  list<pair<int, double> >::iterator it; // to iterate over adjacentVertices

  // TO DO -- write this function

  // reset the cost and previous indices for all vertices, isVisited to false
  for(int i = 0; i < database.size(); i++)
  {
    database[i].isVisited = false;
    database[i].cost = 0;
    database[i].prev = -1;
  }

  priority_queue<Container> containers; // create priority queue of Container objects

  // create a Container object for the start vertex, with 0 cost and negative prev index
  Container start;
  start.vertex = iStart;
  start.cost = 0;
  start.prev = -1;
  containers.push(start); // push the start vertex's container onto the priority queue

  while(!containers.empty()) // while the priority queue is not empty
  {
    // peek/pop a container object from the priority queue
    Container c = containers.top();
    containers.pop();

    if(database[c.vertex].isVisited == true) continue; // if contained object's been visited, "continue"

    database[c.vertex].isVisited = true; // mark contained object as visited
    database[c.vertex].cost = c.cost; // set its cost to that of its container
    database[c.vertex].prev = c.prev; // set its prev to that of its container

    if(c.vertex == iEnd) break; // if contained vertex is the end vertex, exit while-loop

    // for each of that vertex's unvisited neighbors
    for(it = database[c.vertex].adjacentVertices.begin(); it != database[c.vertex].adjacentVertices.end(); it++)
    {
      if(database[(*it).first].isVisited == false)
      {
        Container neighbor; // create a container object for neighbor
        neighbor.cost = (*it).second + c.cost; // set its cost to that of the vertex, plus edge cost
        neighbor.prev = c.vertex; // set its previous to the vertex
        neighbor.vertex = (*it).first; // push container onto priority queue
        containers.push(neighbor);
      }
    }
  }

  // the route's cost equals the end vertex's cost
  result.second = database[iEnd].cost;

  // build a stack of entries, starting from the end vertex, back towards the start
  for (int vertex = iEnd; vertex >= 0; vertex = database[vertex].prev)
    result.first.push(vertex);

  return result;
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
    string fromCity, toCity, cost;

    // read one edge
    getline(fin, fromCity);
    getline(fin, toCity);
    getline(fin, cost);
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
    double edgeCost = atof(cost.c_str());
    database[iFromVertex].adjacentVertices.push_back(pair<int, double>(iToVertex, edgeCost));
    database[iToVertex].adjacentVertices.push_back(pair<int, double>(iFromVertex, edgeCost));
  }
  fin.close();
  cout << "Input file processed\n\n";

  while (true)
  {
    string fromCity, toCity;
    cout << "\nEnter the source city [blank to exit]: ";
    getline(cin, fromCity);
    if (fromCity.length() == 0) break;

    // find the from city
    int iFrom;
    for (iFrom = 0; iFrom < database.size(); iFrom++)
      if (database[iFrom].name == fromCity)
        break;

    cout << "Enter the destination city [blank to exit]: ";
    getline(cin, toCity);
    if (toCity.length() == 0) break;

    // find the destination city
    int iTo;
    for (iTo = 0; iTo < database.size(); iTo++)
      if (database[iTo].name == toCity)
        break;

    // TO DO -- skip the next code block if no matching cites are found
    if(iFrom == database.size() || iTo == database.size()) continue;

    pair<stack<int>, double> result = getCheapestRoute(iFrom, iTo, database);
    cout << "Total miles: " << result.second;
    while (!result.first.empty()){cout << '-' << database[result.first.top()].name; result.first.pop();}

    cout << endl;
  }
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 16b: Write A Function For Cheapest Route \n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
