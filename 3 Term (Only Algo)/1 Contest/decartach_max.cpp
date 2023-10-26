#include <iostream>
#include <vector>

struct Point {
  int key = 0;
  int priority = 0;

  Point() {};

  Point(int key, int priority) : key(key), priority(priority) {};
};

struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  int key = 0;
  int priority = 0;

  Node() {};

  Node(Point point) : key(point.key), priority(point.priority) {};
};

class Treap {
  Node* root = nullptr;
  Node* last_added = nullptr;

 public:
  Treap() {};

  Treap(Node* root, Node* last_added = nullptr) : root(root), last_added(last_added) {};

  void Build(Node* node, const std::vector<Point>& points) {
    for (size_t i = 1; i < points.size(); ++i) {
      Node* now_node = new Node(points[i]);
      if (node->priority > now_node->priority) {
        node->right = now_node;
        now_node->parent = node;
      } else {
        while (node->parent != nullptr && node->priority < now_node->priority) {
          node = node->parent;
        }
        if (node->priority > now_node->priority) {
          Node* right_son = node->right;
          node->right = now_node;
          now_node->parent = node;
          now_node->left = right_son;
          right_son->parent = now_node;
        }
        else {  // node.parent == nullptr
          now_node->left = node;
          node->parent = now_node;
          root = now_node;
        }
      }
      node = now_node;
    }
  }
};


std::istream& operator>>(std::istream& is, std::vector<Point>& points) {
  for (size_t i = 0; i < points.size(); ++i) {
    is >> points[i].key >> points[i].priority;
  }
  return is;
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Point> points(n);
  std::cin >> points;
  Node root(points[0]);
  Treap tree(&root, &root);
  tree.Build(&root, points);
}