#ifndef _RECURSUVESINGLELINKEDLIST_H_
#define _RECURSUVESINGLELINKEDLIST_H_

#include <cstddef>
#include <iostream>

// ! Cannot place template class implementation in *.cpp
// ! It must be implemented in the same file in *.h

// ? Main class delcaration
template <class T>
class RecursiveSingleLinkedList 
{
  private: // ! Make it private to not be visible outside
    class Node; // ? Forward declaration on subclass to serve the class

  public: // ? Constructor & Destructor
    RecursiveSingleLinkedList(void) : first{nullptr} { }
    virtual ~RecursiveSingleLinkedList(void);

  public: // ? func
    RecursiveSingleLinkedList * const PrintList(void);
    RecursiveSingleLinkedList * const Insert(T data, std::size_t seat = 0);
    RecursiveSingleLinkedList * const Remove(std::size_t seat);
    RecursiveSingleLinkedList * const Reverse(void);
    RecursiveSingleLinkedList * const Replace(T data, std::size_t seat);
    std::size_t Length(void) const;

  private: // ? var
    Node * first {nullptr};
};

// ? Subclass entity declaration
template <class T>
class RecursiveSingleLinkedList<T>::Node
{
  public: // ? Constructor & Destructor
    Node(T data);                    // ? Serve to main class
    Node(void) = delete;             // ? Disable default constructor
    Node(const Node& copy) = delete; // ? Disable copy    constructor
    Node(Node&& move) = delete;      // ? Disable move    constructor
    ~Node(void) = default; 

  public: // ? var
    T      data {'\0'};
    Node * next {nullptr};
};

// ? Main class implementation
template <class T>
RecursiveSingleLinkedList<T>::~RecursiveSingleLinkedList(void)
{
  std::cout << "**************************************************************" << std::endl;

  while( this->first ) {
    std::cout << "Address: " << this->first << ", Data: " << this->first->data << ", Next: " << this->first->next << std::endl;
    Remove(0);
  }

  std::cout << "**************************************************************" << std::endl;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::PrintList(void)
{
  std::cout << "--------------------------------------------------------------" << std::endl;

  Node * curr { this->first };
  while( curr != nullptr ) {
    std::cout << "Address: " << curr << ", Data: " << curr->data << ", Next: " << curr->next << std::endl;
    curr = curr->next;
  }

  std::cout << "-------------------------------------------------| Length : " << Length() << std::endl;

  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Insert(T data, std::size_t seat)
{
  Node * const node = new Node { data } ;

  // ? If is empty list
  if( this->first == nullptr ) {
    this->first = node; 
    return this;
  }
  
  // ? If first seat is selected
  if( seat == 0 ) {
    node->next = this->first;
    this->first = node;
    return this;
  }

  // ? Recursively find the node before the inserted node
  auto findFront = [&](auto&& lambda, Node * const curr, std::size_t offset) {
    if( curr->next == nullptr ) return curr; // It is end of list
    if( offset == 0           ) return curr; // Found it
    return lambda(lambda, curr->next, offset - 1); // Recursive
  };

  Node * const front { findFront(findFront, this->first, seat - 1) } ;

  node->next = front->next;
  front->next = node;
  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Remove(std::size_t seat)
{
  // ? If is empty list
  if( this->first == nullptr ) return this;

  // ? If first seat is selected
  if( seat == 0 ) {
    Node * const temp = this->first;
    this->first = temp->next;
    delete temp;
    return this;
  } 

  // ? Recursively find the node before the deleted node
  auto findFront = [&](auto&& lambda, Node * const curr, std::size_t offset) {
    if( curr == nullptr ) return curr; // Haven't found
    if( offset == 0     ) return curr; // Found it
    return lambda(lambda, curr->next, offset - 1); // Recursive
  };

  // ? Recursively find the node before the deleted node
  Node * const front { findFront(findFront, this->first, seat - 1) } ;

  if( front == nullptr || front->next == nullptr ) return this; // check if it works

  Node * const temp = front->next;
  front->next = temp->next;
  delete temp;
  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Reverse(void)
{
  // ? Recursively reverse
  auto turnAround = [&](auto&& lambda, Node * const front, Node * const curr) {
    if( curr == nullptr ) return front;

    Node * const rear = curr->next;
    curr->next = front;
    return lambda(lambda, curr, rear);
  };

  this->first = turnAround(turnAround, nullptr, this->first);

  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Replace(T data, std::size_t seat)
{
  auto findTarget = [&](auto&& lambda, Node * const curr, std::size_t offset) {
    if( curr == nullptr ) return curr;
    if( offset == 0     ) return curr;
    return lambda(lambda, curr->next, offset - 1);
  };

  Node * const target { findTarget(findTarget, this->first, seat) } ;

  if( target != nullptr ) target->data = data;

  return this;
}

template <class T>
std::size_t RecursiveSingleLinkedList<T>::Length(void) const
{
  auto computeLength = [&](auto&& lambda, Node * const curr, std::size_t counter) {
    if( curr == nullptr ) return counter;
    return lambda(lambda, curr->next, counter + 1);
  };

  return computeLength(computeLength, this->first, 0);
}

// ? Subclass implementation
template <class T>
RecursiveSingleLinkedList<T>::Node::Node(T data) : data{data}, next{nullptr} { }

#endif // _RECURSUVESINGLELINKEDLIST_H_