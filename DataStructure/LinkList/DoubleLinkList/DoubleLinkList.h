#ifndef _DOUBLELINKLIST_H_
#define _DOUBLELINKLIST_H_

#include <cstddef>
#include <iostream>

// ! Cannot place template class implementation in *.cpp
// ! It must be implemented in the same file in *.h

// ? Main class delcaration
template <class T>
class DoubleLinkList
{
  private: // ! Make it private to not be visible outside
    class Node; // ? Forward declaration on subclass to serve the class
  
  public: // ? Constructor & Destructor
    DoubleLinkList(void) : head{nullptr}, tail{nullptr}, length{0} { }
    virtual ~DoubleLinkList(void);

  public: // ? func
    DoubleLinkList * const PrintList(void);
    DoubleLinkList * const Insert(T data, std::size_t seat = 0);
    DoubleLinkList * const Remove(std::size_t seat);
    DoubleLinkList * const Reverse(void);
    DoubleLinkList * const Replace(T data, std::size_t seat);

  public: // ? Getter & Setter
    std::size_t GetLength(void) { return this->length ; }

  private: // ? var
    Node *      head   {nullptr};
    Node *      tail   {nullptr};
    std::size_t length {0};
};

// ? Subclass entity declaration
template <class T>
class DoubleLinkList<T>::Node
{
  public:
    Node(T data);
    Node(void) = delete;
    Node(const Node& copy) = delete;
    Node(Node&& move) = delete;
    ~Node(void) = default;
  
  public:
    T      data  {0};
    Node * front {nullptr};
    Node * rear  {nullptr};
};

// ? Main class implementation
template <class T>
DoubleLinkList<T>::~DoubleLinkList(void)
{
  std::cout << "********************************************************************************" << std::endl;

  while( this->head != nullptr ) {
    std::cout 
      << "| Address: " << this->head 
      << ", Data: "    << this->head->data
      << ", front: "   << this->head->front
      << ", rear: "    << this->head->rear
      << " |"          << std::endl;
    Remove(0);
  }

  std::cout << "********************************************************************************" << std::endl;
}

template <class T>
DoubleLinkList<T> * const DoubleLinkList<T>::PrintList(void)
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;

  Node * curr { this->head };
  while( curr != nullptr ) {
    std::cout 
      << "| Address: " << curr 
      << ", Data: "    << curr->data 
      << ", front: "   << curr->front 
      << ", rear: "    << curr->rear 
      << " |"          << std::endl;
    curr = curr->rear;
  }

  std::cout << "--------------------------------------------------------------------------------" << std::endl;

  return this;
}

template <class T>
DoubleLinkList<T> * const DoubleLinkList<T>::Insert(T data, std::size_t seat)
{
  Node * const node { new Node { data } } ; this->length++;

  if( this->head == nullptr ) {
    this->head = node;
    return this;
  }

  if( seat == 0 ) {
    this->head->front = node;
    node->rear = this->head;
    this->head = node;
    return this;
  }

  auto findTarget = [&](auto&& lambda, Node * const curr, std::size_t offset) {
    if( curr->rear == nullptr ) return curr;
    if( offset == 0           ) return curr;
    return lambda(lambda, curr->rear, offset - 1);
  };

  Node * const target { findTarget(findTarget, this->head, seat) } ;

  node->front       = target->front;
  node->front->rear = node;
  node->rear        = target;
  target->front     = node;

  return this;
}

template <class T>
DoubleLinkList<T> * const DoubleLinkList<T>::Remove(std::size_t seat)
{
  if( this->head == nullptr ) return this;

  if( seat == 0 ) {
    Node * const target { this->head } ;
    this->head = target->rear;
    if( target->rear != nullptr ) this->head->front = nullptr;
    delete target;
    return this;
  }

  auto findTarget = [&](auto&& lambda, Node * const curr, std::size_t offset) {
    if( curr == nullptr ) return curr;
    if( offset == 0     ) return curr;
    return lambda(lambda, curr->rear, offset - 1);
  };

  Node * const target { findTarget(findTarget, this->head, seat) } ;
  if( target == nullptr ) return this;
  target->front->rear = target->rear;  // f->t->r => f->r
  if( target->rear != nullptr ) target->rear->front = target->front; // f<-t<-r => f<-r
  delete target;
  return this;
}

template <class T>
DoubleLinkList<T> * const DoubleLinkList<T>::Reverse(void)
{
  if( this->head == nullptr ) return this;

  Node * temp { nullptr } ;

  // ? Recursively reverse
  auto turnAround = [&](auto&& lambda, Node * const curr) {
    temp        = curr->front;
    curr->front = curr->rear;
    curr->rear  = temp;
    if( curr->front == nullptr ) return curr;
    return lambda(lambda, curr->front);
  };

  this->head = turnAround(turnAround, this->head);

  return this;
}

template <class T>
DoubleLinkList<T> * const DoubleLinkList<T>::Replace(T data, std::size_t seat)
{
  auto findTarget = [&](auto&& lambda, Node * const curr, std::size_t offset) {
    if( curr == nullptr ) return curr;
    if( offset == 0     ) return curr;
    return lambda(lambda, curr->rear, offset - 1);
  };

  Node * const target = findTarget(findTarget, this->head, seat);

  if( target != nullptr ) target->data = data;

  return this;
}

// ? Subclass implementation
template <class T>
DoubleLinkList<T>::Node::Node(T data) : data{data}, front{nullptr}, rear{nullptr} { }

#endif // _DOUBLELINKLIST_H_