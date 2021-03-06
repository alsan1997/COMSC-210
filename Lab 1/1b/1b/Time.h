// Lab 1b, Class Programming And Testing
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

class Time
{
  private:
    float hour;
    float minute;
    float second;
  public:
    void setHour(float h){hour = h;}
    void setMinute(float m){minute = m;}
    void setSecond(float s){second = s;}
    float timeInHours() const;
    float timeInSeconds() const;
    float timeInMinutes() const;
};


#endif // TIME_H_INCLUDED
