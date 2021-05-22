#pragma once

#include <vector>
#include <cmath>
#include <list>

namespace itis {

  struct HeapNode {
    int key, value;
    HeapNode() : key(0), value(0){};
    HeapNode(int node_key, int element) : key(node_key), value(element){};
  };

  class BinaryHeap{
   private:
    std::vector<HeapNode> heap;
    void swap(struct HeapNode &p1, struct HeapNode &p2);
    int FindPosition(int node);
    int GetParentNode(int node){return std::floor(node/2);};
   public:
    BinaryHeap(){heap.resize(1);};
    BinaryHeap(int n){
      heap.resize(n + 1);
    }
    // Min-Priority Queue
    void MinHeapify(int node, int length);
    void BuildMinHeap(std::vector<int> array);
    void DecreaseKey(int node, int newKey);
    void MinHeapInsert(int node, int key);
    int ExtractMin();
    int Minimum(){return heap[1].value;};

    bool IsHeapEmpty(){return (heap.size()<=1);};

  };
}  // namespace itis