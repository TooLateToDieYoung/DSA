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
    Node * next {nullptr};
};

// ? Main class implementation
template <class T>
NormalSingleLinkedList<T>::~NormalSingleLinkedList(void)
{
  std::cout << "**************************************************************" << std::endl;

  while( this->first ) {
    std::cout << "Address: " << this->first << ", Data: " << this->first->data << ", Next: " << this->first->next << std::endl;
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
    std::cout << "Address: " << curr << ", Data: " << curr->data << ", Next: " << curr->next << std::endl;
    curr = curr->next;
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
    node->next = this->first;
    this->first = node;
    return this;
  }

  // ? find the node before the inserted node
  Node * prev { this->first } ;

  for(std::size_t offset { seat - 1 }; offset; --offset) {
    if( prev->next == nullptr ) break;
    prev = prev->next;
  }

  /* It does the same thing but is a bit harder to read
  for(
    std::size_t offset { seat - 1 } ;
    ( prev->next != nullptr ) && ( offset != 0 ) ;
    prev = prev->next, --offset
  ) { }
  */

  node->next = prev->next;
  prev->next = node;
  return this;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Remove(std::size_t seat)
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

  // ? find the node before the deleted node
  Node * prev { this->first } ;

  for(std::size_t offset { seat - 1 }; offset; --offset) {
    if( prev->next == nullptr ) return this; // out of length
    prev = prev->next;
  }

  Node * const temp = prev->next;
  prev->next = temp->next;
  delete temp;
  return this;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Reverse(void)
{
  Node * prev { nullptr     } ;
  Node * curr { this->first } ;
  Node * rear { curr->next  } ;

  while( curr ) {
    rear = curr->next;
    curr->next = prev;
    prev = curr;
    curr = rear;
  }

  this->first = prev;

  return this;
}

template <class T>
NormalSingleLinkedList<T> * const NormalSingleLinkedList<T>::Replace(T data, std::size_t seat)
{
  Node * curr { this->first } ;

  for(std::size_t offset { seat }; offset; --offset) {
    if( curr == nullptr ) return this; // out of length
    curr = curr->next;
  }

  curr->data = data;

  return this;
}

template <class T>
std::size_t NormalSingleLinkedList<T>::Length(void) const
{
  std::size_t counter { 0 } ;
  Node *      curr    { this->first } ;

  while( curr ) {
    curr = curr->next;
    counter++;
  }

  return counter;
}

// ? Subclass implementation
template <class T>
NormalSingleLinkedList<T>::Node::Node(T data) : data{data}, next{nullptr} { }

#endif // _NORMALSINGLELINKEDLIST_H_