#ifndef SHAREPTR
#define SHAREPTR

#include <stdexcept>
#include <iostream>

template <class T>
class SharedPtr {
  T* ptr_;
  int* strong_counter_;

 public:
  SharedPtr() noexcept;
  SharedPtr(T*) noexcept;  // NOLINT
  SharedPtr& operator=(const SharedPtr&);
  SharedPtr(const SharedPtr&) noexcept;
  SharedPtr& operator=(SharedPtr&&) noexcept;
  SharedPtr(SharedPtr&&) noexcept;
  ~SharedPtr();
  void Reset(T* ptr = nullptr);
  void Swap(SharedPtr<T>&);
  T* Get() const;
  int UseCount() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
};

template <class T>
SharedPtr<T>::SharedPtr() noexcept : ptr_(nullptr), strong_counter_(nullptr) {
}

template <class T>
SharedPtr<T>::SharedPtr(T* ptr) noexcept : ptr_(ptr) {
  if (ptr_ == nullptr) {
    strong_counter_ = nullptr;
  } else {
    strong_counter_ = new int(1);
  }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& ptr) {
  if (this != &ptr) {
    if (strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        --*strong_counter_;
      }
    }
    ptr_ = ptr.ptr_;
    if (ptr.strong_counter_ != nullptr) {
      ++*ptr.strong_counter_;
    }
    strong_counter_ = ptr.strong_counter_;
  }
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& ptr) noexcept : ptr_(ptr.ptr_) {
  if (ptr.strong_counter_ == nullptr) {
    strong_counter_ = nullptr;
  } else {
    ++*ptr.strong_counter_;
    strong_counter_ = ptr.strong_counter_;
  }
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& ptr) noexcept {
  if (this != &ptr) {
    if (strong_counter_ != nullptr) {
      if (*strong_counter_ == 1) {
        delete ptr_;
        delete strong_counter_;
      } else {
        --*strong_counter_;
      }
    }
    ptr_ = ptr.ptr_;
    strong_counter_ = ptr.strong_counter_;
    ptr.ptr_ = nullptr;
    ptr.strong_counter_ = nullptr;
  }
  return *this;
}

template <class T>
SharedPtr<T>::SharedPtr(SharedPtr&& ptr) noexcept : ptr_(ptr.ptr_), strong_counter_(ptr.strong_counter_) {
  ptr.ptr_ = nullptr;
  ptr.strong_counter_ = nullptr;
}

template <class T>
SharedPtr<T>::~SharedPtr() {
  if (strong_counter_ != nullptr) {
    --*strong_counter_;
    if (*strong_counter_ == 0) {
      delete ptr_;
      delete strong_counter_;
    }
  }
}

template <class T>
void SharedPtr<T>::Reset(T* ptr) {
  this->~SharedPtr();
  ptr_ = ptr;
  if (ptr_ == nullptr) {
    strong_counter_ = nullptr;
  } else {
    strong_counter_ = new int(1);
  }
}

template <class T>
void SharedPtr<T>::Swap(SharedPtr<T>& ptr) {
  std::swap(ptr_, ptr.ptr_);
  std::swap(strong_counter_, ptr.strong_counter_);
}

template <class T>
T* SharedPtr<T>::Get() const {
  return ptr_;
}

template <class T>
int SharedPtr<T>::UseCount() const {
  return ptr_ == nullptr ? 0 : *strong_counter_;
}

template <class T>
T& SharedPtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* SharedPtr<T>::operator->() const {
  return ptr_;
}

template <class T>
SharedPtr<T>::operator bool() const {
  return ptr_;
}
#endif