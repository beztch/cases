#include <iostream>
#include <vector>
#include <bit>
#include <cmath>
#include <cstdint>

int64_t Log(int64_t n) {
  return 64 - std::__countl_zero(static_cast<uint64_t>(n - 1));
}

class SegmentTree {
  std::vector<int64_t> tree_;
  std::vector<int64_t> promise_;
  int64_t n_actual_;

  int64_t Parent(int64_t i) {
    return (i - 1) / 2;
  }
  int64_t Left(int64_t i) {
    return 2 * i + 1;
  }
  int64_t Right(int64_t i) {
    return 2 * i + 2;
  }
  bool IsLeftSon(int i) {
    return (i % 2 == 1);
  }
  bool IsRightSon(int i) {
    return (i % 2 == 0);
  }

  int64_t Query(int64_t l, int64_t r, int64_t node, int64_t a, int64_t b) {
    if (node >= 2 * n_actual_ - 1) {
      return -1000000000;
    }
    if (a >= l && b <= r) {
      return tree_[node] + promise_[node];
    }
    if (a > r || b < l) {
      return -1000000000;
    }
    Push(node);
    return std::max(Query(l, r, Left(node), a, (a + b) / 2), Query(l, r, Right(node), (a + b) / 2 + 1, b));
  }

  void Push(int64_t node) {
    tree_[node] += promise_[node];
    if (Left(node) < 2 * n_actual_ - 1) {
      promise_[Left(node)] += promise_[node];
    }
    if (Right(node) < 2 * n_actual_ - 1) {
      promise_[Right(node)] += promise_[node];
    }
    promise_[node] = 0;
  }

  void Update(int64_t l, int64_t r, int64_t node, int64_t a, int64_t b, int64_t delta) {
    if (node >= 2 * n_actual_ - 1) {
      return;
    }
    if (a >= l && b <= r) {
      promise_[node] += delta;
      return;
    }
    if (a > r || b < l) {
      return;
    }
    Push(node);
    Update(l, r, Left(node), a, (a + b) / 2, delta);
    Update(l, r, Right(node), (a + b) / 2 + 1, b, delta);
    tree_[node] = std::max(Query(a, (a + b) / 2, Left(node), a, (a + b) / 2),
                           Query((a + b) / 2 + 1, b, Right(node), (a + b) / 2 + 1, b));
  }

 public:
  explicit SegmentTree(const std::vector<int64_t>& mass) {
    auto n = static_cast<int64_t>(mass.size());
    n_actual_ = static_cast<int64_t>(pow(2, static_cast<double>(Log(n))));
    tree_ = std::vector<int64_t>(2 * n_actual_ - 1);
    promise_ = std::vector<int64_t>(2 * n_actual_ - 1, 0);
    for (int64_t i = n_actual_ - 1; i < n_actual_ - 1 + n; ++i) {
      tree_[i] = mass[i - n_actual_ + 1];
    }
    for (int64_t i = n_actual_ - 1 + n; i < 2 * n_actual_ - 1; ++i) {
      tree_[i] = -1000000000;
    }
    for (int64_t i = n_actual_ - 2; i >= 0; --i) {
      tree_[i] = std::max(tree_[Left(i)], tree_[Right(i)]);
    }
  }

  int64_t Query(int64_t l, int64_t r) {
    l += n_actual_ - 1;
    r += n_actual_ - 1;
    return Query(l, r, 0, n_actual_ - 1, 2 * n_actual_ - 2);
  }

  void Update(int64_t i, int64_t delta) {
    i += n_actual_ - 1;
    tree_[i] += delta;
    while (i > 0) {
      i = Parent(i);
      tree_[i] = std::max(tree_[Left(i)], tree_[Right(i)]);
    }
  }

  void Update(int64_t l, int64_t r, int64_t delta) {
    l += n_actual_ - 1;
    r += n_actual_ - 1;
    Update(l, r, 0, n_actual_ - 1, 2 * n_actual_ - 2, delta);
  }

  void PrintAll() {
    for (int64_t i = n_actual_ - 1; i < 2 * n_actual_ - 1; ++i) {
      std::cout << tree_[i] << " ";
    }
    std::cout << '\n';
  }
};

int main() {
  int64_t n = 0;
  std::cin >> n;
  std::vector<int64_t> mass(n);
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> mass[i];
  }
  SegmentTree segment_tree(mass);
  int64_t k = 0;
  std::cin >> k;
  for (int i = 0; i < k; ++i) {
    char oper = 0;
    std::cin >> oper;
    switch (oper) {
      case 'm': {
        int64_t l = 0;
        int64_t r = 0;
        std::cin >> l >> r;
        std::cout << segment_tree.Query(l - 1, r - 1) << "\n";
        break;
      }
      case 'a': {
        int64_t l = 0;
        int64_t r = 0;
        int64_t delta = 0;
        std::cin >> l >> r >> delta;
        segment_tree.Update(l - 1, r - 1, delta);
        break;
      }
    }
  }
}
