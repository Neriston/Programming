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
  void SecondMax();
  void Clear(Node* root);
  void Transplant(Node* from, Node* to);
  void Erase(Node* rem);
  Node* Minimum(Node* node);
};

Node* BST::Minimum(Node* node) {
  if (node == nullptr || node->left == nullptr) {
    return node;
  }
  return Minimum(node->left);
}

void BST::Transplant(Node* from, Node* to) {
  if (from->parent == nullptr) {
    this->root = to;
  } else if (from == from->parent->left) {
    from->parent->left = to;
  } else {
    from->parent->right = to;
  }
  if (to != nullptr) {
    to->parent = from->parent;
  }
}

void BST::Erase(Node* rem) {
  if (rem == nullptr) {
    delete rem;
    return;
  }
  if (rem->parent == nullptr) {
    Node* temp = root->left;
    delete root;
    root = temp;
    root->parent = nullptr;
    return;
  }
  if (rem->left == nullptr) {
    Transplant(rem, rem->right);
    delete rem;
  } else if (rem->right == nullptr) {
    Transplant(rem, rem->left);
    delete rem;
  } else {
    Node* min = Minimum(rem->right);
    if (min->parent != rem) {
      Transplant(min, min->right);
      min->right = rem->right;
      min->right->parent = min;
    }
    Transplant(rem, min);
    min->left = rem->left;
    min->right->parent = min;
    delete rem;
  }
}

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

void BST::SecondMax() {
  Node* temp1 = root;
  while (temp1->right != nullptr) {
    temp1 = temp1->right;
  }
  Erase(temp1);
  Node* temp2 = root;
  while (temp2->right != nullptr) {
    temp2 = temp2->right;
  }
  std::cout << temp2->value;
}

int main() {
  BST tree;
  int number;
  while ((std::cin >> number) && number != 0) {
    tree.Insert(number);
  }
  tree.SecondMax();
  tree.Clear(tree.root);
  return 0;
}