#include <iostream>
#include "BST.h"

int main(void)
{
  BST<char> * const tree { new BST<char> { } } ;

  const BST<char>::TraversalTypeDef type { BST<char>::TraversalTypeDef::Levelorder } ;

  tree->Insert('5')->PrintTree<type>(); // [5]
  tree->Insert('3')->PrintTree<type>(); // [5], [3]
  tree->Insert('7')->PrintTree<type>(); // [5], [3, 7]
  tree->Insert('4')->PrintTree<type>(); // [5], [3, 7], [N, 4]
  tree->Insert('6')->PrintTree<type>(); // [5], [3, 7], [N, 4, 6]
  tree->Insert('8')->PrintTree<type>(); // [5], [3, 7], [N, 4, 6, 8]
  tree->Insert('9')->PrintTree<type>(); // [5], [3, 7], [N, 4, 6, 8], [N, N, N, N, N, N, N, 9]
  tree->Delete('8')->PrintTree<type>(); // [5], [3, 7], [N, 4, 6, 9]
  tree->Delete('7')->PrintTree<type>(); // [5], [3, 6], [N, 4, N, 9]

  delete tree;

  return 0;
}