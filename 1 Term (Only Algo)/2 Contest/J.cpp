#include <iostream>
#include <cstring>

struct Node {
  Node* prev = nullptr;
  int value = 0;
  int min = 0;
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
  int Front();
  int Min();
};

int Stack::Front() {
  int temp = Pop();
  Push(temp);
  return temp;
}

void Stack::Push(int val) {
  auto new_node = new Node;
  new_node->value = val;
  if (size_stack_ == 0) {
    this->last_ = new_node;
    this->last_->value = val;
    this->last_->min = val;
    ++(this->size_stack_);
    return;
  }
  if (this->last_->min > val) {
    new_node->min = val;
  } else {
    new_node->min = this->last_->min;
  }
  new_node->prev = this->last_;
  this->last_ = new_node;
  ++(this->size_stack_);
}

int Stack::Pop() {
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
    Clear();
  }
  if (Size() == 1) {
    Pop();
  }
}

int Stack::Size() {
  return this->size_stack_;
}

int Stack::Min() {
  return this->last_->min;
}

class Queue {
 public:
  Stack stack1;
  Stack stack2;
  void Enqueue(int val);
  int Dequeue();
  int Size();
  int Front();
  void Clear();
  int Min();
};

int Queue::Front() {
  if (stack2.Size() == 0) {
    size_t len = stack1.Size();
    for (size_t i = 0; i < len; ++i) {
      int temp = stack1.Pop();
      stack2.Push(temp);
    }
    return stack2.Front();
  }
  return stack2.Front();
}

void Queue::Enqueue(int val) {
  stack1.Push(val);
}

int Queue::Dequeue() {
  if (stack2.Size() == 0) {
    size_t len = stack1.Size();
    for (size_t i = 0; i < len; ++i) {
      int temp = stack1.Pop();
      stack2.Push(temp);
    }
    return stack2.Pop();
  }
  return stack2.Pop();
}

int Queue::Size() {
  return stack1.Size() + stack2.Size();
}

void Queue::Clear() {
  stack1.Clear();
  stack2.Clear();
}

int Queue::Min() {
  if (stack1.Size() == 0) {
    return stack2.Min();
  }
  if (stack2.Size() == 0) {
    return stack1.Min();
  }
  return std::min(stack1.Min(), stack2.Min());
}

int main() {
  auto array = new char[20]{};
  int k;
  Queue queue;
  std::cin >> k;
  for (int64_t i = 0; i < k; ++i) {
    scanf("%s", array);
    if (strcmp(array, "enqueue") == 0) {
      int a;
      std::cin >> a;
      queue.Enqueue(a);
      std::cout << "ok\n";
    } else if (strcmp(array, "dequeue") == 0) {
      if (queue.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Dequeue() << '\n';
      }
    } else if (strcmp(array, "front") == 0) {
      if (queue.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Front() << '\n';
      }
    } else if (strcmp(array, "size") == 0) {
      std::cout << queue.Size() << '\n';
    } else if (strcmp(array, "clear") == 0) {
      queue.Clear();
      std::cout << "ok\n";
    } else if (strcmp(array, "min") == 0) {
      if (queue.Size() == 0) {
        std::cout << "error\n";
      } else {
        std::cout << queue.Min() << '\n';
      }
    }
  }
  queue.Clear();
  delete[] array;
}