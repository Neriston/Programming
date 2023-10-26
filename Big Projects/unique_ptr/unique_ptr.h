#ifndef UNIQUE_H
#define UNIQUE_H

template <class T>
class UniquePtr {
  T* ptr_;

 public:
  UniquePtr() noexcept;
  explicit UniquePtr(T*) noexcept;
  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;
  UniquePtr(UniquePtr&&) noexcept;
  UniquePtr& operator=(UniquePtr&&) noexcept;
  ~UniquePtr();
  T* Release();
  void Reset(T* ptr = nullptr);
  void Swap(UniquePtr&) noexcept;
  T* Get() const;
  T& operator*() const;
  T* operator->() const;
  explicit operator bool() const;
};

template <class T>
UniquePtr<T>::UniquePtr() noexcept : ptr_(nullptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(T* ptr) noexcept : ptr_(ptr) {
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& ptr) noexcept : ptr_(ptr.ptr_) {
  ptr.ptr_ = nullptr;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& ptr) noexcept {
  if (this != &ptr) {
    delete ptr_;
    ptr_ = ptr.ptr_;
    ptr.ptr_ = nullptr;
  }
  return *this;
}

template <class T>
UniquePtr<T>::~UniquePtr() {
  delete ptr_;
}

template <class T>
T* UniquePtr<T>::Release() {
  T* temp = ptr_;
  ptr_ = nullptr;
  return temp;
}

template <class T>
void UniquePtr<T>::Reset(T* ptr) {
  delete ptr_;
  ptr_ = ptr;
}

template <class T>
void UniquePtr<T>::Swap(UniquePtr<T>& ptr) noexcept {
  T* temp = std::move(ptr.ptr_);
  ptr.ptr_ = std::move(ptr_);
  ptr_ = std::move(temp);
}

template <class T>
T* UniquePtr<T>::Get() const {
  return ptr_;
}

template <class T>
T& UniquePtr<T>::operator*() const {
  return *ptr_;
}

template <class T>
T* UniquePtr<T>::operator->() const {
  return ptr_;
}

template <class T>
UniquePtr<T>::operator bool() const {
  return ptr_;
}
#endif