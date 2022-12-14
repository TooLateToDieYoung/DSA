#ifndef _BST_H_
#define _BST_H_

#include <iostream>

template<class T>
class BST
{
  public:
    typedef enum { Preorder, Inorder, Postorder, Levelorder } TraversalTypeDef;

  private:
    class Node;

  private:
    Node * root;

  public:
    explicit BST(void) : root{nullptr} {}
    virtual ~BST(void);
  
  public:
    BST * Insert(T data);
    BST * Delete(T data);
    template<TraversalTypeDef type> BST * PrintTree(void);

    std::size_t Height(void) const { return this->root->Height(); }
    std::size_t Size(void) const { return this->root->Size(); }

  private:
    void PrintPreorder(const Node * const curr) const;
    void PrintInorder(const Node * const curr) const;
    void PrintPostorder(const Node * const curr) const;
    void PrintLevelorder(const Node * const curr) const;
};

template<class T>
class BST<T>::Node
{
  public:
    explicit Node(T data) : data{data}, L{nullptr}, R{nullptr} { }
    ~Node(void) = default;

  public:
    std::size_t Height(void) const;
    std::size_t Size(void) const;

  public:
    T      data;
    Node * L;
    Node * R;
};

template<class T>
BST<T>::~BST(void) 
{
  std::cout << "~BST() -----------------------------------------------------" << std::endl;
  while( this->root != nullptr ) {
    Delete(this->root->data);
    PrintLevelorder(this->root);
  }
}

template<class T>
BST<T> * BST<T>::Insert(T data)
{
  auto FindPrev = [&](auto&& lambda, Node * const curr) {
    if( curr == nullptr   ) return curr; // ? Only happens when this->root is nullptr
    if( curr->data > data ) return ( curr->L == nullptr ) ? curr : lambda(lambda, curr->L) ;
    if( curr->data < data ) return ( curr->R == nullptr ) ? curr : lambda(lambda, curr->R) ;
    return curr; // ? Have it already
  };

  Node * const prev { FindPrev(FindPrev, this->root) } ;

  if     ( prev == nullptr   ) this->root = new Node { data } ;
  else if( prev->data > data ) prev->L    = new Node { data } ;
  else if( prev->data < data ) prev->R    = new Node { data } ;

  return this;
}

template<class T>
BST<T> * BST<T>::Delete(T data)
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
  while( curr->L != nullptr || curr->R != nullptr ) {
    curr->data = rear->data;
    prev = curr;
    curr = rear;
    rear = ( curr->L != nullptr ) ? ( curr->L ) : ( curr->R ) ;
  }

  if( curr == this->root ) this->root = nullptr;
  else if( prev->L == curr ) prev->L  = nullptr;
  else if( prev->R == curr ) prev->R  = nullptr;

  delete curr;

  return this;
}

template<class T>
template<BST<T>::TraversalTypeDef type>
BST<T> * BST<T>::PrintTree(void)
{
  std::cout << "Print() ----------------------------------------------------" << std::endl;
  std::cout << "Size: " << Size() << ", Height: " << Height() << std::endl;
  switch ( type ) 
  {
    case Preorder:   { PrintPreorder(this->root);   break; }
    case Inorder:    { PrintInorder(this->root);    break; }
    case Postorder:  { PrintPostorder(this->root);  break; }
    case Levelorder: { PrintLevelorder(this->root); break; }
    default: break;
  }
  std::cout << "------------------------------------------------------------" << std::endl;

  return this;
}

template<class T>
void BST<T>::PrintPreorder(const Node * const curr) const
{
  if( curr == nullptr ) return;
  std::cout << "Address: " << curr << ", Data: " << curr->data << std::endl;
  PrintPreorder(curr->L);
  PrintPreorder(curr->R);
}

template<class T>
void BST<T>::PrintInorder(const Node * const curr) const
{
  if( curr == nullptr ) return;
  PrintInorder(curr->L);
  std::cout << "Address: " << curr << ", Data: " << curr->data << std::endl;
  PrintInorder(curr->R);
}

template<class T>
void BST<T>::PrintPostorder(const Node * const curr) const
{
  if( curr == nullptr ) return;
  PrintPostorder(curr->L);
  PrintPostorder(curr->R);
  std::cout << "Address: " << curr << ", Data: " << curr->data << std::endl;
}

template<class T>
void BST<T>::PrintLevelorder(const Node * const curr) const
{
  // ? Count size of curr node ( need to contain null place )
  auto CountSize = [&](auto&& lambda, const Node * const curr, const std::size_t size) {
    if( curr == nullptr ) return size / 2; // ? if touch the null place, than back out
    const std::size_t sizeL = lambda(lambda, curr->L, size * 2 + 0);
    const std::size_t sizeR = lambda(lambda, curr->R, size * 2 + 1);
    return ( sizeL > sizeR ) ? ( sizeL ) : ( sizeR ) ; // ? compare which side is bigger
  };

  const std::size_t size { CountSize(CountSize, curr, 1) + 1 } ;

  T * arr { new T[size] {} } ; // ? Convert BST into array form

  auto ConvertToArray = [&](auto&& lambda, const Node * const curr, const std::size_t index) {
    if( curr == nullptr ) return; // ? if touch null place, keeping it empty
    arr[index] = curr->data;
    lambda(lambda, curr->L, index * 2 + 0);
    lambda(lambda, curr->R, index * 2 + 1);
  };

  ConvertToArray(ConvertToArray, curr, 1);

  // ? Print datas
  std::size_t module {2};
  std::cout << "Data: [" ;
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

template<class T>
std::size_t BST<T>::Node::Height(void) const
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
std::size_t BST<T>::Node::Size(void) const
{
  auto RecursiveSize = [&](auto&& lambda, const Node * const curr) {
    if( curr == nullptr ) return 1;
    return lambda(lambda, curr->L) + lambda(lambda, curr->R);
  };
  return RecursiveSize(RecursiveSize, this) - 1;
}

#endif // _BST_H_