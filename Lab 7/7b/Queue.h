// Lab 7b, Write And Test A Queue Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

template <class T>
class Queue
{
  private:
    struct Node
    {
      T value;
      Node* next;
    };
    Node* start;
    Node* end; // for efficiency
    int siz; // track size

  public:
    Queue(); // constructor
    void push(const T&);
    bool pop(T&);
    bool peek(T&) const;
    int size() const {return siz;} // inline
    bool empty() const {return 0 == start;}
    void clear();
    ~Queue(); // destructor
    Queue(const Queue<T>&); // copy constructor
    Queue<T>& operator=(const Queue<T>&); // operator= assignment function
};

template <class T>
Queue<T>::Queue()
{
  start = 0;
  end = 0;
  siz = 0;
}

template <class T>
void Queue<T>::push(const T& a)
{
  Node* node = new Node;
  node->value = a;
  node->next = 0;
  if (end) end->next = node;
  else start = node;
  end = node;
  ++siz;
}

template <class T>
bool Queue<T>::peek(T& a) const
{
  if (0 == start) return false; // failed
  a = start->value;
  return true; // success
}

template <class T>
bool Queue<T>::pop(T& a)
{
  if (0 == start) return false; // failed
  a = start->value;
  Node* p = start->next;
  delete start;
  start = p;
  if (start == 0) end = 0;
  --siz;
  return true; // success
}

template<class T>
void Queue<T>::clear()
{
  while (start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }
  end = 0;
  siz = 0;
}

template <class T>
Queue<T>::~Queue()
{
  while (start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }
}

template <class T>
Queue<T>::Queue(const Queue<T>& a)
{
  start = 0;
  end = 0;
  siz = a.siz;

  for (Node* p = a.start; p; p = p->next)
  {
    Node* node = new Node;
    node->value = p->value;
    node->next = 0;
    if (end) end->next = node;
    else start = node;
    end = node;
  }
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& a)
{
  if (this == &a) return *this;

  // deallocate existing queue
  while (start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }

  // build new queue
  end = 0; // data member end pointer
  for (Node* p = a.start; p; p = p->next)
  {
    Node* node = new Node;
    node->value = p->value;
    node->next = 0;
    if (end) end->next = node;
    else start = node;
    end = node;
  }
  siz = a.siz;

  return *this;
}

#endif // QUEUE_H_INCLUDED
