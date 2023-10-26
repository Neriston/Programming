#include <iostream>
#include <vector>
#include <fstream>
#include <string>

struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int priority = 0;
  int value = 0;
  int size = 0;

  Node() = default;

  explicit Node(int x) : value(x) {
    priority = std::rand();
    size = 1;
  }
};

int GetSize(Node* node) {
  if (node == nullptr) {
    return 0;
  }
  return node->size;
}

void UpdateSize(Node* node) {
  if (node != nullptr) {
    node->size = GetSize(node->left) + GetSize(node->right) + 1;
  }
}

class Treap {
  Node* root_ = nullptr;

 public:
  Treap() = default;

  explicit Treap(Node* root) : root_(root) {
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
      return t2;
    }
    t1->right = Merge(t1->right, t2);
    UpdateSize(t1);
    return t1;
  }

  std::pair<Node*, Node*> Split(Node* t, int k) {
    if (t == nullptr) {
      return {nullptr, nullptr};
    }
    int left_size = GetSize(t->left);
    if (left_size < k) {
      std::pair<Node*, Node*> pair = Split(t->right, k - left_size - 1);
      t->right = pair.first;
      UpdateSize(t);
      return {t, pair.second};
    }
    std::pair<Node*, Node*> pair = Split(t->left, k);
    t->left = pair.second;
    UpdateSize(t);
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

  void Query(int l, int r) {
    auto p1 = Split(root_, l);
    auto p2 = Split(p1.second, r - l);
    root_ = Merge(p2.first, Merge(p1.first, p2.second));
  }

  void TreePrint(Node* t) {
    if (t != nullptr) {
      TreePrint(t->left);
      std::cout << t->value << ' ';
      TreePrint(t->right);
    }
  }

  void Print() {
    TreePrint(root_);
  }

  void Delete(Node* now_node, int k) {
    auto p1 = Split(now_node, k);
    auto p2 = Split(p1.second, 1);
    root_ = Merge(p1.first, p2.second);
    delete p2.first;
  }

  void DeleteAll() {
    while (root_ != nullptr) {
      Delete(root_, 0);
    }
  }
};

int main() {
  int n = 0;
  int m = 0;
  std::cin >> n >> m;
  Treap tree;
  for (int i = 1; i <= n; ++i) {
    tree.Insert(i, i);
  }
  for (int i = 0; i < m; ++i) {
    int l = 0;
    int r = 0;
    std::cin >> l >> r;
    tree.Query(l - 1, r);
  }
  tree.Print();
  tree.DeleteAll();
  return 0;
}