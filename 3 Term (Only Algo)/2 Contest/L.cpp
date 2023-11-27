#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

struct Node {
  std::unordered_map<char, Node*> edges;
  bool is_terminal = false;
  Node* suff_ref = nullptr;
  Node* exit_link = nullptr;
  std::string str = " ";

  Node() = default;
  Node(const std::unordered_map<char, Node*>& edges, const bool& is_terminal, Node*& suff_ref, Node*& exit_link,
       std::string& str)
      : edges(edges), is_terminal(is_terminal), suff_ref(suff_ref), exit_link(exit_link), str(str) {
  }
};

class Trie {
  Node* root_ = new Node();

  struct HelpForSufRef {
    char symbol = ' ';
    Node* parent = nullptr;
    Node* node = nullptr;

    HelpForSufRef() = default;
    HelpForSufRef(const char& symbol, Node*& parent, Node*& node) : symbol(symbol), parent(parent), node(node) {
    }
  };

 public:
  Node* ShowRoot() const {
    return root_;
  }
  Trie() = default;
  ~Trie();
  bool Find(const std::string&) const;
  void Insert(const std::string&);
  void ClearNode(Node*);
  void BuildSuffixReferences();
  void BuildExitLinks();
  Node* NextState(Node*&, const char&) const;
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
      new_node->str = now_node->str;
      edge = new_node;
    }
    now_node = edge;
  }
  now_node->is_terminal = true;
  now_node->str = string;
}

void Trie::BuildSuffixReferences() {
  std::queue<HelpForSufRef> queue;
  for (auto& element : root_->edges) {
    queue.emplace(element.first, root_, element.second);
  }
  HelpForSufRef temp = {};
  while (!queue.empty()) {
    temp = queue.front();
    queue.pop();
    Node* suff_ref_parent = temp.parent->suff_ref;
    while (suff_ref_parent != nullptr && suff_ref_parent->edges.find(temp.symbol) == suff_ref_parent->edges.end()) {
      suff_ref_parent = suff_ref_parent->suff_ref;
    }
    temp.node->suff_ref = (suff_ref_parent == nullptr ? root_ : suff_ref_parent->edges[temp.symbol]);
    for (auto& pair : temp.node->edges) {
      queue.emplace(pair.first, temp.node, pair.second);
    }
  }
}

void Trie::BuildExitLinks() {
  std::queue<Node*> queue;
  for (auto& element : root_->edges) {
    queue.emplace(element.second);
  }
  Node* node = nullptr;
  while (!queue.empty()) {
    node = queue.front();
    queue.pop();
    Node* suff = node->suff_ref;
    if (suff != root_) {
      node->exit_link = (suff->is_terminal ? suff : suff->exit_link);
    }
    for (auto& pair : node->edges) {
      queue.emplace(pair.second);
    }
  }
}

Node* Trie::NextState(Node*& node, const char& symbol) const {
  while (node != nullptr && node->edges.find(symbol) == node->edges.end()) {
    node = node->suff_ref;
  }
  return (node == nullptr ? root_ : node->edges[symbol]);
}

void SaveEntries(const int& index, Node* node, std::unordered_map<std::string, std::vector<int>>& num_patterns) {
  if (!node->is_terminal) {
    node = node->exit_link;
  }
  while (node != nullptr) {
    num_patterns[node->str].emplace_back(index - static_cast<int>(node->str.length()) + 2);
    node = node->exit_link;
  }
}

void AhoCorasick(const std::string& main_str, const int& n) {
  Trie trie;
  std::string pattern;
  std::unordered_map<std::string, std::vector<int>> num_patterns;
  std::vector<std::string> patterns(n, " ");
  for (int i = 0; i < n; ++i) {
    std::cin >> pattern;
    patterns[i] = pattern;
    trie.Insert(pattern);
  }
  trie.BuildSuffixReferences();
  trie.BuildExitLinks();
  Node* node = trie.ShowRoot();
  for (int i = 0; i < static_cast<int>(main_str.length()); ++i) {
    node = trie.NextState(node, main_str[i]);
    SaveEntries(i, node, num_patterns);
  }
  for (const auto& str : patterns) {
    std::cout << num_patterns[str].size() << ' ';
    for (const auto& ind : num_patterns[str]) {
      std::cout << ind << ' ';
    }
    std::cout << '\n';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string main_str;
  int n = 0;
  std::cin >> main_str >> n;
  AhoCorasick(main_str, n);
  return 0;
}