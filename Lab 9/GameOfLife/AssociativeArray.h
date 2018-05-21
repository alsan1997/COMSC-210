// Lab 9, Write, Test, and Apply The AssociativeArray Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef ASSOCIATIVEARRAY_H_INCLUDED
#define ASSOCIATIVEARRAY_H_INCLUDED

#include <vector>
using namespace std;

template <class T, class U>
class AssociativeArray
{
  private:
    T* values;
    U* key;
    bool* inUse;
    static const int INIT_CAP = 100; // initial capacity
    T dummy;
    int siz;
    int cap;

  public:
    AssociativeArray(int c = INIT_CAP); // constructor
    T& operator[](const U&);
    T operator[](const U&) const;
    int size() const {return siz;}
    int capacity() const {return cap;}
    bool containsKey(const U&) const;
    void deleteKey(const U&);
    vector<U> keys() const;
    void clear();
    ~AssociativeArray();
    AssociativeArray(const AssociativeArray<T, U>&); // copy constructor
    AssociativeArray<T, U>& operator=(const AssociativeArray<T, U>&); // assignment operator
};

template <class T, class U>
AssociativeArray<T, U>::AssociativeArray(int init_cap) // constructor
{
  cap = init_cap;
  values = new T[cap];
  key = new U[cap];
  inUse = new bool[cap];
  siz = 0;

  for(int i = 0; i < cap; i++)
    inUse[i] = false;
}

template <class T, class U>
T& AssociativeArray<T, U>::operator[](const U& a)
{
  // for-loop to scan all data
  for(int i = 0; i < cap; i++)
    if(inUse[i] == true && key[i] == a) // if inUse[i] == true AND key[i] matches parameter
      return values[i]; // return mutable reference to value[i]

  // for-loop to scan all data
  for(int i = 0; i < cap; i++)
  {
    if(inUse[i] == false)// if inUse[i] == false
    {
      key[i] = a; // set key[i] to parameter
      inUse[i] = true; // set inUse[i] to true
      siz++;// add 1 to size
      return values[i]; // return value[i]
    }
  }

  int i = cap;  // set i = cap

  // double the array capacities
  T* tempValues = new T[cap * 2];
  for(int i = 0; i < cap; i++)
    tempValues[i] = values[i];
  delete[] values;
  values = tempValues;

  U* tempKey = new U[cap * 2];
  for(int i = 0; i < cap; i++)
    tempKey[i] = key[i];
  delete[] key;
  key = tempKey;

  bool* tempinUse = new bool[cap * 2];
  for(int i = 0; i < cap; i++)
    tempinUse[i] = inUse[i];
  delete[] inUse;
  inUse = tempinUse;

  key[i] = a; // set key[i] to parameter
  inUse[i] = true; // set inUse[i] to true
  siz++; // add 1 to size
  return values[i]; // return value[i]
}

template <class T, class U>
T AssociativeArray<T, U>::operator[](const U& a) const
{
  // for-loop to scan all data
  for(int i = 0; i < cap; i++)
   if(inUse[i] == true && key[i] == a) // if inUse[i] == true AND key[i] matches parameter
      return values[i]; // return value[i]

  return dummy;// return dummy
}

template <class T, class U>
bool AssociativeArray<T, U>::containsKey(const U& a) const
{
  for(int i = 0; i < cap; i++)
    if(key[i] == a)
      return inUse[i];
}

template <class T, class U>
void AssociativeArray<T, U>::deleteKey(const U& a)
{
  for(int i = 0; i < cap; i++)
  {
    if(key[i] == a)
    {
      inUse = false;
      --siz;
    }
  }
}

template <class T, class U>
vector<U> AssociativeArray<T, U>::keys() const
{
  vector<U> v;

  for(int i = 0; i < cap; i++)
  {
    if(inUse[i])
      v.push_back(i);
  }

  return v;
}

template <class T, class U>
void AssociativeArray<T, U>::clear()
{
  for(int i = 0; i < cap; i++)
    inUse[i] = false;

  siz = 0;
}

template <class T, class U>
AssociativeArray<T, U>::~AssociativeArray()
{
  delete[] values;
  delete[] inUse;
  delete[] key;
}

template <class T, class U>
AssociativeArray<T, U>::AssociativeArray(const AssociativeArray<T, U>& a) // copy constructor
{
  cap = a.cap;
  values = new T[cap];
  inUse = new bool[cap];
  key = new U[cap];

  for(int i = 0; i < cap; i++)
  {
    values[i] = a.values[i];
    inUse[i] = a.inUse[i];
    key[i] = a.key[i];
  }
}

template <class T, class U>
AssociativeArray<T, U>& AssociativeArray<T, U>::operator=(const AssociativeArray<T, U>& a) // assignment operator
{
  if (this == &a) return *this;

  delete[] values;
  delete[] inUse;
  delete[] key;

  cap = a.cap;
  values = new T[cap];
  inUse = new bool[cap];
  key = new U[cap];

  for(int i = 0; i < cap; i++)
  {
    values[i] = a.values[i];
    inUse[i] = a.inUse[i];
    key[i] = a.key[i];
  }

  return *this;
}

#endif // ASSOCIATIVEARRAY_H_INCLUDED
