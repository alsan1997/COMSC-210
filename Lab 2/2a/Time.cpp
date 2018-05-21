// Lab 2a, Writing Overloading Operators
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Block

#include "Time.h"

// timeInHours function
float Time::timeInHours() const
{
  float timeHours;

  timeHours =  (minute / 60) + (second / 3600) + hour;

  return timeHours;
}

// timeInSeconds function
float Time::timeInSeconds() const
{
  float timeSeconds;

  float hours = hour * 3600;
  float mins = minute * 60;

  timeSeconds = hours + mins + second;
  return timeSeconds;
}

// timeInSeconds function
float Time::timeInMinutes() const
{
  float timeMinutes;

  float hours = hour * 60;
  float secs = second / 60;

  timeMinutes = hours + minute + secs;
  return timeMinutes;
}

bool Time::operator<(const Time& b) const
{
  if(timeInSeconds() < b.timeInSeconds()) return true;

  return false;
}

bool Time::operator==(const Time& b) const
{
  if(timeInSeconds() == b.timeInSeconds()) return true;

  return false;
}

