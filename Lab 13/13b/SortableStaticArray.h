// Lab 13b, Applying A Data Structure To A Database Program
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef SORTABLESTATICARRAY_H_INCLUDED
#define SORTABLESTATICARRAY_H_INCLUDED

#include <vector>

template<class T, int CAPACITY>
class StaticArray
{
  private:
    T data[CAPACITY];
    bool inUse[CAPACITY];
    T dummy;

  public:
    StaticArray();
    T& operator[](int); // lookup key is an index
    T operator[](int) const;
    int size() const; // #of keys "in use", initially zero
    int capacity() const {return CAPACITY;}
    bool containsKey(int) const;
    void deleteKey(int); // set "in use" to false
    vector<int> keys() const; // all "in use" keys
    void clear();
    void sort();
};

template<class T, int CAPACITY>
StaticArray<T, CAPACITY>::StaticArray()
{
  for(int i = 0; i < CAPACITY; i++)
    inUse[i] = false;
}

template<class T, int CAPACITY>
T& StaticArray<T, CAPACITY>::operator[](int index)
{
  if(index < 0) return dummy;
  if(index >= CAPACITY) return dummy;

  inUse[index] = true;

  return data[index];
}

template<class T, int CAPACITY>
T StaticArray<T, CAPACITY>::operator[](int index) const
{
  if(index < 0) return dummy;
  if(index >= CAPACITY) return dummy;

  return data[index];
}

template<class T, int CAPACITY>
int StaticArray<T, CAPACITY>::size() const // #of keys "in use", initially zero
{
  int inc = 0;

  for(int i = 0; i < capacity(); i++)
  {
    if(inUse[i] == true)
      inc++;
  }

  return inc;
}

template<class T, int CAPACITY>
bool StaticArray<T, CAPACITY>::containsKey(int index) const
{
  if(index < 0) return false;
  if(index >= CAPACITY) return false;

  return inUse[index];
}

template<class T, int CAPACITY>
void StaticArray<T, CAPACITY>::deleteKey(int index) // set "in use" to false
{
  if(index < 0) return;
  if(index >= CAPACITY) return;

  inUse[index] = false;
}

template<class T, int CAPACITY>
vector<int> StaticArray<T, CAPACITY>::keys() const // all "in use" keys
{
  vector<int> v;

  for(int i = 0; i < CAPACITY; i++)
  {
    if(inUse[i])
      v.push_back(i);
  }

  return v;
}

template<class T, int CAPACITY>
void StaticArray<T, CAPACITY>::clear()
{
  for(int i = 0; i < capacity(); i++)
    inUse[i] = false;
}

template <class T, int CAPACITY>
void StaticArray<T, CAPACITY>::sort()
{
  int i, j;

  for (i = 0; i < CAPACITY; i++) // stop at n
  {
    if (!inUse[i]) continue; // in case of holes
    for (j = i + 1; j < CAPACITY; j++)
    {
      if (!inUse[j]) continue; // in case of holes
      if (data[j] < data[i]) // for LO-to-HI sorting
      {
        T temp = data[i];
        data[i] = data[j];
        data[j] = temp;
      }
    }
  }
}

#endif // SORTABLESTATICARRAY_H_INCLUDED
