// Lab 4a, Write A Dynamic Array Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef DYNAMICARRAY_H_INCLUDED
#define DYNAMICARRAY_H_INCLUDED

#include <vector>
using namespace std;

template <class T>
class DynamicArray
{
  private:
    static const int INIT_CAP = 100; // initial capacity
    int cap; // avoid name conflict with "int capacity() const"
    T* values; // allocated in constructor
    bool* inUse; // allocated in constructor & set to false
    T dummy;

  public:
    DynamicArray(int c = INIT_CAP); // default constructor
    T& operator[](int); // lookup key is an index
    T operator[](int) const;
    int size() const; // #of keys "in use", initially zero
    int capacity() const {return cap;}
    bool containsKey(int) const;
    void deleteKey(int); // set "in use" to false
    vector<int> keys() const; // all "in use" keys
    void clear();
    ~DynamicArray(); // destructor
    DynamicArray(const DynamicArray<T>&); // copy constructor
    DynamicArray<T>& operator=(const DynamicArray<T>&); // assignment operator
};

template<class T>
DynamicArray<T>::DynamicArray(int init_cap)
{
  cap = init_cap;
  values = new T[cap];
  inUse = new bool[cap];

  for(int i = 0; i < cap; i++)
    inUse[i] = false;
}

template<class T>
T& DynamicArray<T>::operator[](int index)
{
  if(index < 0) return dummy;

  if(index >= cap)
  {
    T* tempValues = new T[index + 1];
    for(int i = 0; i < cap; i++)
      tempValues[i] = values[i];
    delete[] values;
    values = tempValues;

    bool* tempInUse = new bool[index + 1];
    for(int i = 0; i < cap; i++)
      tempInUse[i] = inUse[i];
    for(int i = cap; i <= index; i++)
      tempInUse[i] = false;
    delete[] inUse;
    inUse = tempInUse;

    cap = index + 1;
  }

  inUse[index] = true;
  return values[index];
}

template<class T>
T DynamicArray<T>::operator[](int index) const
{
  if(index < 0) return dummy;
  if(index >= cap) return dummy;

  return values[index];
}

template<class T>
int DynamicArray<T>::size() const
{
  int inc = 0;

  for(int i = 0; i < capacity(); i++)
  {
    if(inUse[i] == true)
      inc++;
  }

  return inc;
}

template<class T>
bool DynamicArray<T>::containsKey(int index) const
{
  if(index < 0) return false;
  if(index >= capacity()) return false;

  return inUse[index];
}

template<class T>
void DynamicArray<T>::deleteKey(int index)
{
  if(index < 0) return;
  if(index >= capacity()) return;

  inUse[index] = false;
}

template<class T>
vector<int> DynamicArray<T>::keys() const
{
  vector<int> v;

  for(int i = 0; i < capacity(); i++)
  {
    if(inUse[i])
      v.push_back(i);
  }

  return v;
}

template<class T>
void DynamicArray<T>::clear()
{
  for(int i = 0; i < capacity(); i++)
    inUse[i] = false;
}

template<class T>
DynamicArray<T>::~DynamicArray()
{
  delete[] values;
  delete[] inUse;
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& a)
{
  cap = a.cap;
  values = new T[cap];
  inUse = new bool[cap];

  for(int i = 0; i < cap; i++)
  {
    values[i] = a.values[i];
    inUse[i] = a.inUse[i];
  }
}

template <class T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& a)
{
  if (this == &a) return *this;

  // same as destructor code block
  delete[] values;
  delete[] inUse;

  // same as copy constructor code blocks
  cap = a.cap;
  values = new T[cap];
  inUse = new bool[cap];

  for(int i = 0; i < cap; i++)
  {
    values[i] = a.values[i];
    inUse[i] = a.inUse[i];
  }

  return *this;
}

#endif // DYNAMICARRAY_H_INCLUDED
