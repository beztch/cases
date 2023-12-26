#include <iostream>
#include <vector>
#include <map>
#include <queue>

struct Node {
  std::map<char, int> next;
  bool terminal;
  int suf_ref;
  int exit_link;
  Node() : terminal(false), suf_ref(-1), exit_link(-2) {
  }
};

class Bor {
  int amount_;
  std::vector<Node> node_;
  std::vector<int> leng_;
  std::vector<int> where_;

  void BuildSuffixRefferences() {
    std::queue<std::pair<int, char> > stack;
    for (auto sos = node_[0].next.begin(); sos != node_[0].next.end(); ++sos) {
      stack.emplace(0, sos->first);
      node_[node_[0].next[sos->first]].suf_ref = 0;
    }
    while (!stack.empty()) {
      std::pair<int, char> pair = stack.front();
      int node = pair.first;
      char c = pair.second;
      int next = node_[node].next[c];
      stack.pop();
      int suff = node_[node].suf_ref;
      while (suff != -1 && node_[suff].next[c] == 0) {
        suff = node_[suff].suf_ref;
      }
      node_[next].suf_ref = (suff == -1 ? 0 : node_[suff].next[c]);
      for (auto sos = node_[next].next.begin(); sos != node_[next].next.end(); ++sos) {
        if (sos->second != 0 && node_[sos->second].suf_ref == -1) {
          stack.emplace(next, sos->first);
        }
      }
    }
  }

  void BuildExitLinks() {
    std::queue<int> stack;
    node_[0].exit_link = -1;
    for (auto it = node_[0].next.begin(); it != node_[0].next.end(); ++it) {
      stack.push(it->second);
      node_[it->second].exit_link = -1;
    }
    while (!stack.empty()) {
      int node = stack.front();
      stack.pop();
      int suff = node_[node].suf_ref;
      if (suff != 0 && suff != -1) {
        node_[node].exit_link = (node_[suff].terminal ? suff : node_[suff].exit_link);
      } else {
        node_[node].exit_link = -1;
      }
      for (auto sos = node_[node].next.begin(); sos != node_[node].next.end(); ++sos) {
        if (node_[sos->second].exit_link == -2) {
          stack.push(sos->second);
        }
      }
    }
  }

 public:
  explicit Bor(std::vector<std::string>& dict) : amount_(static_cast<int>(dict.size())), leng_(amount_) {
    where_.resize(1000000);
    node_.reserve(1000000);
    int count = 0;
    node_.emplace_back();
    node_[0].terminal = false;
    int n = amount_;
    for (int i = 0; i < n; ++i) {
      int cur = 0;
      int len = static_cast<int>(dict[i].length());
      leng_[i] = len;
      char c = 0;
      for (int j = 0; j < len; ++j) {
        c = dict[i][j];
        if (node_[cur].next[c] == 0) {
          node_.emplace_back();
          node_[cur].next[c] = ++count;
          (node_.end() - 1)->terminal = false;
        }
        cur = node_[cur].next[c];
      }
      node_[cur].terminal = true;
      where_[cur] = i;
    }
    node_[0].suf_ref = -1;
    BuildSuffixRefferences();
    BuildExitLinks();
  }

  void Print() {
    int n = static_cast<int>(node_.size());
    for (int i = 0; i < n; ++i) {
      std::cout << "вершина: " << i << " терминальная? " << node_[i].terminal << " конченая " << node_[i].exit_link
                << " ребрa: \n";
      for (auto it = node_[i].next.begin(); it != node_[i].next.end(); ++it) {
        std::cout << "цвет: " << it->first << " куда: " << it->second << '\n';
      }
    }
  }

  int NextState(int node, char c) {
    while (node != -1 && node_[node].next[c] == 0) {
      node = node_[node].suf_ref;
    }
    return (node == -1 ? 0 : node_[node].next[c]);
  }

  void LoadEntries(int ind, int node, std::vector<std::vector<int> >& answer) {
    if (!node_[node].terminal) {
      node = node_[node].exit_link;
    }
    while (node != -1) {
      answer[where_[node]].emplace_back(ind);
      node = node_[node].exit_link;
    }
  }

  void AhoKorasik(std::string& str) {
    std::vector<std::vector<int> > answer(amount_);
    int node = 0;
    int len = static_cast<int>(str.length());
    for (int i = 0; i < len; ++i) {
      node = NextState(node, str[i]);
      LoadEntries(i, node, answer);
    }
    for (int i = 0; i < amount_; ++i) {
      int len = static_cast<int>(leng_[i]);
      std::cout << answer[i].size() << " ";
      for (auto itt = answer[i].begin(); itt != answer[i].end(); ++itt) {
        std::cout << *itt + 2 - len << " ";
      }
      std::cout << '\n';
    }
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string string;
  std::cin >> string;
  int n = 0;
  std::cin >> n;
  std::vector<std::string> dict(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> dict[i];
  }
  Bor bor(dict);
  bor.AhoKorasik(string);
}
