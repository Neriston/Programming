#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  int value;
};

class Stack {

 private:
  Node* last_ = nullptr;
  size_t size_stack_ = 0;

 public:
  void Push(int val);
  int Pop();
  int Size();
  void Clear();
};

void Stack::Push(int val) {
  auto new_node = new Node;
  new_node->value = val;
  new_node->prev = this->last_;
  this->last_ = new_node;
  ++(this->size_stack_);
}

int Stack::Pop() {
  if (this->size_stack_ == 0) {
    return 0;
  }
  Node* temp = this->last_;
  int value = this->last_->value;
  this->last_ = this->last_->prev;
  delete temp;
  --(this->size_stack_);
  return value;
}

void Stack::Clear() {
  if (Size() > 1) {
    Pop();
    //--(this->size_stack_);
    Clear();
  }
  if (Size() == 1) {
    Pop();
    //--(this->size_stack_);
  }
}

int Stack::Size() {
  return this->size_stack_;
}

int main() {
  Stack stack;
  char array[1000001];
  std::cin.get(array, 1000001);
  for (size_t i = 0; i < strlen(array); ++i) {
    if (array[i] == '(' || array[i] == '{' || array[i] == '[') {
      stack.Push(array[i]);
    } else if (array[i] == ')') {
      char now = stack.Pop();
      if (now != '(') {
        std::cout << "NO";
        stack.Clear();
        return 0;
      }
    } else if (array[i] == '}') {
      char now = stack.Pop();
      if (now != '{') {
        std::cout << "NO";
        stack.Clear();
        return 0;
      }
    } else {
      char now = stack.Pop();
      if (now != '[') {
        std::cout << "NO";
        stack.Clear();
        return 0;
      }
    }
  }
  if (stack.Size() == 0) {
    std::cout << "YES";
  } else {
    stack.Clear();
    std::cout << "NO";
  }
  return 0;
}