// Lab 12, Write A Customer Service Simulation
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#include <iostream>
using namespace std;

#include <vector>
#include <queue>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Customer
{
  int arrivalTime; // the clock time that the customer arrives to be placed in the wait queue
  int servStartTime;  // the clock time that the customer's service starts
  int servEndTime; // the clock time that the customer's service ends
  char IDtag;
};

struct ServiceEvent
{
  int eventClockTime;
  int serverNumber;
  bool operator<(const ServiceEvent&) const;
};

bool ServiceEvent::operator<(const ServiceEvent& a) const
{
  return(eventClockTime > a.eventClockTime);
}

// requires cmath and cstdlib (and srand and rand to seed the random number generator)
int getRandomNumberOfServiceRequests(double averageRequestsPerTimeStep)
{
  int requests = 0;
  double probOfnRequests = exp(-averageRequestsPerTimeStep);
  for (double randomValue = (double)rand() / RAND_MAX;
    (randomValue -= probOfnRequests) > 0.0;
    probOfnRequests *= averageRequestsPerTimeStep / (double)++requests);
  return requests;
}

int getRandomNumber(int max, int min)
{
  int randomNum = rand() % (max - min + 1) + min;
  return randomNum;
}

void outputMe();

int main()
{
  // call identifying output
  outputMe();

  srand(time(0)); rand();

  // the six data variables
  int numOfServer;
  double avgArrivalRate;
  int maxWaitQueue;
  int minServiceTime;
  int maxServiceTime;
  int stopOfArrivalTime;

  double avgServiceTime;
  double numOfServingPerMin;
  double turnAwayTime;

  // additional variables
  int turnAwayCustomer = 0;
  int charCount = 0;

  // open the fjle
  ifstream fin;
  fin.open("simulation.txt");
  if(!fin.good())
    throw "I/O Error";

  // read the input values from a text file, one per line, in the order specified above.
  while(fin.good())
  {
    // read data
    fin >> numOfServer;
    fin >> avgArrivalRate;
    fin >> maxWaitQueue;
    fin >> minServiceTime;
    fin >> maxServiceTime;
    fin >> stopOfArrivalTime;
  }
  fin.close(); // close file

  avgServiceTime = (maxServiceTime + minServiceTime) / 2.0;
  numOfServingPerMin = numOfServer / avgServiceTime;
  turnAwayTime = avgArrivalRate - numOfServingPerMin;

  // output the summary
  cout << "number of servers: " << numOfServer << endl;
  cout << "customer arrival rate: " << avgArrivalRate << ", for " << stopOfArrivalTime << " minutes" << endl;
  cout << "maximum queue length: " << maxWaitQueue << endl;
  cout << "minimum service time: " << minServiceTime << endl;
  cout << "maximum service time: " << maxServiceTime << endl;

  cout.setf(ios::fixed|ios::showpoint);
  cout << setprecision(3);
  cout << "expected turn away rate: " << turnAwayTime << " per minute, while full" << endl << endl;

  // declare and create and assign arrays and queues to be used in the solution
  queue<Customer> waitQueue, servComplete, tempQueue;
  priority_queue<ServiceEvent> servEvent;
  vector<Customer> serverArray(numOfServer);
  vector<bool> serverArrayInUse(numOfServer);

  Customer dummy;
  dummy.IDtag = ' ';

  ServiceEvent tempSE;

  for(int i = 0; i < numOfServer; i++)
    serverArrayInUse[i] = false;

  // the clock time loop
  for (int time = 0;; time++) // the clock time
  {
    // handle all service events scheduled to complete at this clock time
    // while (event priority queue is not empty AND clock time of the top service event equals the current clock time)
    while(!servEvent.empty() && servEvent.top().eventClockTime == time)
    {
      // remove the top service event from the priority queue
      // determine the server associated with the removed service event
      tempSE = servEvent.top();
      servEvent.pop();

      // set this server's current customer's service end time to the current clock time
      serverArray[tempSE.serverNumber].servEndTime = time;

      // copy this server's current customer to the served customers queue
      servComplete.push(serverArray[tempSE.serverNumber]);
      serverArray[tempSE.serverNumber] = dummy;

      // set this server to idle
      serverArrayInUse[tempSE.serverNumber] = false;
    }

    // handle new arrivals -- can be turned away if wait queue is at maximum length!
    // if time is less than the time at which new arrivals stop
    if(time < stopOfArrivalTime)
    {
      // get the #of of arrivals from the Poisson process (a whole number >= 0) -- see the lecture topic notes!
      int numOfServiceRequest = getRandomNumberOfServiceRequests(avgArrivalRate);

      // for each new arrival
      for(int i = 0; i < numOfServiceRequest; i++)
      {
        // if the wait queue is full
        if(waitQueue.size() >= maxWaitQueue)
        {
          // "turn away the customer" by adding one to the count of turned away customers
          turnAwayCustomer++;
          break;
        }

        else // else
        {
          Customer tempC; // create a new customer object
          tempC.arrivalTime = time; // set its arrival time equal to the current clock time
          tempC.IDtag = (char)('A' + (charCount++ % 26)); // assign it an ID (A-Z)
          waitQueue.push(tempC); // copy the new customer to the wait queue
        }
      }
    }

    // for idle servers, move customer from wait queue and begin service
    // for each server
    for(int i = 0; i < numOfServer; i++)
    {
      // if (server is idle AND the wait queue is not empty)
      if(serverArrayInUse[i] == false && waitQueue.size() > 0)
      {
        // remove top customer from wait queue
        // copy it to the server array
        serverArray[i] = waitQueue.front();
        waitQueue.pop();

        // set the copied customer's service time to the current clock time
        serverArray[i].servStartTime = time;

        // use random number generation to determining the service time interval for the customer
        int serviceTimeInterval = getRandomNumber(maxServiceTime, minServiceTime);
        serverArrayInUse[i] = true;

        // create a new service event for the server, for the current clock time PLUS the service time interval
        tempSE.serverNumber = i;
        tempSE.eventClockTime = time + serviceTimeInterval;

        // add the service event to the event priority queue
        servEvent.push(tempSE);
      }
    }

    // output summary

    cout << "Time: " << time << endl; // output the current time

    // output a heading for the visual prepresentation of the servers and the wait queue
    cout << "------------------------" << endl;
    cout << "line   now serving   queue" << endl;
    cout << "----   -----------   -----" << endl;

    for(int i = 0; i < numOfServer; i++) // for each server
    {
      // output the server's index number (zero-based)
      cout << " " << i << "        ";

      // show the ID of the customer being served by that server (blank if idle)
      if(serverArrayInUse[i])
        cout << serverArray[i].IDtag;

      if(i == 0) // for server 0 only, show the IDs of customers in the wait queue
      {
        tempQueue = waitQueue;
        cout << "          ";
        for(int i = 0; i < waitQueue.size(); i++)
        {
          cout << tempQueue.front().IDtag;
          tempQueue.pop();
        }
      }
      cout << endl;
    }

    // summarize performance
    if(time > 0) // if time is greater than zero
    {
      tempQueue = servComplete;
      int timetotal = 0, siz = servComplete.size();

      // iterate over the served customers queue to get the average time between arrival and service end
      for(int i = 0; i < siz; i++)
      {
        timetotal += (tempQueue.front().servEndTime - tempQueue.front().servStartTime);
        tempQueue.pop();
      }

      // and if any, output the average of their "service end time" minus their "arrival time"
      // output the rate of customers turned away as total turned away divided by the current time
      cout << "Avg time: " << (double)timetotal / siz;
      cout << ". Turned away per minute: " << (double)turnAwayCustomer / time << endl;
    }

    // if the user wants to quit, break out of this loop
    cout << "Press ENTER to continue, X-ENTER to exit..." << endl;
    if(cin.get() == 'X') break;
  }
}

void outputMe()
{
  // print my name and this assignment's title
  cout << "Lab 12, Write A Customer Service Simulation\n";
  cout << "Programmer: Aldo Sanjoto\n";
  cout << "Editor(s) used: Code::Blocks\n";
  cout << "Compiler(s) used: Code::Blocks\n";
  cout << "File: " << __FILE__ << endl;
  cout << "Complied: " << __DATE__ << " at " << __TIME__ << endl << endl;
}
