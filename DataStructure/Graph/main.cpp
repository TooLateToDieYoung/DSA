#include "Graph.h"
#include <memory>

int main(void)
{
  std::unique_ptr<Graph<char>> graph { std::make_unique<Graph<char>>() };

  graph->Insert('a')->PrintGraph();

  graph->Insert('k')->Connect('k', 'a')->PrintGraph();

  graph->Insert('g')->Connect('k', 'g')->PrintGraph();

  graph->Insert('e')->Connect('e', 'a')->Connect('k', 'e')->PrintGraph();

  graph->Disconnect('e', 'a')->PrintGraph();

  graph->Delete('k')->PrintGraph();

  return 0;
}