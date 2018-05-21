// Lab 6a, Write A Linked Array Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef LINKEDARRAY_H_INCLUDED
#define LINKEDARRAY_H_INCLUDED

#include <vector>
using namespace std;

template <class T>
class LinkedArray
{
  private:
    struct Node
    {
      T value;
      bool inUse;
      Node* next;
    };

    Node* start;
    Node* end;
    int cap; // avoid name conflict with "int capacity() const"
    int siz;
    static const int INIT_CAP = 100; // initial capacity
    T dummy;

  public:
    LinkedArray(int c = INIT_CAP); // default constructor
    T& operator[](int); // lookup key is an index
    T operator[](int) const;
    int size() const {return siz;} // #of keys "in use", initially zero
    int capacity() const {return cap;}
    bool containsKey(int) const;
    void deleteKey(int); // set "in use" to false
    vector<int> keys() const; // all "in use" keys
    void clear();
    ~LinkedArray(); // destructor
    LinkedArray(const LinkedArray<T>&); // copy constructor
    LinkedArray<T>& operator=(const LinkedArray<T>&); // assignment operator
};

template<class T>
LinkedArray<T>::LinkedArray(int init_cap)
{
  cap = init_cap;
  start = 0;
  end = 0;
  siz = 0;

  for(int i = 0; i < cap; i++)
  {
    Node* node = new Node;
    node->inUse = false;
    node->next = 0;
    if(end) end->next = node;
    else start = node;
    end = node;
  }
}

// setter
template<class T>
T& LinkedArray<T>::operator[](int index)
{
  if(index < 0) return dummy;

  if(index >= cap)
  {
    for(int i = 0; i < index; i++)
    {
      Node* node = new Node;
      node->inUse = false;
      node->next = 0;
      if(end) end->next = node;
      else start = node;
      end = node;
    }

    cap = index + 1;
  }

  int counts = 0;
  Node* p;
  for(p = start; p; p = p->next, counts++)
  {
    if(index == counts) break;
  }

  if(p)
    if(!p->inUse)
    {
      p->inUse = true;
      siz++;
    }

  return p->value;
}

// getter
template<class T>
T LinkedArray<T>::operator[](int index) const
{
  if(index < 0) return dummy;
  if(index >= cap) return dummy;

  int counts = 0;
  Node* p;
  for(p = start; p; p = p->next, counts++)
  {
    if(index == counts)break;
  }

  if(p)
    return p->value;
}

template<class T>
bool LinkedArray<T>::containsKey(int index) const
{
  if(index < 0) return false;
  if(index >= cap) return false;

  // traverse to index node
  int counts = 0;
  Node* p;
  for(p = start; p; p = p->next, counts++)
  {
    if(index == counts) break;
  }

  return p->inUse;
}

template<class T>
void LinkedArray<T>::deleteKey(int index)
{
  if(index < 0) return;
  if(index >= cap) return;

  // traverse to index node
  int counts = 0;
  Node* p;
  for(p = start; p; p = p->next, counts++)
  {
    if(index == counts) break;
  }

  if(p->inUse) --siz;
  p->inUse = false;
}

template<class T>
vector<int> LinkedArray<T>::keys() const
{
  vector<int> v;

  int counts = 0;
  Node* p;
  for(p = start; p; p = p->next, counts++)
  {
    if(p->inUse)
      v.push_back(counts);
  }

  return v;
}

template<class T>
void LinkedArray<T>::clear()
{
  for (Node* p = start; p; p = p->next)
    p->inUse = false;
  siz = 0;
}

template<class T>
LinkedArray<T>::~LinkedArray()
{
  while(start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }

  end = 0;
}

template<class T>
LinkedArray<T>::LinkedArray(const LinkedArray<T>& a)
{
  cap = a.cap;
  siz = a.siz;
  start = end = 0;

  for(Node* p = a.start; p; p = p->next)
  {
    Node* node = new Node;
    node->next = 0;
    if(end)
      end->next = node;
    else
      start = node;
    end = node;
    node->value = p->value;
    node->inUse = p->inUse;
  }
}

template <class T>
LinkedArray<T>& LinkedArray<T>::operator=(const LinkedArray<T>& a)
{
  if (this == &a) return *this;

  // same as destructor code block
   while(start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }
  end = 0;

  // same as copy constructor code blocks
  cap = a.cap;
  siz = a.siz;

  start = end = 0;

  for(Node* p = a.start; p; p = p->next)
  {
    Node* node = new Node;
    node->next = 0;
    if(end)
      end->next = node;
    else
      start = node;
    end = node;
    node->value = p->value;
    node->inUse = p->inUse;
  }
  return *this;
}

#endif // DYNAMICARRAY_H_INCLUDED
