#include "DoubleLinkList.h"

int main(void)
{
  DoubleLinkList<char> * const list { new DoubleLinkList<char> { } } ;

  list->Insert('a')->PrintList();    // a
  list->Insert('b')->PrintList();    // b a
  list->Insert('c')->PrintList();    // c b a
  list->Insert('d', 1)->PrintList(); // c d b a 
  list->Insert('e', 3)->PrintList(); // c d b e a 
  
  list->Remove(0)->PrintList(); // X d b e a
  list->Remove(1)->PrintList(); //   d X e a
  list->Remove(2)->PrintList(); //   d   e X

  list->Reverse()->PrintList(); // e d

  delete list; // e d

  return 0;
}