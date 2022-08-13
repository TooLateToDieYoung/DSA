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

  private: // ? func
    Node * const FindTargetPreviousNode(Node * const curr, std::size_t offset, const std::size_t& seat);

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
    Node * rear {nullptr};
};

// ? Main class implementation
template <class T>
RecursiveSingleLinkedList<T>::~RecursiveSingleLinkedList(void)
{
  std::cout << "**************************************************************" << std::endl;

  while( this->first ) {
    std::cout << "Address: " << this->first << ", Data: " << this->first->data << ", Next: " << this->first->rear << std::endl;
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
    std::cout << "Address: " << curr << ", Data: " << curr->data << ", Next: " << curr->rear << std::endl;
    curr = curr->rear;
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
    node->rear = this->first;
    this->first = node;
    return this;
  }

  const std::size_t length { Length() } ;

  Node * const prev { 
    ( seat < length ) ?
    FindTargetPreviousNode(this->first, 0, seat  ) :
    FindTargetPreviousNode(this->first, 0, length) 
  } ;
                           // p -> r, n
  node->rear = prev->rear; // p -> r, n -> r
  prev->rear = node;       // p -> n -> r
  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Remove(std::size_t seat)
{
  // ? If is empty list
  if( this->first == nullptr ) return this;

  // ? If first seat is selected
  if( seat == 0 ) {
    Node * const curr { this->first } ;
    this->first = this->first->rear;
    delete curr;
    return this;
  } 

  const std::size_t length { Length() } ;

  if( seat >= length ) return this;

  // ? Recursively find the node before the deleted node
  Node * const prev { FindTargetPreviousNode(this->first, 0, seat) } ;
  Node * const curr { prev->rear } ;
  prev->rear = prev->rear->rear;
  delete curr;
  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Reverse(void)
{
  // ? Recursively reverse
  auto turnAround = [&](auto&& lambda, Node * const prev, Node * const curr) {
    if( curr == nullptr ) return prev;

    Node * const rear = curr->rear;
    curr->rear = prev;
    return lambda(lambda, curr, rear);
  };

  this->first = turnAround(turnAround, nullptr, this->first);

  return this;
}

template <class T>
RecursiveSingleLinkedList<T> * const RecursiveSingleLinkedList<T>::Replace(T data, std::size_t seat)
{
  if( this->first == nullptr ) return this;

  if( seat == 0 ) {
    this->first->data = data;
    return this;
  }

  const std::size_t length { Length() } ;

  if( seat >= length ) return this;

  // ? Recursively find the node before the deleted node
  FindTargetPreviousNode(this->first, 0, seat)->rear->data = data;

  return this;
}

template <class T>
std::size_t RecursiveSingleLinkedList<T>::Length(void) const
{
  auto computeLength = [&](auto&& lambda, Node * const curr, std::size_t counter) {
    if( curr == nullptr ) return counter;
    return lambda(lambda, curr->rear, counter + 1);
  };

  return computeLength(computeLength, this->first, 0);
}

template <class T>
RecursiveSingleLinkedList<T>::Node * const RecursiveSingleLinkedList<T>::FindTargetPreviousNode(Node * const curr, std::size_t offset, const std::size_t& seat)
{
  return ( offset == seat - 1 ) ? ( curr ) : FindTargetPreviousNode(curr->rear, offset + 1, seat) ;
}

// ? Subclass implementation
template <class T>
RecursiveSingleLinkedList<T>::Node::Node(T data) : data{data}, rear{nullptr} { }

#endif // _RECURSUVESINGLELINKEDLIST_H_