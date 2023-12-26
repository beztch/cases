#include <iostream>
#include <vector>
#include <queue>
using Matrix = std::vector<std::vector<int>>;

enum class Color { White, Gray, Black };

bool BFS(Matrix& graph, Matrix& layer_graph, int source, int sink) {
  int n = static_cast<int>(graph.size());
  std::vector<int> parent(n, -1);
  std::vector<int> dist(static_cast<int>(graph.size()), -1);
  std::queue<int> queue;
  queue.push(source);
  parent[source] = source;
  dist[source] = 0;
  while (!queue.empty()) {
    source = queue.front();
    queue.pop();
    for (int i = 0; i < static_cast<int>(graph.size()); ++i) {
      if (graph[source][i] > 0 && source != i) {
        if (dist[i] == -1) {
          dist[i] = dist[source] + 1;
          layer_graph[source][i] = graph[source][i];
          layer_graph[i][source] = graph[i][source];
          parent[i] = source;
          queue.push(i);
        } else if (dist[i] == dist[source] + 1) {
          layer_graph[source][i] = graph[source][i];
          layer_graph[i][source] = graph[i][source];
        }
      }
    }
  }
  return (parent[sink] != -1);
}

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

int Dinic(Matrix& graph, int source, int sink) {
  int n = static_cast<int>(graph.size());
  int max_flow = 0;
  std::vector<std::vector<int>> layer_graph(n, std::vector<int>(n, 0));
  while (BFS(graph, layer_graph, source, sink)) {
    for (std::vector<int> parent(graph.size(), -1); DFS(layer_graph, parent, source, sink);) {
      int path = -1;
      for (int v = sink; v != source; v = parent[v]) {
        int u = parent[v];
        path = (path == -1 ? layer_graph[u][v] : (std::min(path, layer_graph[u][v])));
      }
      for (int v = sink; v != source; v = parent[v]) {
        int u = parent[v];
        layer_graph[u][v] -= path;
        layer_graph[v][u] += path;
        graph[u][v] -= path;
        graph[v][u] += path;
      }
      max_flow += path;
    }
    layer_graph = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
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
  std::cout << Dinic(graph, 0, v - 1) << '\n';
  return 0;
}
