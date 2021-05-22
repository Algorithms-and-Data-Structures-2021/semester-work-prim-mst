#pragma once

#include <vector>
#include <list>

namespace itis {

  static const int maxDistance = 100;

  class Graph_MST {
   private:
    int num_vertex;
    std::vector<std::list<std::pair<int, int>>> AdjList;
    std::vector<int> predecessor, distance;
    std::vector<bool> visited;
    void InitializeSingleSource(int Start);
    void PrintDataArray(std::vector<int> array);

   public:
    Graph_MST() : num_vertex(0){};
    Graph_MST(int n) : num_vertex(n) {
      AdjList.resize(num_vertex);
    }
    void AddEdge(int from, int to, int weight);
    void Prim_MinQueue(int Start);

    friend class BinaryHeap;
  };

}  // namespace itis