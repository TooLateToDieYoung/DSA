#ifndef _RECURSIVEDOUBLELINKEDLIST_H_
#define _RECURSIVEDOUBLELINKEDLIST_H_

#include <cstddef>
#include <iostream>

// ! Cannot place template class implementation in *.cpp
// ! It must be implemented in the same file in *.h

// ? Main class delcaration
template <class T>
class RecursiveDoubleLinkedList
{
  private: // ! Make it private to not be visible outside
    class Node; // ? Forward declaration on subclass to serve the class
  
  public: // ? Constructor & Destructor
    RecursiveDoubleLinkedList(void) : head{nullptr}, tail{nullptr} { }
    virtual ~RecursiveDoubleLinkedList(void);

  public: // ? func
    RecursiveDoubleLinkedList * const PrintList(void);
    RecursiveDoubleLinkedList * const Insert(T data, std::size_t seat = 0);
    RecursiveDoubleLinkedList * const Remove(std::size_t seat);
    RecursiveDoubleLinkedList * const Reverse(void);
    RecursiveDoubleLinkedList * const Replace(T data, std::size_t seat);
    std::size_t Length(void) const;

  private: // ? func
    Node * const FindNodeFromHead(Node * curr, std::size_t offset, const std::size_t& seat);
    Node * const FindNodeFromTail(Node * curr, std::size_t offset, const std::size_t& seat);

  private: // ? var
    Node * head {nullptr};
    Node * tail {nullptr};
};

// ? Subclass entity declaration
template <class T>
class RecursiveDoubleLinkedList<T>::Node
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
RecursiveDoubleLinkedList<T>::~RecursiveDoubleLinkedList(void)
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
RecursiveDoubleLinkedList<T> * const RecursiveDoubleLinkedList<T>::PrintList(void)
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
RecursiveDoubleLinkedList<T> * const RecursiveDoubleLinkedList<T>::Insert(T data, std::size_t seat)
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

  Node * const curr { 
    ( seat < length / 2 ) ?
    FindNodeFromHead(this->head, 0,          seat) :
    FindNodeFromTail(this->tail, length - 1, seat) 
  } ;

  node->prev = curr->prev;
  node->prev->rear = node;
  node->rear = curr;
  node->rear->prev = node;

  return this;
}

template <class T>
RecursiveDoubleLinkedList<T> * const RecursiveDoubleLinkedList<T>::Remove(std::size_t seat)
{
  if( this->head == nullptr ) return this;
  
  if( this->head == this->tail ) {
    if( seat == 0 ) {
      Node * const curr { this->head } ;
      this->head = nullptr;
      this->tail = nullptr;
      delete curr;
    }
    return this;
  }

  if( seat == 0 ) {
    Node * const curr { this->head } ;
    this->head       = this->head->rear;
    this->head->prev = nullptr;
    delete curr;
    return this;
  }

  std::size_t length { Length() } ;

  if( seat >= length ) return this;

  if( seat == length - 1 ) {
    Node * const curr { this->tail } ;
    this->tail       = this->tail->prev;
    this->tail->rear = nullptr;
    delete curr;
    return this;
  }

  Node * const curr { 
    ( seat < length / 2 ) ?
    FindNodeFromHead(this->head, 0,          seat) :
    FindNodeFromTail(this->tail, length - 1, seat) 
  } ;
                                 // p <-> t <-> r
  curr->prev->rear = curr->rear; // p <-  t <-> r, p  -> r
  curr->rear->prev = curr->prev; // p <-  t  -> r, p <-> r
  delete curr;
  return this;
}

template <class T>
RecursiveDoubleLinkedList<T> * const RecursiveDoubleLinkedList<T>::Reverse(void)
{
  if( this->head == nullptr ) return this;

  Node * temp { nullptr } ;

  // ? Recursively reverse
  auto turnAround = [&](auto&& lambda, Node * const curr) {
    temp        = curr->prev;
    curr->prev  = curr->rear;
    curr->rear  = temp;
    if( curr->prev == nullptr ) return curr;
    return lambda(lambda, curr->prev);
  };

  this->tail = this->head;
  this->head = turnAround(turnAround, this->head);

  return this;
}

template <class T>
RecursiveDoubleLinkedList<T> * const RecursiveDoubleLinkedList<T>::Replace(T data, std::size_t seat)
{
  if( this->head == nullptr ) return this;

  const std::size_t length { Length() } ;

  if( seat >= length ) return this;

  Node * const curr { 
    ( seat < length / 2 ) ?
    FindNodeFromHead(this->head, 0,          seat) :
    FindNodeFromTail(this->tail, length - 1, seat) 
  } ;

  curr->data = data;

  return this;
}

template <class T>
std::size_t RecursiveDoubleLinkedList<T>::Length(void) const
{
  auto computeLength = [&](auto&& lambda, Node * const curr, std::size_t counter) {
    if( curr == nullptr ) return counter;
    return lambda(lambda, curr->rear, counter + 1);
  };

  return computeLength(computeLength, this->head, 0);
}

template <class T>
RecursiveDoubleLinkedList<T>::Node * const RecursiveDoubleLinkedList<T>::FindNodeFromHead(Node * curr, std::size_t offset, const std::size_t& seat)
{
  return ( offset == seat ) ? ( curr ) : FindNodeFromHead(curr->rear, offset + 1, seat) ;
}

template <class T>
RecursiveDoubleLinkedList<T>::Node * const RecursiveDoubleLinkedList<T>::FindNodeFromTail(Node * curr, std::size_t offset, const std::size_t& seat)
{
  return ( offset == seat ) ? ( curr ) : FindNodeFromTail(curr->prev, offset - 1, seat) ;
}


// ? Subclass implementation
template <class T>
RecursiveDoubleLinkedList<T>::Node::Node(T data) : data{data}, prev{nullptr}, rear{nullptr} { }

#endif // _RECURSIVEDOUBLELINKEDLIST_H_