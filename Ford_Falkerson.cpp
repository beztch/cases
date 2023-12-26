#include <iostream>
#include <vector>
using Matrix = std::vector<std::vector<int>>;

enum class Color { White, Gray, Black };

bool DFSVisit(Matrix& graph, std::vector<int>& parent, std::vector<Color>& color, int v, int sink) {
  color[v] = Color::Gray;
  for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
    if (color[i] == Color::White && graph[v][i] > 0) {
      parent[i] = v;
      if (i == sink) {
        color[i] = Color::Black;
        return true;
      }
      if (DFSVisit(graph, parent, color, i, sink)) {
        return true;
      }
    }
  }
  color[v] = Color::Black;
  return false;
}

bool DFS(Matrix& graph, std::vector<int>& parent, int source, int sink) {
  std::vector<Color> color(graph.size(), Color::White);
  parent[source] = source;
  DFSVisit(graph, parent, color, source, sink);
  return color[sink] == Color::Black;
}

int FordFalkerson(Matrix& graph, int source, int sink) {
  Matrix rest_graph = graph;
  int max_flow = 0;
  for (std::vector<int> parent(rest_graph.size(), -1); DFS(rest_graph, parent, source, sink);) {
    int path = -1;
    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      path = (path == -1 ? rest_graph[u][v] : (std::min(path, rest_graph[u][v])));
    }
    for (int v = sink; v != source; v = parent[v]) {
      int u = parent[v];
      rest_graph[u][v] -= path;
      rest_graph[v][u] += path;
    }
    max_flow += path;
  }
  return max_flow;
}

int main() {
  int v = 0;
  int e = 0;
  std::cin >> v >> e;
  Matrix graph(v);
  for (int i = 0; i < v; ++i) {
    graph[i].resize(v, 0);
  }
  for (int i = 0; i < e; ++i) {
    int a = 0;
    int b = 0;
    int c = 0;
    std::cin >> a >> b >> c;
    graph[a - 1][b - 1] = c;
  }
  std::cout << FordFalkerson(graph, 0, v - 1) << '\n';
  return 0;
}
