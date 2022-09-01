#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>
#include <memory>
#include <iostream>

template<class T>
class Graph
{
  private:
    class Vertex;

  public:
    explicit Graph(void) = default;
    virtual ~Graph(void) { while(!vertexs.empty()) Delete(vertexs[0]->key)->PrintGraph(); }
  
    Graph * const Insert(T key) {
      if( FindOrder(key) == -1 ) {
        std::shared_ptr<Vertex> sp { std::make_shared<Vertex>(key) };
        this->vertexs.push_back(sp);
      }
      return this;
    }

    Graph * const Delete(T key) {
      const int order { FindOrder(key) };
      if( order == -1 ) return this;
      for(auto& edge : vertexs[order]->edges) edge->Disarrow(vertexs[order]);
      vertexs.erase(vertexs.begin() + order);
      return this;
    }

    Graph * const Connect(T key1, T key2) {
      if( key1 == key2 ) return this;

      const int order1 { FindOrder(key1) };
      if( order1 == -1 ) return this;

      const int order2 { FindOrder(key2) };
      if( order2 == -1 ) return this;

      vertexs[order1]->Arrow(vertexs[order2]);
      vertexs[order2]->Arrow(vertexs[order1]);

      return this;
    }

    Graph * const Disconnect(T key1, T key2) {
      if( key1 == key2 ) return this;

      const int order1 { FindOrder(key1) };
      if( order1 == -1 ) return this;
      
      const int order2 { FindOrder(key2) };
      if( order2 == -1 ) return this;

      vertexs[order1]->Disarrow(vertexs[order2]);
      vertexs[order2]->Disarrow(vertexs[order1]);
      return this;
    }

    void PrintGraph(void) {
      std::cout << "+-------------------------------------------+" << std::endl;
      std::cout << "| Address       | key | use_count           |" << std::endl;
      for(auto& vertex : vertexs) {
        std::cout << "| "<< (void*)vertex.get() << " |  " << vertex->key << "  | " << vertex.use_count() << " | ";
        for(auto& edge : vertex->edges) {
          std::cout << edge->key << ", ";
        }
        std::cout << std::endl;
      }
    }

  private:
    int FindOrder(T key) {
      for(int i {0}; i != vertexs.size(); ++i)
        if( vertexs[i]->key == key ) return i;
      return -1;
    }
  
  private:
    std::vector<std::shared_ptr<Vertex>> vertexs { };
};

template<class T>
class Graph<T>::Vertex
{
  public:
    explicit Vertex(T key) : key{key} {}
    virtual ~Vertex(void) = default;

    void Arrow(std::shared_ptr<Vertex> obj) { edges.push_back(obj); }
    void Disarrow(std::shared_ptr<Vertex> obj) {
      for(auto it {edges.begin()}; it != edges.end(); ++it) {
        if( it->get() == obj.get() ) {
          edges.erase(it);
          return;
        }
      }
    }

  public:
    T                                    key   { };
    std::vector<std::shared_ptr<Vertex>> edges { };
};

#endif // _GRAPH_H_