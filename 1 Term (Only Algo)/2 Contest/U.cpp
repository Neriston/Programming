#include <iostream>

struct Node {
  int64_t value;
  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

class BST {
 public:
  Node* root = nullptr;
  Node* last = nullptr;
  void Insert(int value);
  void FirstMax();
  void Clear(Node* root);
  void Transplant(Node* from, Node* to);
  void Erase(Node* rem);
  Node* Minimum(Node* node);
  void PostOrder(Node* node);
};

void BST::PostOrder(Node* node) {
  if (node != nullptr) {
    PostOrder(node->left);
    PostOrder(node->right);
    std::cout << node->value << ' ';
  }
}

void BST::Insert(int value) {
  Node* parent = nullptr;
  Node* cur = root;
  auto elem = new Node;
  elem->value = value;
  if (root == nullptr) {
    root = elem;
    last = root;
    return;
  }
  if (last->value > value) {
    elem->parent = last;
    last->left = elem;
    last = elem;
    return;
  }
  if (last->value < value) {
    while (cur != nullptr) {
      parent = cur;
      if (value > cur->value) {
        cur = cur->right;
      } else if (value < cur->value) {
        cur = cur->left;
      } else {
        delete elem;
        return;
      }
    }
  }
  elem->parent = parent;
  last = elem;
  if (elem->parent == nullptr) {
    root = elem;
  } else {
    if (value > parent->value) {
      parent->right = elem;
    } else if (value < parent->value) {
      parent->left = elem;
    }
  }
}

void BST::Clear(Node* root) {
  if (root != nullptr) {
    if ((root->left) != nullptr) {
      Clear(root->left);
    }
    if ((root->right) != nullptr) {
      Clear(root->right);
    }
  }
  delete root;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  BST tree;
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int num;
    std::cin >> num;
    tree.Insert(num);
  }
  tree.PostOrder(tree.root);
  tree.Clear(tree.root);
  return 0;
}