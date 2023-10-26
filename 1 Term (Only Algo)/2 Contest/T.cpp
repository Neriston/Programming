#include <iostream>

struct Node {
  int64_t value;
  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;
};

class BST {
 public:
  Node *root = nullptr;
  void Insert(int value);
  void Clear(Node *root);
  void Morris();
};

void BST::Morris() {
  if (this->root == nullptr) {
    return;
  }
  Node *cur = this->root;
  while (cur != nullptr) {
    if (cur->left == nullptr) {
      std::cout << cur->value << '\n';
      cur = cur->right;
    } else {
      Node *prev = cur->left;
      while (prev->right != nullptr && prev->right != cur) {
        prev = prev->right;
      }
      if (prev->right == nullptr) {
        prev->right = cur;
        cur = cur->left;
      } else {
        prev->right = nullptr;
        std::cout << cur->value << '\n';
        cur = cur->right;
      }
    }
  }
}

void BST::Insert(int value) {
  auto key = new Node;
  key->value = value;
  Node *parent = nullptr;
  Node *current = this->root;
  while (current != nullptr) {
    parent = current;
    if ((key->value) < (current->value)) {
      current = current->left;
    } else if ((key->value) > (current->value)) {
      current = current->right;
    } else {
      delete key;
      return;
    }
  }
  key->parent = parent;
  if (!parent) {
    this->root = key;
  } else if (key->value < parent->value) {
    parent->left = key;
  } else {
    parent->right = key;
  }
}

void BST::Clear(Node *root) {
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
  int number;
  while ((std::cin >> number) && number != 0) {
    tree.Insert(number);
  }
  tree.Morris();
  tree.Clear(tree.root);
  return 0;
}