// Lab 2b, Writing Templates And Overloading Operators
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

template <class T>
class Road
{
  private:
    T width;
    T length;
  public:
    void setWidth(float w){width = w;}
    void setLength(float l){length = l;}
    float getWidth() const{return width;}
    float getLength() const{return length;}
    float asphalt(float thickness) const;
};

template<class T>
float Road<T>::asphalt(float thickness) const
{
  float volume;

  volume = width * (length*5280) * (thickness/12);

  return volume;
}

template<class T>
bool operator<(const Road<T>& a, const Road<T>& b)
{
  if(a.getLength() < b.getLength()) return true;

  return false;
}

template<class T>
bool operator==(const Road<T>& a, const Road<T>& b)
{
  if(a.getLength() == b.getLength() && a.getWidth() == b.getWidth()) return true;

  return false;
}

#endif // ROAD_H_INCLUDED
