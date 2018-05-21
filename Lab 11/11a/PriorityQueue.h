// Lab 11a, Write And Test A Priority Queue Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

template <class T>
class PriorityQueue
{
  private:
    T* value;
    int cap;
    int siz;

  public:
    PriorityQueue(int = 2); // constructor
    void enqueue(const T&); // enqueue
    T& front() {return value[0];} // front
    T& back() {return value[siz - 1];} // back
    T dequeue(); // dequeue
    bool empty() const {return siz == 0;} // empty
    void clear() {siz = 0;}// clear
    int size() const {return siz;} // size

    ~PriorityQueue(); // destructor
    PriorityQueue(const PriorityQueue<T>&); // copy constructor
    PriorityQueue<T>& operator=(const PriorityQueue<T>&); // assignment operator
};

template <class T>
PriorityQueue<T>::PriorityQueue(int init_cap) // constructor
{
  // initialize data member
  cap = init_cap;
  siz = 0;
  value = new T[cap];
}

template <class T>
void PriorityQueue<T>::enqueue(const T& newValue)
{
  int index = siz; // set index = size

  if(index >= cap) // if index >= capacity, double the capacity
  {
    T* tempValues = new T[cap * 2];
    for(int i = 0; i < cap; i++)
      tempValues[i] = value[i];
    delete[] value;
    value = tempValues;

    cap *= 2;
  }

  // copy new value into array at index
  value[index] = newValue;

  while(true) // start loop
  {
    int parentIndex = (index + 1)/2  - 1; // parentIndex = (index+1)/2 - 1

    if(parentIndex < 0) break; // if parentIndex < 0, exit loop
    if(value[parentIndex] >= value[index]) break; // if value at parentIndex >= value at index, exit loop
    swap(value[parentIndex], value[index]); // swap values at parentIndex and index
    index = parentIndex; // set index = parentIndex
  } // repeat to top of loop

  siz++; // increment size
}

template <class T>
T PriorityQueue<T>::dequeue() // dequeue
{
  int savedValue = value[0]; // save value at index 0 to return at end
  int index = 0; // set index to zero

  int indexLeftChild;
  int indexRightChild;

  while(true) // start loop
  {
    indexLeftChild = 2 * index + 1; // index of left child = 2*index+1
    indexRightChild = 2 * index + 2; // index of right child = 2*index+2

    if(indexLeftChild >= siz) break; // if left child index >= size, exit loop

    // if left child index = size-1
    // OR values of left child >= value of right child
    if(indexLeftChild == siz - 1 || value[indexLeftChild] >= value[indexRightChild])
    {
      value[index] = value[indexLeftChild]; // set value at index to value of left child
      index = indexLeftChild; // set index = index of left child
    }
    else // else
    {
      value[index] = value[indexRightChild]; // set value at index to value of right child
      index = indexRightChild;    // set index = index of right child
    }
  } // end loop

  siz--; // decrement size

  if(siz < cap / 4) // if size < capacity/4, halve the capacity
  {
    T* tempValues = new T[cap / 2];
    for(int i = 0; i < cap; i++)
      tempValues[i] = value[i];
    delete[] value;
    value = tempValues;

    cap = cap / 2;
  }

  value[index] = value[siz]; // copy value at size into array at index

  while(true) // start loop
  {
    int parentIndex = (index + 1)/2  - 1; // parentIndex = (index+1)/2 - 1

    if(parentIndex < 0) break; // if parentIndex < 0, exit loop
    if(value[parentIndex] >= value[index]) break; // if value at parentIndex >= value at index, exit loop
    swap(value[parentIndex], value[index]); // swap values at parentIndex and index
    index = parentIndex; // set index = parentIndex
  } // repeat to top of loop

  return savedValue; // return saved value
}

template <class T>
PriorityQueue<T>:: ~PriorityQueue() // destructor
{
  delete[] value;
}

template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& a) // copy constructor
{
  cap = a.cap;
  siz = a.siz;
  value = new T[cap];

  for(int i = 0; i < cap; i++)
    value[i] = a.value[i];
}

template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& a) // assignment operator11
{
  if (this == &a) return *this;

  delete[] value; // same as destructor code

  // same as copy constructor code
  cap = a.cap;
  siz = a.siz;
  value = new T[cap];

  for(int i = 0; i < cap; i++)
    value[i] = a.value[i];

  return *this;
}

#endif // PRIORITYQUEUE_H_INCLUDED
