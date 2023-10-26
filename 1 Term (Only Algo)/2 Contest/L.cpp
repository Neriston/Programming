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
  void Insert(int value);
  int TreeHeight(Node* root);
  void Clear(Node* root);
};

void BST::Insert(int value) {
  auto key = new Node;
  key->value = value;
  Node* parent = nullptr;
  Node* current = this->root;
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

int BST::TreeHeight(Node* root) {
  int l = 0;
  int r = 0;
  int h = 0;
  if (root != nullptr) {
    l = TreeHeight(root->left);
    r = TreeHeight(root->right);
    h = ((l > r) ? l : r) + 1;
  }
  return h;
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
  BST tree;
  int number;
  while ((std::cin >> number) && number != 0) {
    tree.Insert(number);
  }
  std::cout << tree.TreeHeight(tree.root);
  tree.Clear(tree.root);
}