#include <iostream>
#include "SingleLinkList.h"

int main(void)
{
  SingleLinkList<char> * list { new SingleLinkList<char> { } } ;

  // 0 -> 1 0 -> 2 1 0 -> 3 2 1 0 -> 4 3 2 1 0
  for(char c { 0 }; c < 5; ++c) list->Insert(c + 0x30);   
  list->PrintList(); // 4 3 2 1 0

  // 4 3 2 1 5 0 -> 4 3 2 6 1 5 0 -> 4 3 7 2 6 1 5 0 -> 4 8 3 7 2 6 1 5 0 -> 9 4 8 3 7 2 6 1 5 0
  for(char c { 0 }; c < 5; ++c) list->Insert(c + 0x35, 4 - c);
  list->PrintList(); // 9 4 8 3 7 2 6 1 5 0 

  list->Remove(0)->PrintList(); // X 4 8 3 7 2 6 1 5 0
  list->Remove(4)->PrintList(); //   4 8 3 7 X 6 1 5 0
  list->Remove(7)->PrintList(); //   4 8 3 7   6 1 5 X
  list->Remove(9)->PrintList(); //   4 8 3 7   6 1 5   -> nothing ( out of length )

  list->Reverse()->PrintList(); // 5 1 6 7 3 8 4
  list->Reverse()->PrintList(); // 4 8 3 7 6 1 5

  list->Replace('a', 0); // a 8 3 7 6 1 5
  list->Replace('b', 3); // a 8 3 b 6 1 5
  list->Replace('c', 6); // a 8 3 b 6 1 c
  list->Replace('d', 9); // a 8 3 b 6 1 c -> nothing ( out of length )

  delete list; // a 8 3 b 6 1 c

  return 0;
}
