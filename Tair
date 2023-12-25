#include <iostream>
#include <vector>
#include <cstdint>
#include <random>

struct Node {
  int64_t key;
  int64_t priority;
  int64_t size;
  Node* parent;
  Node* left_child;
  Node* right_child;
  Node() : key(0), priority(0), size(0), parent(nullptr), left_child(nullptr), right_child(nullptr) {
  }
  Node(int64_t x, int64_t y)
      : key(x), priority(y), size(x), parent(nullptr), left_child(nullptr), right_child(nullptr) {
  }
  ~Node() = default;
};

void SetRightChild(Node* parent, Node* child) {
  if (parent == nullptr) {
    return;
  }
  if (child == nullptr) {
    parent->right_child = child;
    return;
  }
  parent->right_child = child;
  parent->size += child->size;
  child->parent = parent;
}

void SetLeftChild(Node* parent, Node* child) {
  if (parent == nullptr) {
    return;
  }
  if (child == nullptr) {
    parent->left_child = child;
    return;
  }
  parent->left_child = child;
  parent->size += child->size;
  child->parent = parent;
}

void CutLeftChild(Node* parent) {
  if (parent == nullptr) {
    return;
  }
  if (parent->left_child == nullptr) {
    return;
  }
  Node* tmp = parent->left_child;
  parent->left_child = nullptr;
  parent->size -= tmp->size;
  tmp->parent = nullptr;
}

void CutRightChild(Node* parent) {
  if (parent == nullptr) {
    return;
  }
  if (parent->right_child == nullptr) {
    return;
  }
  Node* tmp = parent->right_child;
  parent->right_child = nullptr;
  parent->size -= tmp->size;
  tmp->parent = nullptr;
}

struct Tair {
  int64_t key;
  int64_t priority;
  int64_t num;
  Tair(int64_t x, int64_t y, int64_t z) : key(x), priority(y), num(z) {
  }
  Tair() : key(0), priority(0), num(0) {
  }
};

class Treap {
  Node* root_;

 public:
  struct Iterator {
   private:
    Node* cur_;

   public:
    Iterator() : cur_(nullptr) {
    }
    Iterator(Node* node) : cur_(node) {  // NOLINT
    }

    Node* operator->() {
      return cur_;
    }

    Node& operator*() {
      return *cur_;
    }

    operator bool() {  // NOLINT
      return (cur_ != nullptr);
    }

    Iterator& operator++() {
      if (cur_ == nullptr) {
        return *this;
      }
      if (cur_->right_child != nullptr) {
        cur_ = cur_->right_child;
        while (cur_->left_child != nullptr) {
          cur_ = cur_->left_child;
        }
      } else {
        while (cur_->parent != nullptr && cur_->parent->right_child == cur_) {
          cur_ = cur_->parent;
        }
        cur_ = cur_->parent;
      }
      return *this;
    }

    Iterator& operator--() {
      if (cur_ == nullptr) {
        return *this;
      }
      if (cur_->left_child != nullptr) {
        cur_ = cur_->left_child;
        while (cur_->right_child != nullptr) {
          cur_ = cur_->right_child;
        }
      } else {
        while (cur_->parent != nullptr && cur_->parent->left_child == cur_) {
          cur_ = cur_->parent;
        }
        cur_ = cur_->parent;
      }
      return *this;
    }
  };

  friend Treap Merge(Treap&&, Treap&&);
  friend std::pair<Treap, Treap> Split(Treap&& treap, int64_t x_0);

