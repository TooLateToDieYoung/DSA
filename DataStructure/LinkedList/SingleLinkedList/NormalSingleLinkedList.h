#ifndef _NORMALSINGLELINKEDLIST_H_
#define _NORMALSINGLELINKEDLIST_H_

#include <cstddef>
#include <iostream>

// ! Cannot place template class implementation in *.cpp
// ! It must be implemented in the same file in *.h

// ? Main class delcaration
template <class T>
class NormalSingleLinkedList 
{
  private: // ! Make it private to not be visible outside
    class Node; // ? Forward declaration on subclass to serve the class

  public: // ? Constructor & Destructor
    NormalSingleLinkedList(void) : first{nullptr} { }
    virtual ~NormalSingleLinkedList(void);

  public: // ? func
    NormalSingleLinkedList * const PrintList(void);
    NormalSingleLinkedList * const Insert(T data, std::size_t seat = 0);
    NormalSingleLinkedList * const Remove(std::size_t seat);
    NormalSingleLinkedList * const Reverse(void);
    NormalSingleLinkedList * const Replace(T data, std::size_t seat);
    std::size_t Length(void) const;

  private: // ? func
    Node * const FindTargetPreviousNode(const std::size_t& seat) const;

  private: // ? var
    Node * first {nullptr};
};

// ? Subclass entity declaration
template <class T>
class NormalSingleLinkedList<T>::Node
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
NormalSingleLinkedList<T>::~NormalSingleLinkedList(void)
{
  std::cout << "**************************************************************" << std::endl;

  while( this->first ) {
    std::cout << "Address: " << this->first << ", Data: " << this->first->data << ", Next: " << this->first->rear << std::endl;
    Remove(0);
  }

  std::cout << "**************************************************************" << std::endl;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::PrintList(void)
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
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Insert(T data, std::size_t seat)
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

  Node * const prev { ( seat < length ) ? FindTargetPreviousNode(seat) : FindTargetPreviousNode(length) } ;
                           // p -> r, n
  node->rear = prev->rear; // p -> r, n -> r
  prev->rear = node;       // p -> n -> r
  return this;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Remove(std::size_t seat)
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

  // ? Find the node before the deleted node
  Node * const prev { FindTargetPreviousNode(seat) } ;
  Node * const curr { prev->rear } ;
  prev->rear = prev->rear->rear;
  delete curr;
  return this;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Reverse(void)
{
  Node * prev { nullptr     } ;
  Node * curr { this->first } ;
  Node * rear { curr->rear  } ;

  while( curr ) {
    rear = curr->rear;
    curr->rear = prev;
    prev = curr;
    curr = rear;
  }

  this->first = prev;

  return this;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Replace(T data, std::size_t seat)
{
  if( this->first == nullptr ) return this;

  if( seat == 0 ) {
    this->first->data = data;
    return this;
  }

  const std::size_t length { Length() } ;

  if( seat >= length ) return this;

  // ? Find the node before the deleted node
  FindTargetPreviousNode(seat)->rear->data = data;

  return this;
}

template <class T>
std::size_t NormalSingleLinkedList<T>::Length(void) const
{
  std::size_t counter { 0 } ;
  Node *      curr    { this->first } ;

  while( curr ) {
    curr = curr->rear;
    counter++;
  }

  return counter;
}

template <class T>
NormalSingleLinkedList<T>::Node * const NormalSingleLinkedList<T>::FindTargetPreviousNode(const std::size_t& seat) const
{
  Node * curr { this->first } ;
  for(std::size_t offset { 0 }; offset != seat - 1; ++offset) curr = curr->rear;

  return curr;
}


// ? Subclass implementation
template <class T>
NormalSingleLinkedList<T>::Node::Node(T data) : data{data}, rear{nullptr} { }

#endif // _NORMALSINGLELINKEDLIST_H_