#ifndef _NORMALDOUBLELINKEDLIST_H_
#define _NORMALDOUBLELINKEDLIST_H_

#include <cstddef>
#include <iostream>

// ! Cannot place template class implementation in *.cpp
// ! It must be implemented in the same file in *.h

// ? Main class delcaration
template <class T>
class NormalDoubleLinkedList
{
  private: // ! Make it private to not be visible outside
    class Node; // ? Forward declaration on subclass to serve the class
  
  public: // ? Constructor & Destructor
    NormalDoubleLinkedList(void) : head{nullptr}, tail{nullptr} { }
    virtual ~NormalDoubleLinkedList(void);

  public: // ? func
    NormalDoubleLinkedList * const PrintList(void);
    NormalDoubleLinkedList * const Insert(T data, std::size_t seat = 0);
    NormalDoubleLinkedList * const Remove(std::size_t seat);
    NormalDoubleLinkedList * const Reverse(void);
    NormalDoubleLinkedList * const Replace(T data, std::size_t seat);
    std::size_t Length(void) const;

  private: // ? var
    Node * head {nullptr};
    Node * tail {nullptr};
};

// ? Subclass entity declaration
template <class T>
class NormalDoubleLinkedList<T>::Node
{
  public:
    Node(T data);
    Node(void) = delete;
    Node(const Node& copy) = delete;
    Node(Node&& move) = delete;
    ~Node(void) = default;
  
  public:
    T      data {0};
    Node * prev {nullptr};
    Node * rear {nullptr};
};

// ? Main class implementation
template <class T>
NormalDoubleLinkedList<T>::~NormalDoubleLinkedList(void)
{
  std::cout << "********************************************************************************" << std::endl;

  while( this->head != nullptr ) {
    std::cout 
      << "| Address: " << this->head 
      << ", Data: "    << this->head->data
      << ", prev: "    << this->head->prev
      << ", rear: "    << this->head->rear
      << " |"          << std::endl;
    Remove(0);
  }

  std::cout << "********************************************************************************" << std::endl;
}

template <class T>
NormalDoubleLinkedList<T> * const NormalDoubleLinkedList<T>::PrintList(void)
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;

  std::cout 
    << "* head: " << this->head << std::endl
    << "* tail: " << this->tail << std::endl;

  Node * curr { this->head };
  while( curr != nullptr ) {
    std::cout 
      << "| Address: " << curr 
      << ", Data: "    << curr->data 
      << ", prev: "    << curr->prev 
      << ", rear: "    << curr->rear 
      << " |"          << std::endl;
    curr = curr->rear;
  }

  std::cout << "----------------------------------------------------------------| Length: " << Length() << std::endl;

  return this;
}

template <class T>
NormalDoubleLinkedList<T> * const NormalDoubleLinkedList<T>::Insert(T data, std::size_t seat)
{
  Node * const node { new Node { data } } ;

  if( this->head == nullptr ) {
    this->head = node;
    this->tail = node;
    return this;
  }

  if( seat == 0 ) {
    node->rear       = this->head;
    node->rear->prev = node;
    this->head       = node;
    return this;
  }

  std::size_t length { Length() } ;

  if( seat >= length ) {
    node->prev       = this->tail;
    node->prev->rear = node;
    this->tail       = node;
    return this;
  }

  Node * curr { nullptr } ;

  // ? Find the target seat by checking if it is in the first half of the list
  if( seat < length / 2 ) {
    curr = this->head;
    for(std::size_t offset { 0 }; offset < seat; ++offset) curr = curr->rear;
  } 
  else {
    curr = this->tail;
    for(std::size_t offset { length - 1 }; offset > seat; --offset) curr = curr->prev;
  }

                                                       // n , p <-> c <-> r
  node->prev = curr->prev;                             // p <- n, p <-> c <-> r
  if( node->prev != nullptr ) node->prev->rear = node; // p <-> n, p <- c <-> r
  node->rear = curr;                                   // p <-> n -> c <-> r, p <- c <-> r
  if( node->rear != nullptr ) node->rear->prev = node; // p <-> n <-> c <-> r

  if( curr == this->head ) this->head = node;          // X = p <-> h = n <-> c <-> r

  return this;
}

template <class T>
NormalDoubleLinkedList<T> * const NormalDoubleLinkedList<T>::Remove(std::size_t seat)
{
  if( this->head == nullptr ) return this;

  const std::size_t length { Length() } ;

  if( seat >= length ) return this;

  if( length == 1 ) {
    Node * const curr { this->head } ;
    this->head = nullptr;
    this->tail = nullptr;
    delete curr;
    return this;
  }

  if( seat == 0 ) {
    Node * const curr { this->head } ;
    this->head       = this->head->rear;
    this->head->prev = nullptr;
    delete curr;
    return this;
  }

  if( seat == length - 1 ) {
    Node * const curr { this->tail } ;
    this->tail       = this->tail->prev;
    this->tail->rear = nullptr;
    delete curr;
    return this;
  }

  Node * curr { nullptr } ;
  if( seat < length / 2 ) {
    curr = this->head;
    for(std::size_t offset { 0 }; offset < seat; ++offset) curr = curr->rear;
  } 
  else {
    curr = this->tail;
    for(std::size_t offset { length - 1 }; offset > seat; --offset) curr = curr->prev;
  }

  curr->prev->rear = curr->rear; // p  -> r, p <-  c <-> r
  curr->rear->prev = curr->prev; // p <-> r, p <-  c  -> r
  delete curr;
  return this;
}

template <class T>
NormalDoubleLinkedList<T> * const NormalDoubleLinkedList<T>::Reverse(void)
{
  if( this->head == nullptr ) return this;

  Node * curr { this->head } ;
  Node * temp { nullptr } ;
  
  while( curr ) {
    temp = curr->prev;
    curr->prev = curr->rear;
    curr->rear = temp;
    curr = curr->prev;
  }

  temp = this->head;
  this->head = this->tail;
  this->tail = temp;

  return this;
}

template <class T>
NormalDoubleLinkedList<T> * const NormalDoubleLinkedList<T>::Replace(T data, std::size_t seat)
{
  if( this->head == nullptr ) return this;

  const std::size_t length { Length() } ;

  if( seat >= length ) return this;

  Node * curr { nullptr } ;
  if( seat < length / 2 ) {
    curr = this->head;
    for(std::size_t offset { 0 }; offset < seat; ++offset) curr = curr->rear;
  } 
  else {
    curr = this->tail;
    for(std::size_t offset { length - 1 }; offset > seat; --offset) curr = curr->prev;
  }

  curr->data = data;

  return this;
}

template <class T>
std::size_t NormalDoubleLinkedList<T>::Length(void) const
{
  std::size_t counter { 0 } ;
  Node *      curr    { this->head } ;

  while( curr ) {
    curr = curr->rear;
    counter++;
  }

  return counter;
}

// ? Subclass implementation
template <class T>
NormalDoubleLinkedList<T>::Node::Node(T data) : data{data}, prev{nullptr}, rear{nullptr} { }

#endif // _NORMALDOUBLELINKEDLIST_H_