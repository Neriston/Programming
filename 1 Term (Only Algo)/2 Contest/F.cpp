#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  Node* next = nullptr;
  int64_t value;
};

class Deque {
 private:
  Node* last_ = nullptr;
  Node* first_ = nullptr;
  size_t size_deque_ = 0;

 public:
  void PushFront(int64_t val);
  void PushBack(int64_t val);
  void PopFront();
  void PopBack();
  int Size();
  void Front();
  void Back();
  void Pop();
  void Clear();
  void Exit();
};

void Deque::PushFront(int64_t val) {
  auto new_node = new Node;
  new_node->value = val;
  new_node->prev = this->last_;
  new_node->next = nullptr;
  if (this->last_) {
    this->last_->next = new_node;
  }
  if (!this->first_) {
    this->first_ = new_node;
  }
  this->last_ = new_node;
  ++(this->size_deque_);
  std::cout << "ok\n";
}

void Deque::PushBack(int64_t val) {
  auto new_node = new Node;
  new_node->value = val;
  new_node->prev = nullptr;
  new_node->next = this->first_;
  if (this->first_) {
    this->first_->prev = new_node;
  }
  if (!this->last_) {
    this->last_ = new_node;
  }
  this->first_ = new_node;
  ++(this->size_deque_);
  std::cout << "ok\n";
}

void Deque::PopFront() {
  if (this->size_deque_ == 0) {
    std::cout << "error\n";
    return;
  }
  if (this->size_deque_ == 1) {
    int value = this->last_->value;
    delete this->last_;
    this->last_ = nullptr;
    this->first_ = nullptr;
    std::cout << value << '\n';
    --(this->size_deque_);
    return;
  }
  Node* temp = this->last_;
  int64_t value = this->last_->value;
  this->last_ = this->last_->prev;
  delete temp;
  --(this->size_deque_);
  std::cout << value << '\n';
}

void Deque::PopBack() {
  if (this->size_deque_ == 0) {
    std::cout << "error\n";
    return;
  }
  if (this->size_deque_ == 1) {
    int value = this->first_->value;
    delete this->first_;
    this->last_ = nullptr;
    this->first_ = nullptr;
    std::cout << value << '\n';
    --(this->size_deque_);
    return;
  }
  Node* temp = this->first_;
  int64_t value = this->first_->value;
  this->first_ = this->first_->next;
  delete temp;
  --(this->size_deque_);
  std::cout << value << '\n';
}

int Deque::Size() {
  return this->size_deque_;
}

void Deque::Front() {
  if (this->size_deque_ == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << this->last_->value << '\n';
}

void Deque::Back() {
  if (this->size_deque_ == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << this->first_->value << '\n';
}

void Deque::Pop() {
  if (this->size_deque_ == 1) {
    delete this->first_;
    this->last_ = nullptr;
    this->first_ = nullptr;
    --(this->size_deque_);
    return;
  }
  Node* temp = this->first_;
  this->first_ = this->first_->next;
  delete temp;
  --(this->size_deque_);
}

void Deque::Clear() {
  if (Size() > 1) {
    Pop();
    Clear();
  }
  if (Size() == 1) {
    Pop();
  }
}

void Deque::Exit() {
  std::cout << "bye";
}

int main() {
  auto array = new char[20]{};
  int k;
  Deque deque;
  std::cin >> k;
  for (int64_t i = 0; i < k; ++i) {
    scanf("%s", array);
    if (strcmp(array, "push_back") == 0) {
      int a;
      std::cin >> a;
      deque.PushBack(a);
    } else if (strcmp(array, "push_front") == 0) {
      int a;
      std::cin >> a;
      deque.PushFront(a);
    } else if (strcmp(array, "pop_front") == 0) {
      deque.PopFront();
    } else if (strcmp(array, "pop_back") == 0) {
      deque.PopBack();
    } else if (strcmp(array, "front") == 0) {
      deque.Front();
    } else if (strcmp(array, "back") == 0) {
      deque.Back();
    } else if (strcmp(array, "size") == 0) {
      std::cout << deque.Size() << '\n';
    } else if (strcmp(array, "clear") == 0) {
      deque.Clear();
      std::cout << "ok\n";
    } else if (strcmp(array, "exit") == 0) {
      deque.Exit();
    }
  }
  deque.Clear();
  delete[] array;
}