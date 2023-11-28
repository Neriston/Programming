#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

struct Node {
  std::unordered_map<char, Node*> edges;
  Node* suf_ref = nullptr;
  size_t len = 0;
  size_t end_pos = 0;
  size_t num = 0;
  bool visited = false;
  Node() = default;
};

class SuffixAutomaton {
  Node* root_ = new Node();
  Node* last_ = nullptr;
  int cnt_ = 0;

 public:
  Node* Clone(Node*, const char&, Node*, const Node*&);
  void AddSymbol(const char&);
  explicit SuffixAutomaton(const std::string& str) {
    for (const auto& elem : str) {
      AddSymbol(elem);
    }
  }
  friend std::ostream& operator<<(std::ostream&, const SuffixAutomaton&);
  ~SuffixAutomaton() {
    std::cout << cnt_ + 1 << '\n';
    std::queue<Node*> queue;
    std::vector<Node*> removable;
    queue.emplace(root_);
    while (!queue.empty()) {
      Node* node = queue.front();
      queue.pop();
      if (!node->visited) {
        removable.emplace_back(node);
        for (const auto& elem : node->edges) {
          std::cout << node->num << ' ' << elem.first << ' ' << elem.second->num << '\n';
          queue.emplace(elem.second);
        }
        node->visited = true;
      }
    }
    for (const auto& elem : removable) {
      delete elem;
    }
  }
};

Node* SuffixAutomaton::Clone(Node* parent, const char& symbol, Node* node, const Node*& copy_last) {
  Node* clone = new Node();
  ++cnt_;
  clone->edges = node->edges;
  clone->suf_ref = node->suf_ref;
  clone->len = parent->len + 1;
  clone->end_pos = copy_last->end_pos;
  clone->num = cnt_;
  node->suf_ref = clone;
  while (parent != nullptr && parent->edges[symbol] == node) {
    parent->edges[symbol] = clone;
    parent = parent->suf_ref;
  }
  return clone;
}

void SuffixAutomaton::AddSymbol(const char& symbol) {
  Node* new_node = new Node();
  ++cnt_;
  if (root_->edges.empty()) {
    new_node->len = 1;
    new_node->end_pos = 1;
    new_node->suf_ref = root_;
    last_ = new_node;
    root_->edges[symbol] = new_node;
    new_node->num = cnt_;
    return;
  }
  new_node->len = last_->len + 1;
  new_node->end_pos = last_->end_pos + 1;
  new_node->num = cnt_;
  const Node* copy_last = last_;
  while (last_ != nullptr && last_->edges.find(symbol) == last_->edges.end()) {
    last_->edges[symbol] = new_node;
    last_ = last_->suf_ref;
  }
  if (last_ == nullptr) {
    new_node->suf_ref = root_;
  } else if (last_->len + 1 == last_->edges[symbol]->len) {
    new_node->suf_ref = last_->edges[symbol];
  } else {
    new_node->suf_ref = Clone(last_, symbol, last_->edges[symbol], copy_last);
  }
  last_ = new_node;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string str;
  std::cin >> str;
  SuffixAutomaton suf_auto(str);
  return 0;
}