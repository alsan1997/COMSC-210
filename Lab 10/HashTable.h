// Lab 10a, Write, Test, and Apply The HashTable Class Template
// Programmer: Aldo Sanjoto
// Editor(s) used: Code::Blocks
// Compiler(s) used: Code::Blocks

#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <list> // for the list itself
#include <algorithm> // for searching the list
#include <vector>
using namespace std;

template <class T, class U, int CAPACITY>
class HashTable
{
  private:
    struct Node
    {
      T value;
      U key;
      void operator=(const T& v){value = v;}
      bool operator==(const Node& n) const {return key == n.key;}
    };

    int siz;
    T dummy;
    list<Node> data[CAPACITY]; // an array of N empty lists a data member
    int getWrappedIndex(const U&) const;
    int(*hashCode)(const U&); // as data member, "hashCode"
    // typename list<Node>::iterator it; // an uninitialized pointer to a Node in a list a local variable
    // int wi; // the wrapped index, in the range 0 to N-1 a local variable

  public:
    HashTable(int(*)(const U&)); // constructor
    T& operator[] (const U&); // operator setter
    T operator[] (const U&) const; // operator getter
    int size() const {return siz;} // size
    int capacity() const {return 0.8 * CAPACITY;} // return capacity using rule-of-thumb
    bool containsKey(const U&) const; // containsKey
    void deleteKey(const U&); // deleteKey
    void clear(); // clear
    vector<U> keys() const; // keys
};

template <class T, class U, int CAPACITY>
HashTable<T, U, CAPACITY>::HashTable(int (*hashcode)(const U& key))
{
  siz = 0;
  hashCode = hashcode;
}

template <class T, class U, int CAPACITY>
int HashTable<T, U, CAPACITY>::getWrappedIndex(const U& key) const
{
  // in getWrappedIndex:
  int wi = hashCode(key) % CAPACITY;

  if (wi < 0)
    wi = wi + CAPACITY;

  return wi;
}

template <class T, class U, int CAPACITY>
T& HashTable<T, U, CAPACITY>::operator[](const U& key)
{
  int wi = getWrappedIndex(key);
  typename list<Node>::iterator it;
  Node temp; temp.key = key; // do NOT set temp.value
  it = find(data[wi].begin(), data[wi].end(), temp);

  if(it == data[wi].end())
  {
    data[wi].push_back(temp);
    siz++;
    return data[wi].back().value;
  }
  else
    return it->value;
}

template <class T, class U, int CAPACITY>
T HashTable<T, U, CAPACITY>::operator[](const U& key) const
{
  int wi = getWrappedIndex(hashCode(key));
  typename list<Node>::const_iterator it;
  Node temp; temp.key = key; // do NOT set temp.value
  it = find(data[wi].begin(), data[wi].end(), temp);

  // if else diff.
  if (it == data[wi].end())
    return dummy;
  else if (it->key == key)
    return it->value;
  else
    return dummy;
}

template <class T, class U, int CAPACITY>
bool HashTable<T, U, CAPACITY>::containsKey(const U& key) const
{
  int wi = getWrappedIndex(key);
  typename list<Node>::const_iterator it;
  Node temp; temp.key = key; // do NOT set temp.value
  it = find(data[wi].begin(), data[wi].end(), temp);

  if (it == data[wi].end())
    return false;
  else
    return true;
}

template <class T, class U, int CAPACITY>
void HashTable<T, U, CAPACITY>::deleteKey(const U& key)
{
  int wi = getWrappedIndex(hashCode(key));
  typename list<Node>::iterator it;
  Node temp; temp.key = key; // do NOT set temp.value
  it = find(data[wi].begin(), data[wi].end(), temp);

  if(it == data[wi].end())
    return;

  if(it->key == key)
  {
    data[wi].erase(it);
    siz--;
  }
}

template <class T, class U, int CAPACITY>
void HashTable<T, U, CAPACITY>::clear()
{
  for(int i = 0; i < CAPACITY; i++)
    data[i].clear();

  siz = 0;
}

template <class T, class U, int CAPACITY> // return a vector of all the keys
vector<U> HashTable<T, U, CAPACITY>::keys() const
{
  vector<U> result;
  typename list<Node>::const_iterator it;

  for(int i = 0; i < CAPACITY; i++)
  {
    for(it = data[i].begin(); it != data[i].end(); it++)
      result.push_back(it->key);
  }

  return result;
}

#endif // HASHTABLE_H_INCLUDED
