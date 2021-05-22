#include <iostream>
#include <iomanip>
#include "data_structure.hpp"
#include "graph.hpp"

namespace itis {

  int BinaryHeap::FindPosition(int node) {

    int idx = 0;
    for (int i = 1; i < heap.size(); i++) {
      if (heap[i].value == node) {
        idx = i;
      }
    }
    return idx;
  }
  void BinaryHeap::MinHeapInsert(int node, int key) {
    heap.emplace_back(HeapNode(node, key));
    DecreaseKey(node, key);
  }
  void BinaryHeap::DecreaseKey(int node, int newKey) {

    int index_node = FindPosition(node);

    if (newKey >= heap[index_node].key) {
      std::cout << "new key is not smaller than current key\n";
      return;
    }
    heap[index_node].key = newKey;

    while (index_node > 1 && heap[GetParentNode(index_node)].key > heap[index_node].key) {
      swap(heap[index_node], heap[GetParentNode(index_node)]);
      index_node = GetParentNode(index_node);
    }
  }
  void BinaryHeap::swap(struct HeapNode &p1, struct HeapNode &p2) {

    struct HeapNode temp = p1;
    p1 = p2;
    p2 = temp;
  }
  int BinaryHeap::ExtractMin() {

    if (IsHeapEmpty()) {
      std::cout << "error: heap is empty\n";
      exit(-1);
    }
    int min = heap[1].value;

    heap[1] = heap[heap.size() - 1];
    heap.erase(heap.begin() + heap.size() - 1);
    MinHeapify(1, (int) heap.size());

    return min;
  }
  void BinaryHeap::BuildMinHeap(std::vector<int> array) {

    for (int i = 0; i < array.size(); i++) {
      heap[i + 1].value = i;
      heap[i + 1].key = array[i];
    }
    for (int i = (int) heap.size() / 2; i >= 1; i--) {
      MinHeapify(i, (int) heap.size() - 1);
    }
  }
  void BinaryHeap::MinHeapify(int node, int length) {

    int left = 2 * node, right = 2 * node + 1, smallest;

    if (left <= length && heap[left].key < heap[node].key)
      smallest = left;
    else
      smallest = node;

    if (right <= length && heap[right].key < heap[smallest].key)
      smallest = right;

    if (smallest != node) {
      swap(heap[smallest], heap[node]);
      MinHeapify(smallest, length);
    }
  }

  /////////////// Prim's Algorithm /////////////////

  void Graph_MST::InitializeSingleSource(int Start) {

    distance.resize(num_vertex);
    predecessor.resize(num_vertex);

    for (int i = 0; i < num_vertex; i++) {
      distance[i] = maxDistance;
      predecessor[i] = -1;
    }
    distance[Start] = 0;
  }

  void Graph_MST::AddEdge(int from, int to, int weight) {
    AdjList[from].push_back(std::make_pair(to, weight));
  }

  void Graph_MST::Prim_MinQueue(int Start) {

    InitializeSingleSource(Start);

    BinaryHeap minQueue(num_vertex);
    minQueue.BuildMinHeap(distance);

    visited.resize(num_vertex, false);

    while (!minQueue.IsHeapEmpty()) {
      int u = minQueue.ExtractMin();
      visited[u] = true;
      for (auto itr = AdjList[u].begin(); itr != AdjList[u].end(); itr++) {
        if (visited[(*itr).first] == false && (*itr).second < distance[(*itr).first]) {
          distance[(*itr).first] = (*itr).second;
          predecessor[(*itr).first] = u;
          minQueue.DecreaseKey((*itr).first, distance[(*itr).first]);
        }
      }
    }

    std::cout << "print predecessor[]:\n";
    PrintDataArray(predecessor);
    std::cout << "print distance[]:\n";
    PrintDataArray(distance);

    std::cout << std::setw(3) << "v1"
              << " - " << std::setw(3) << "v2"
              << " : weight\n";
    int i = (Start + 1) % num_vertex;
    while (i != Start) {
      std::cout << std::setw(3) << predecessor[i] << " - " << std::setw(3) << i << " : " << std::setw(3) << distance[i]
                << "\n";
      i = (++i) % num_vertex;
    }
  }

  void Graph_MST::PrintDataArray(std::vector<int> array) {
    for (int i = 0; i < num_vertex; i++) {
      std::cout << std::setw(4) << i;
    }
    std::cout << std::endl;
    for (int i = 0; i < num_vertex; i++) {
      std::cout << std::setw(4) << array[i];
    }
    std::cout << std::endl << std::endl;
  }

  int main() {

    std::cout << "MST found by Prim_MinQueue:\n";
    Graph_MST g6(7);

    g6.AddEdge(0, 1, 5);
    g6.AddEdge(0, 5, 3);
    g6.AddEdge(1, 0, 5);
    g6.AddEdge(1, 2, 10);
    g6.AddEdge(1, 4, 1);
    g6.AddEdge(1, 6, 4);
    g6.AddEdge(2, 1, 10);
    g6.AddEdge(2, 3, 5);
    g6.AddEdge(2, 6, 8);
    g6.AddEdge(3, 2, 5);
    g6.AddEdge(3, 4, 7);
    g6.AddEdge(3, 6, 9);
    g6.AddEdge(4, 1, 1);
    g6.AddEdge(4, 3, 7);
    g6.AddEdge(4, 5, 6);
    g6.AddEdge(4, 6, 2);
    g6.AddEdge(5, 0, 3);
    g6.AddEdge(5, 4, 6);
    g6.AddEdge(6, 1, 4);
    g6.AddEdge(6, 2, 8);
    g6.AddEdge(6, 3, 9);
    g6.AddEdge(6, 4, 2);

    std::cout << "MST found by Prim_MinQueue:\n";

    g6.Prim_MinQueue(2);

    return 0;
  }
}  // namespace itis