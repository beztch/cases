#include <iostream>
#include <vector>
#include <map>

class Bor {
  std::vector<std::map<char, int> > node_;
  std::vector<bool> terminal_;

 public:
  explicit Bor(std::vector<std::string>& dict) {
    int count = 0;
    node_.emplace_back();
    terminal_.emplace_back(false);
    int n = static_cast<int>(dict.size());
    for (int i = 0; i < n; ++i) {
      int cur = 0;
      int len = static_cast<int>(dict[i].length());
      char c = 0;
      for (int j = 0; j < len; ++j) {
        c = dict[i][j];
        if (node_[cur][c] == 0) {
          node_.emplace_back();
          node_[cur][c] = ++count;
          terminal_.emplace_back(false);
        }
        cur = node_[cur][c];
      }
      terminal_[cur] = true;
    }
  }

  void Print() {
    int n = static_cast<int>(terminal_.size());
    for (int i = 0; i < n; ++i) {
      std::cout << "вершина: " << i << " терминальная? " << terminal_[i] << " ребрa: \n";
      for (auto it = node_[i].begin(); it != node_[i].end(); ++it) {
        std::cout << "цвет: " << it->first << " куда: " << it->second << '\n';
      }
    }
  }
};

struct Node {
  std::map<char, int> edge;
  int suf_ptr;
  int max_len;
  int end_pos;
  bool terminal;
  Node() : edge(), suf_ptr(-1), max_len(0), end_pos(0), terminal(false) {
  }
  Node(std::map<char, int> e, int s, int l, int ep, bool it)
      : edge(e), suf_ptr(s), max_len(l), end_pos(ep), terminal(it) {
  }
};

class SuffixGandomat {
  std::vector<Node> node_;

 public:
  int Clone(int parent, char c, int ver) {
    node_.emplace_back(node_[ver].edge, node_[ver].suf_ptr, node_[parent].max_len + 1, 0, false);
    int clone = (node_[ver].suf_ptr = static_cast<int>(node_.size()) - 1);
    while (parent != -1 && node_[parent].edge[c] == ver) {
      node_[parent].edge[c] = clone;
      parent = node_[parent].suf_ptr;
    }
    return clone;
  }

  void AddSymbol(char c, int& last) {
    node_.emplace_back(std::map<char, int>(), -1, node_[last].max_len + 1, node_[last].end_pos + 1, false);
    int new_node = static_cast<int>(node_.size()) - 1;
    while (last != -1 && node_[last].edge[c] == 0) {
      node_[last].edge[c] = new_node;
      last = node_[last].suf_ptr;
    }
    if (last == -1) {
      node_[new_node].suf_ptr = 0;
    } else if (node_[last].max_len + 1 == node_[node_[last].edge[c]].max_len) {
      node_[new_node].suf_ptr = node_[last].edge[c];
    } else {
      node_[new_node].suf_ptr = Clone(last, c, node_[last].edge[c]);
    }
    last = new_node;
  }

  explicit SuffixGandomat(std::string& string) {
    int last = 0;
    node_ = std::vector<Node>();
    node_.emplace_back();
    int length = static_cast<int>(string.length());
    for (int i = 0; i < length; ++i) {
      AddSymbol(string[i], last);
    }
  }

  void Print() {
    int n = static_cast<int>(node_.size());
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
      for (auto it = node_[i].edge.begin(); it != node_[i].edge.end(); ++it) {
        std::cout << i << " " << it->first << " " << it->second << '\n';
      }
    }
  }
};

int main() {
  std::string str;
  std::cin >> str;
  SuffixGandomat bor(str);
  bor.Print();
}
