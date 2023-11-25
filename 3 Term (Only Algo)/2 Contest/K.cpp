#include <iostream>
#include <string>
#include <unordered_map>

struct Node {
  std::unordered_map<char, Node*> edges;
  bool is_terminal = false;

  Node() = default;
};

class Trie {
  Node* root_ = new Node();

 public:
  ~Trie();
  bool Find(const std::string&) const;
  void Insert(const std::string&);
  void ClearNode(Node*);
};

Trie::~Trie() {
  if (root_ != nullptr) {
    for (const auto& edge : root_->edges) {
      ClearNode(edge.second);
    }
  }
  delete root_;
}

void Trie::ClearNode(Node* node) {
  if (node != nullptr) {
    for (const auto& edge : node->edges) {
      ClearNode(edge.second);
    }
  }
  delete node;
}

bool Trie::Find(const std::string& string) const {
  Node* now_node = root_;
  for (const auto& symbol : string) {
    auto edge = now_node->edges[symbol];
    if (edge == nullptr) {
      return false;
    }
    now_node = edge;
  }
  return true;
}

void Trie::Insert(const std::string& string) {
  Node* now_node = root_;
  for (const auto& symbol : string) {
    auto edge = now_node->edges[symbol];
    if (edge == nullptr) {
      Node* new_node = new Node();
      now_node->edges[symbol] = new_node;
      now_node = new_node;
      edge = new_node;
    }
    now_node = edge;
  }
  now_node->is_terminal = true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  char operation = ' ';
  Trie trie;
  std::string string;
  while (std::cin >> operation && operation != '#') {
    std::cin >> string;
    if (operation == '+') {
      trie.Insert(string);
    } else {
      bool flag = trie.Find(string);
      if (flag) {
        std::cout << "YES\n";
      } else {
        std::cout << "NO\n";
      }
    }
  }
  return 0;
}