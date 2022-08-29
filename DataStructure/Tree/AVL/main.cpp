#include "AVL.h"
#include <string>

int main(void) 
{
  AVL<char> * const tree { new AVL<char> {} } ;

  std::string str { "bdm23384re1r0vcb5hg213djfsCM6" } ;

  for(auto& c : str) tree->Insert(c)->PrintLevelorder();

  delete tree;

  return 0;
}