// Lab 14a,Write A Sortable Array Class Template
// Programmer: Axel Hugo
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Block


#ifndef SORTABLEDYNAMICARRAY_H_INCLUDED
#define SORTABLEDYNAMICARRAY_H_INCLUDED

#include<vector>
using namespace std;

template <class T>
class SortableDynamicArray
{
public:
  SortableDynamicArray(int c=INIT_CAP);
  T& operator[](int); // lookup key is an index
  T operator[](int) const;
  int size() const; // #of keys "in use", initially zero
  int capacity() const{return cap;}
  bool containsKey(int) const;
  void deleteKey(int); // set "in use" to false
  vector<int> keys() const; // all "in use" keys
  void clear();
  ~SortableDynamicArray();
  SortableDynamicArray(const SortableDynamicArray<T>&);
  SortableDynamicArray<T>& operator=(const SortableDynamicArray<T>&);


    void sort(int);
    int bsearch(int, const T&) const;

private:
  static const int INIT_CAP = 100;
  int cap;
  T* values;
  bool* inUse;
  T dummy;
};

template <class T>
void SortableDynamicArray<T>::sort(int n)
{

  T* temp = new T[n];
  for (int i = 1; i < n; i *= 2)
  {
    int index = 0;
    for (int j = 0; j < n; j++)
      temp[j] = values[j];


    for (int j = 0; j < n; j += 2 * i)
    {
      int left = j;
      int leftMax = min(left + i, n);
      int right = leftMax;
      int rightMax = min(right + i, n);
      while (true)
      {
        if (left == leftMax && right == rightMax) break;
        if (left == leftMax) values[index++] = temp[right++];
        else if (right == rightMax) values[index++] = temp[left++];
        else if (temp[right] < temp[left]) values[index++] = temp[right++];
        else values[index++] = temp[left++];
      }
    }
  }
  delete [] temp;
}

template<class T>
int SortableDynamicArray<T>::bsearch(int indexAfterLast, const T& value) const
{
  int start = 0;
  int end = indexAfterLast;

  while(true)
  {
    int mid = (start + end - 1) / 2;

    if (value == values[mid]) return mid;

    else if (start == end - 1) return -1;

    else if (value < values[mid])
    {
      if (start == mid) return -1;
      else {end = mid; continue;}
    }
    else
    {
      if (mid == end - 1) return -1;
      else {start = mid + 1; continue;}
    }
  }
}


// the "Default" Constructor
// to use as a "default parameter"
template <class T>
SortableDynamicArray<T>::SortableDynamicArray(int init_cap)
{
    cap = init_cap;
    values = new T[cap];
    inUse = new bool[cap];

    for (int i=0; i < cap ; i++)
        inUse[i] = false;
}

template <class T>
T SortableDynamicArray<T>::operator[](int index) const
{
  if(index < 0) return dummy;
  if(index >= cap) return dummy;

  return values[index];
}

//Increasing Capacity in
template <class T>
T& SortableDynamicArray<T>::operator[](int index)
{
    if(index < 0) return dummy;

    if(index >= cap)
    {
    T* tempValues = new T[index + 1];
    for (int i = 0; i < cap; i++)
        tempValues[i] = values[i];
    delete[] values;
    values = tempValues;

      bool* tempInUse = new bool[index + 1];
      for (int i = 0; i < cap; i++)
        tempInUse[i] = inUse[i];
      for (int i = cap; i <= index; i++)
         tempInUse[i] = false;
      delete [] inUse;
      inUse = tempInUse;

      cap = index + 1;
    }

    inUse[index] = true;
    return values[index];
}

template <class T>
int SortableDynamicArray<T>::size() const
{
  int inc=0;

  for(int i=0; i< cap; i++)
  {
    if(inUse[i]==true)
    inc++;
  }
  return inc;
}

template <class T>
bool SortableDynamicArray<T>::containsKey(int index) const
{
    if (index < 0) return false;
    if(index >= cap) return false;

    return inUse[index];
}

template <class T>
void SortableDynamicArray<T>::deleteKey(int index)
{
  if(index < 0) return;
  if(index >= cap) return;

  inUse[index] = false;
}

template <class T>
vector<int> SortableDynamicArray<T>::keys() const
{
    vector<int> v;
  for(int i = 0; i < cap; i++)
  {
    if(inUse[i])
      v.push_back(i);
  }
  return v;
}

template <class T>
void SortableDynamicArray<T>:: clear()
{
    for(int i = 0; i < cap; i++)
      inUse[i] = false;
}

//Templated Copy Constructor
//to allows copies to have their own arrays avoids conflicting destructors
template <class T>
SortableDynamicArray<T>::SortableDynamicArray(const SortableDynamicArray<T>& a)
{
  cap = a.cap;
  values = new T[cap];
  inUse = new bool[cap];

  for (int i=0; i < cap; i++)
  {
      values[i] = a.values[i];
      inUse[i] = a.inUse[i];
  }
}

//Templated Assignment Operator
//to allows copies to have their own arrays avoids conflicting destructors
template <class T>
SortableDynamicArray<T>& SortableDynamicArray<T>::operator=(const SortableDynamicArray<T>& a)
{
    if (this == &a) return *this;

    //same as destructor code block
    delete[] values;
    delete[] inUse;

    //same as copy constructor code block
      cap = a.cap;
  values = new T[cap];
  inUse = new bool[cap];

  for (int i=0; i < cap; i++)
  {
      values[i] = a.values[i];
      inUse[i] = a.inUse[i];
  }

  return *this;
}
//Templated Destructor
//to deallocate memory allocated in constructor
template <class T>
SortableDynamicArray<T>::~SortableDynamicArray()
{
    delete[] values;
    delete[] inUse;
}


#endif // SORTABLEDYNAMICARRAY_H_INCLUDED
