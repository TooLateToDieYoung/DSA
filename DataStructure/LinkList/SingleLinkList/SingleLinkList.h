#ifndef _SINGLELINKLIST_H_
#define _SINGLELINKLIST_H_

#include <cstddef>
#include <iostream>

// ! Cannot place template class implementation in *.cpp
// ! It must be implemented in the same file in *.h

// ? Main class delcaration
template <class T>
class SingleLinkList 
{
  private: // ! Make it private to not be visible outside
    class Node; // ? Forward declaration on subclass to serve the class

  public: // ? Constructor & Destructor
    SingleLinkList(void) : first{nullptr} { }
    virtual ~SingleLinkList(void);

  public: // ? func
    SingleLinkList * const PrintList(void);
    SingleLinkList * const Insert(T data, std::size_t seat = 0);
    SingleLinkList * const Remove(std::size_t seat);
    SingleLinkList * const Reverse(void);
    SingleLinkList * const Replace(T data, std::size_t seat);

  private: // ? var
    Node * first  {nullptr};
};

// ? Subclass entity declaration
template <class T>
class SingleLinkList<T>::Node
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
SingleLinkList<T>::~SingleLinkList(void)
{
  std::cout << "**************************************************************" << std::endl;

  while( this->first ) {
    std::cout << "Address: " << this->first << ", Data: " << this->first->data << ", Next: " << this->first->next << std::endl;
    Remove(0);
  }

  std::cout << "**************************************************************" << std::endl;
}

template <class T>
SingleLinkList<T> * const SingleLinkList<T>::PrintList(void)
{
  std::cout << "--------------------------------------------------------------" << std::endl;

  Node * curr { this->first };
  while( curr != nullptr ) {
    std::cout << "Address: " << curr << ", Data: " << curr->data << ", Next: " << curr->next << std::endl;
    curr = curr->next;
  }

  std::cout << "--------------------------------------------------------------" << std::endl;

  return this;
}

template <class T>
SingleLinkList<T> * const SingleLinkList<T>::Insert(T data, std::size_t seat)
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
SingleLinkList<T> * const SingleLinkList<T>::Remove(std::size_t seat)
{
  // ? If is empty list
  if( this->first == nullptr ) return this;

  // ? If first seat is selected
  if( seat == 0 ) {
    Node * temp = this->first;
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

  Node * temp = front->next;
  front->next = temp->next;
  delete temp;
  return this;
}

template <class T>
SingleLinkList<T> * const SingleLinkList<T>::Reverse(void)
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
SingleLinkList<T> * const SingleLinkList<T>::Replace(T data, std::size_t seat)
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

// ? Subclass implementation
template <class T>
SingleLinkList<T>::Node::Node(T data) : data{data}, next{nullptr} { }

#endif // _SINGLELINKLIST_H_