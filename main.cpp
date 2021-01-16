#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

struct Edge {
  int cost;
  pair<int, int> island_index;
};

class UnionFind {
 public:
  explicit UnionFind(int count) : parent_vec(count), rank_vec(count, 0) {
    for (int i = 0; i < count; ++i) {
      parent_vec[i] = i;
    }
  }

  int findParent(int node) {
    if (parent_vec[node] == node) {
      return node;
    } else {
      return parent_vec[node] = findParent(parent_vec[node]);
    }
  }

  void unionParent(int first_node, int second_node) {
    first_node = findParent(first_node);
    second_node = findParent(second_node);
    if (first_node == second_node) {
      return;
    }
    if (rank_vec[first_node] > rank_vec[second_node]) {
      swap(first_node, second_node);
    }
    parent_vec[first_node] = second_node;
    if (rank_vec[first_node] == rank_vec[second_node]) {
      ++rank_vec[second_node];
    }
  }

 private:
  vector<int> parent_vec;
  vector<int> rank_vec;
};

vector<Edge> edge_vec;

int solution(int node_count, vector<vector<int>> _edge_vec_vec) {
  int edge_count = _edge_vec_vec.size();
  edge_vec.resize(edge_count);
  for (int i = 0; i < edge_count; ++i) {
    edge_vec[i].island_index.first = _edge_vec_vec[i][0];
    edge_vec[i].island_index.second = _edge_vec_vec[i][1];
    edge_vec[i].cost = _edge_vec_vec[i][2];
  }
  sort(edge_vec.begin(), edge_vec.end(), [](Edge first_edge, Edge second_edge) {
    return first_edge.cost < second_edge.cost;
  });
  UnionFind union_find(node_count);
  int result = 0;
  for (int i = 0; i < edge_count; ++i) {
    int first_island_parent = union_find.findParent(edge_vec[i].island_index.first);
    int second_island_parent = union_find.findParent(edge_vec[i].island_index.second);
    if (first_island_parent != second_island_parent) {
      result += edge_vec[i].cost;
      union_find.unionParent(edge_vec[i].island_index.first, edge_vec[i].island_index.second);
    }
  }
  return result;
}

int main() {
  cout << solution(4, {{0, 1, 1}, {0, 2, 2}, {1, 2, 5}, {1, 3, 1}, {2, 3, 8}}) << endl;
  return 0;
}
