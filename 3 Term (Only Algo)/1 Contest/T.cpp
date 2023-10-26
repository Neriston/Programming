#include <iostream>
#include <vector>

struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  int priority = 0;
  int value = 0;
  int size = 0;
  int64_t sum = 0;

  Node() = default;

  explicit Node(int x) : value(x) {
    priority = std::rand();
    size = 1;
    sum = value;
  }
};

int GetSize(const Node* node) {
  return node == nullptr ? 0 : node->size;
}

void UpdateSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
  }
}

int64_t GetSum(const Node* node) {
  return node == nullptr ? 0 : node->sum;
}

void UpdateSum(Node* node) {
  if (node != nullptr) {
    node->sum = GetSum(node->left) + GetSum(node->right) + node->value;
  }
}

class Treap {
  Node* root_ = nullptr;

  friend class TwoTreapsEvenAndOdd;

 public:
  Treap() = default;

  ~Treap() {
    while (root_ != nullptr) {
      Delete(root_, 0);
    }
  }

  Node* Merge(Node* t1, Node* t2) {
    if (t1 == nullptr) {
      return t2;
    }
    if (t2 == nullptr) {
      return t1;
    }
    if (t2->priority < t1->priority) {
      t2->left = Merge(t1, t2->left);
      UpdateSize(t2);
      UpdateSum(t2);
      return t2;
    }
    t1->right = Merge(t1->right, t2);
    UpdateSize(t1);
    UpdateSum(t1);
    return t1;
  }

  std::pair<Node*, Node*> Split(Node* t, int k) {
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    int left_size = GetSize(t->left);
    if (left_size < k) {
      auto pair = Split(t->right, k - left_size - 1);
      t->right = pair.first;
      UpdateSize(t);
      UpdateSum(t);
      return {t, pair.second};
    }
    auto pair = Split(t->left, k);
    t->left = pair.second;
    UpdateSize(t);
    UpdateSum(t);
    return {pair.first, t};
  }

  void Insert(int k, int value) {
    Node* node = new Node(value);
    if (root_ == nullptr) {
      root_ = node;
      return;
    }
    std::pair<Node*, Node*> pair = Split(root_, k);
    root_ = Merge(Merge(pair.first, node), pair.second);
  }

  void Delete(Node* now_node, int k) {
    auto p1 = Split(now_node, k);
    auto p2 = Split(p1.second, 1);
    root_ = Merge(p1.first, p2.second);
    delete p2.first;
  }

  int64_t Sum(const int& l, const int& r) {
    auto p1 = Split(root_, l);
    auto p2 = Split(p1.second, r - l);
    int64_t sum = 0;
    sum = GetSum(p2.first);
    root_ = Merge(Merge(p1.first, p2.first), p2.second);
    return sum;
  }
};

class TwoTreapsEvenAndOdd {
  Treap even_ = Treap();
  Treap odd_ = Treap();

 public:
  TwoTreapsEvenAndOdd() = default;

  explicit TwoTreapsEvenAndOdd(const std::vector<int>& vector) {
    for (size_t i = 0; i < vector.size(); ++i) {
      if (i % 2 == 0) {
        odd_.Insert(static_cast<int>(i) / 2, vector[i]);  //  нечетные
      } else {
        even_.Insert(static_cast<int>(i) / 2, vector[i]);  //  четные
      }
    }
  }
  int64_t Sum(const int& l, const int& r) {
    return odd_.Sum(l / 2, (r + 1) / 2) + even_.Sum((l - 1) / 2, r / 2);
  }

  void Swapper(const int& l, const int& r) {
    auto p1 = odd_.Split(odd_.root_, l / 2);
    auto p2 = odd_.Split(p1.second, (r + 1) / 2 - l / 2);
    auto p3 = even_.Split(even_.root_, (l - 1) / 2);
    auto p4 = even_.Split(p3.second, r / 2 - (l - 1) / 2);
    odd_.root_ = odd_.Merge(odd_.Merge(p1.first, p4.first), p2.second);
    even_.root_ = even_.Merge(odd_.Merge(p3.first, p2.first), p4.second);
  }
};

std::istream& operator>>(std::istream& is, std::vector<int>& vector) {
  for (size_t i = 0; i < vector.size(); ++i) {
    is >> vector[i];
  }
  return is;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  int n = 0;
  int m = 0;
  int cnt = 0;
  std::cin >> n >> m;
  while (n != 0 && m != 0) {
    ++cnt;
    std::cout << "Swapper " << cnt << ":\n";
    std::vector<int> numbers(n, 0);
    std::cin >> numbers;
    TwoTreapsEvenAndOdd trees(numbers);
    for (int i = 0; i < m; ++i) {
      int query = 0;
      int first = 0;
      int second = 0;
      std::cin >> query >> first >> second;
      if (query == 1) {
        trees.Swapper(first, second);
      } else if (query == 2) {
        std::cout << trees.Sum(first, second) << '\n';
      }
    }
    std::cin >> n >> m;
  }
  return 0;
}