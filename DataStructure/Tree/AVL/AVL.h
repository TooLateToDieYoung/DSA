#ifndef _AVL_H_
#define _AVL_H_

#include <iostream>

template<class T>
class AVL
{
  private:
    class Node;

  public:
    explicit AVL(void) : root{nullptr} {}
    virtual ~AVL(void);
  
  public:
    std::size_t Height(void) const { return this->root->Height(); }
    std::size_t Size(void) const { return this->root->Size(); }
    void        PrintLevelorder(void) const;
    AVL * const Insert(T data);
    AVL * const Delete(T data);

  private:
    Node * root;
};

template<class T>
class AVL<T>::Node
{
  public:
    explicit Node(T data) : data{data}, L{nullptr}, R{nullptr} {}
    ~Node(void) = default;

  public:
    bool         isLeaf(void) const;
    std::size_t  Height(void) const;
    std::size_t  Size(void) const;
    Node * const RotationL(void);
    Node * const RotationR(void);
    Node * const Rebalance(void);

  public:
    T           data   { };
    Node *      L      { nullptr };
    Node *      R      { nullptr };
};

template<class T>
AVL<T>::~AVL(void) 
{
  std::cout << "~AVL() -----------------------------------------------------" << std::endl;
  while( this->root != nullptr ) {
    Delete(this->root->data);
    PrintLevelorder();
  }
}

template<class T>
AVL<T> * const AVL<T>::Insert(T data)
{
  auto FindPrev = [&](auto&& lambda, Node * const curr) {
    if( curr == nullptr   ) return curr; // ? Only happens when this->root is nullptr
    if( curr->data > data ) return ( curr->L == nullptr ) ? curr : lambda(lambda, curr->L) ;
    if( curr->data < data ) return ( curr->R == nullptr ) ? curr : lambda(lambda, curr->R) ;
    return curr; // ? Have it already
  };

  Node * const prev { FindPrev(FindPrev, this->root) } ;

  if     ( prev == nullptr   ) this->root = new Node { data };
  else if( prev->data > data ) prev->L    = new Node { data };
  else if( prev->data < data ) prev->R    = new Node { data };

  this->root = this->root->Rebalance();

  return this;
}

template<class T>
AVL<T> * const AVL<T>::Delete(T data)
{
  if( this->root == nullptr ) return this;

  Node * prev { nullptr } ;
  Node * curr { this->root } ;
  Node * rear { ( curr->data > data ) ? ( curr->L ) : ( curr->R ) } ;

  // ? Looking for target node
  while( curr->data != data ) {
    if( rear == nullptr ) return this; // ? Not found
    prev = curr;
    curr = rear;
    rear = ( curr->data > data ) ? ( curr->L ) : ( curr->R ) ;
  }

  // ? Sink node to be a leaf of tree
  rear = ( curr->L != nullptr ) ? ( curr->L ) : ( curr->R ) ;
  while( !curr->isLeaf() ) {
    curr->data = rear->data;
    prev = curr;
    curr = rear;
    rear = ( curr->L != nullptr ) ? ( curr->L ) : ( curr->R ) ;
  }

  if( curr == this->root ) this->root = nullptr;
  else if( prev->L == curr ) prev->L  = nullptr;
  else if( prev->R == curr ) prev->R  = nullptr;

  delete curr;

  if( this->root != nullptr ) this->root = this->root->Rebalance();

  return this;
}

template<class T>
void AVL<T>::PrintLevelorder(void) const
{
  // ? Count size of curr node ( need to contain null place )
  auto CountSize = [&](auto&& lambda, const Node * const curr, const std::size_t size) {
    if( curr == nullptr ) return size / 2; // ? if touch the null place, than back out
    const std::size_t sizeL = lambda(lambda, curr->L, size * 2 + 0);
    const std::size_t sizeR = lambda(lambda, curr->R, size * 2 + 1);
    return ( sizeL > sizeR ) ? ( sizeL ) : ( sizeR ) ; // ? compare which side is bigger
  };

  const std::size_t size { CountSize(CountSize, this->root, 1) + 1 } ;

  T * arr { new T[size] {} } ; // ? Convert BST into array form

  auto ConvertToArray = [&](auto&& lambda, const Node * const curr, const std::size_t index) {
    if( curr == nullptr ) return; // ? if touch null place, keeping it empty
    arr[index] = curr->data;
    lambda(lambda, curr->L, index * 2 + 0);
    lambda(lambda, curr->R, index * 2 + 1);
  };

  ConvertToArray(ConvertToArray, this->root, 1);

  // ? Print datas
  std::size_t module {2};
  std::cout << "Height: " << Height() << ", Size: " << Size() << ", Data: [" ;
  for(std::size_t index {1}; index < size; ++index) {
    if( index % module == 0 ) { module *= 2;
      std::cout << "], [" ;
    } else if( index != 1 ) {
      std::cout << ", " ;
    }
    std::cout << arr[index] ;
  }
  std::cout << "]" << std::endl;
  
  delete[] arr;
}

// ? class AVL<T>::Node impelement
template<class T>
bool AVL<T>::Node::isLeaf(void) const 
{
  return ( this->L == nullptr && this->R == nullptr ) ;
}

template<class T>
std::size_t AVL<T>::Node::Height(void) const
{
  auto RecursiveHeight = [&](auto&& lambda, const Node * const curr, const std::size_t deep) {
    if( curr == nullptr ) return deep;
    std::size_t deepL = lambda(lambda, curr->L, deep + 1);
    std::size_t deepR = lambda(lambda, curr->R, deep + 1);
    return ( deepL > deepR ) ? ( deepL ) : ( deepR ) ;
  };
  return RecursiveHeight(RecursiveHeight, this, 0);
}

template<class T>
std::size_t AVL<T>::Node::Size(void) const
{
  auto RecursiveSize = [&](auto&& lambda, const Node * const curr) {
    if( curr == nullptr ) return 1;
    return lambda(lambda, curr->L) + lambda(lambda, curr->R);
  };
  return RecursiveSize(RecursiveSize, this) - 1;
}

template<class T>
AVL<T>::Node * const AVL<T>::Node::RotationL(void)
{
  Node * const temp { this->R } ;
  this->R = temp->L;
  temp->L = this;
  return temp;
}

template<class T>
AVL<T>::Node * const AVL<T>::Node::RotationR(void)
{
  Node * const temp { this->L } ;
  this->L = temp->R;
  temp->R = this;
  return temp;
}

template<class T>
AVL<T>::Node * const AVL<T>::Node::Rebalance(void)
{
  if( this->Height() > 3 ) {
    if( this->L != nullptr ) this->L = this->L->Rebalance();
    if( this->R != nullptr ) this->R = this->R->Rebalance();
  }

  const std::size_t heightL { ( this->L != nullptr ) ? ( this->L->Height() ) : ( 0 ) } ;
  const std::size_t heightR { ( this->R != nullptr ) ? ( this->R->Height() ) : ( 0 ) } ;
  const short factor { static_cast<const short>( heightL - heightR ) } ; 
  
  switch ( factor ) {
    case +2: {
      if( this->L->R != nullptr ) this->L = this->L->RotationL();
      return this->RotationR();
    }
    case -2: {
      if( this->R->L != nullptr ) this->R = this->R->RotationR();
      return this->RotationL();
    }
    default: return this;
  }
}

#endif // _AVL_H_