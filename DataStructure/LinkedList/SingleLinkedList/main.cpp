#include "NormalSingleLinkedList.h"
#include "RecursiveSingleLinkedList.h"

int main(void)
{
  NormalSingleLinkedList<char> * list { new NormalSingleLinkedList<char> { } } ;
  // RecursiveSingleLinkedList<char> * list { new RecursiveSingleLinkedList<char> { } } ;

  // 0 -> 1 0 -> 2 1 0 -> 3 2 1 0 -> 4 3 2 1 0
  for(char c { 0 }; c < 5; ++c) list->Insert(c + 0x30)->PrintList();

  // 4 3 2 1 0 5 -> 4 3 2 1 6 0 5 -> 4 3 2 7 1 6 0 5 -> 4 3 8 2 7 1 6 0 5 -> 4 9 3 8 2 7 1 6 0 5
  for(char c { 0 }; c < 5; ++c) list->Insert(c + 0x35, 5 - c)->PrintList();

  list->Remove(0)->PrintList(); // X 9 3 8 2 7 1 6 0 5
  list->Remove(4)->PrintList(); //   9 3 8 2 X 1 6 0 5
  list->Remove(7)->PrintList(); //   9 3 8 2   1 6 0 X
  list->Remove(9)->PrintList(); //   9 3 8 2   1 6 0   -> nothing ( out of length )

  list->Reverse()->PrintList(); // 0 6 1 2 8 3 9
  list->Reverse()->PrintList(); // 9 3 8 2 1 6 0

  list->Replace('a', 0)->PrintList(); // a 3 8 2 1 6 0
  list->Replace('b', 3)->PrintList(); // a 3 8 b 1 6 0
  list->Replace('c', 6)->PrintList(); // a 3 8 b 1 6 c
  list->Replace('d', 9)->PrintList(); // a 3 8 b 1 6 c -> nothing ( out of length )

  delete list; // a 3 8 b 1 6 c

  return 0;
}