  Treap() : root_(nullptr) {
  }
  Treap(Node* root) : root_(root) {  // NOLINT
  }
  Treap(const Treap& other) = delete;
  Treap(Treap& other) = delete;
  Treap(Treap&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  Treap(const Treap&& other) = delete;

  Treap& operator=(Treap&& other) {
    root_ = other.root_;
    other.root_ = nullptr;
    return *this;
  }

  Treap CutLeftTreap() {
    if (root_ == nullptr) {
      return {nullptr};
    }
    Node* left = root_->left_child;
    CutLeftChild(root_);
    return {left};
  }

  Treap CutRightTreap() {
    if (root_ == nullptr) {
      return {nullptr};
    }
    Node* right = root_->right_child;
    CutRightChild(root_);
    return {right};
  }

  void SetLeftTreap(Treap&& other) {
    SetLeftChild(root_, other.root_);
    other.root_ = nullptr;
  }

  void SetRightTreap(Treap&& other) {
    SetRightChild(root_, other.root_);
    other.root_ = nullptr;
  }

  ~Treap() {
    Node* cur = root_;
    while (cur != nullptr) {
      if (cur->left_child != nullptr) {
        cur = cur->left_child;
      } else if (cur->right_child != nullptr) {
        cur = cur->right_child;
      } else {
        Node* temp = cur;
        cur = cur->parent;
        if (cur != nullptr && cur->left_child == temp) {
          cur->left_child = nullptr;
        } else if (cur != nullptr) {
          cur->right_child = nullptr;
        }
        delete temp;
      }
    }
    root_ = nullptr;
    cur = nullptr;
  }

  operator bool() const {  // NOLINT
    return root_ != nullptr;
  }

  void Insert(int64_t key, int64_t priority) {
    if (Contain(key)) {
      return;
    }
    auto [treap_1, treap_2] = Split(std::move(*this), key);
    *this = Merge(Merge(std::move(treap_1), Treap(new Node(key, priority))), std::move(treap_2));
  }

  void Erase(int64_t key) {
    auto [treap_left, treap_temp] = Split(std::move(*this), key);
    auto [trash, treap_right] = Split(std::move(treap_temp), key + 1);
    *this = Merge(std::move(treap_left), std::move(treap_right));
  }

  int64_t Query(int64_t l, int64_t r) {
    auto [treap_l, treap_future_center] = Split(std::move(*this), l);
    auto [treap_center, treap_r] = Split(std::move(treap_future_center), r + 1);
    int64_t ans = 0;
    if (treap_center.root_ != nullptr) {
      ans = treap_center.root_->size;
    }
    *this = Merge(Merge(std::move(treap_l), std::move(treap_center)), std::move(treap_r));
    return ans;
  }

  Node* LowerBound(int64_t key) {
    if (root_ == nullptr) {
      return nullptr;
    }
    Node* cur = root_;
    Node* last = nullptr;
    while (true) {
      if (cur->key < key) {
        if (cur->right_child != nullptr) {
          cur = cur->right_child;
        } else {
          return last;
        }
      } else {
        last = cur;
        if (cur->left_child != nullptr) {
          cur = cur->left_child;
        } else {
          return last;
        }
      }
    }
  }

  Node* UpperBound(int64_t key) {
    if (root_ == nullptr) {
      return nullptr;
    }
    Node* cur = root_;
    Node* last = nullptr;
    while (true) {
      if (cur->key <= key) {
        if (cur->right_child != nullptr) {
          cur = cur->right_child;
        } else {
          return last;
        }
      } else {
        last = cur;
        if (cur->left_child != nullptr) {
          cur = cur->left_child;
        } else {
          return last;
        }
      }
    }
  }

  Node* Previous(int64_t key) {
    if (root_ == nullptr) {
      return nullptr;
    }
    Node* cur = root_;
    Node* last = nullptr;
    while (true) {
      if (cur->key > key) {
        if (cur->left_child != nullptr) {
          cur = cur->left_child;
        } else {
          return last;
        }
      } else if (cur->key == key) {
        return cur;
      } else {
        last = cur;
        if (cur->right_child != nullptr) {
          cur = cur->right_child;
        } else {
          return last;
        }
      }
    }
  }

  Node* Kth(int64_t k) {
    k += 1;
    if (root_ == nullptr) {
      return nullptr;
    }
    Node* cur = root_;
    while (true) {
      if (cur->size + 1 < k) {
        return nullptr;
      }
      int64_t left = 0;
      if (cur->left_child != nullptr) {
        left = cur->left_child->size + 1;
      }
      if (left < k - 1) {
        cur = cur->right_child;
        k -= left + 1;
      } else if (left == k - 1) {
        return cur;
      } else {
        cur = cur->left_child;
      }
    }
  }

  bool Contain(int64_t key) {
    if (root_ == nullptr) {
      return false;
    }
    Node* l_b = LowerBound(key);
    return (l_b != nullptr && l_b->key == key);
  }
};

Treap Merge(Treap&& tree_first, Treap&& tree_second) {
  if (tree_first.root_ == nullptr) {
    return std::move(tree_second);
  }
  if (tree_second.root_ == nullptr) {
    return std::move(tree_first);
  }
  if (tree_second.root_->priority > tree_first.root_->priority) {
    Treap left = tree_second.CutLeftTreap();
    tree_second.SetLeftTreap(Merge(std::move(tree_first), std::move(left)));
    return std::move(tree_second);
  }
  Treap right = tree_first.CutRightTreap();
  tree_first.SetRightTreap(Merge(std::move(right), std::move(tree_second)));
  return std::move(tree_first);
}

std::pair<Treap, Treap> Split(Treap&& treap, int64_t x_0) {
  if (treap.root_ == nullptr) {
    return {Treap(nullptr), Treap(nullptr)};
  }
  if (treap.root_->key < x_0) {
    Treap tmp = treap.CutRightTreap();
    auto [treap_1, treap_2] = Split(std::move(tmp), x_0);
    treap.SetRightTreap(std::move(treap_1));
    return {std::move(treap), std::move(treap_2)};
  }
  Treap tmp = treap.CutLeftTreap();
  auto [treap_1, treap_2] = Split(std::move(tmp), x_0);
  treap.SetLeftTreap(std::move(treap_2));
  return {std::move(treap_1), std::move(treap)};
}

int main() {
  Treap treap;
  int64_t k = 0;
  std::cin >> k;
  for (int64_t i = 0; i < k; ++i) {
    getchar();
    char c = '0';
    c = static_cast<char>(getchar());
    switch (c) {
      case '+': {
        int64_t a = 0;
        std::cin >> a;
        treap.Insert(a, rand() % 10000);
        break;
      }
      case '?': {
        int64_t l = 0;
        int64_t r = 0;
        std::cin >> l >> r;
        std::cout << treap.Query(l, r) << '\n';
        break;
      }
    }
  }
  return 0;
}
