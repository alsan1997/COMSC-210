// Lab 7a, Write And Apply A Stack Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

template <class T>
class Stack
{
  private:
    struct Node
    {
      T value;
      Node* next;
    };
    Node* start; // no end needed
    int siz; // track size

  public:
    Stack(); // constructor
    void push(const T&);
    bool pop(T&);
    bool peek(T&) const;
    int size() const {return siz;} // inline
    bool empty() const {return 0 == siz;} // inline
    void clear();
    ~Stack(); // destructor
    Stack(const Stack<T>&); // copy constructor
    Stack<T>& operator=(const Stack<T>&); // operator= assignment function
};

template <class T>
Stack<T>::Stack()
{
  start = 0; // empty list
  siz = 0;
}

template <class T>
void Stack<T>::push(const T& a)
{
  Node* node = new Node;
  node->value = a;
  node->next = start;
  start = node;
  ++siz;
}

template <class T>
bool Stack<T>::peek(T& a) const
{
  if (0 == siz) return false; // failed
  a = start->value;
  return true; // success
}

template <class T>
bool Stack<T>::pop(T& a)
{
  if (0 == siz) return false; // failed
  a = start->value;
  Node* p = start->next;
  delete start;
  start = p;
  --siz;
  return true; // success
}

template <class T>
void Stack<T>::clear()
{
  while (start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }
  siz = 0;
}

template <class T>
Stack<T>::~Stack()
{
  while (start)
  {
    Node* p = start->next;
    delete start;
    start = p;
  }
}

template <class T>
Stack<T>::Stack(const Stack<T>& a)
{
  start = 0;
  Node* end = 0; // temporary end pointer
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
Stack<T>& Stack<T>::operator=(const Stack<T>& a)
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
  Node* end = 0; // temporary end pointer
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

#endif // STACK_H_INCLUDED
