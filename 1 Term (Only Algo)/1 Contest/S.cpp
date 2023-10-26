#ifndef HEAP
#define HEAP
#include <cstddef>

template <class T>
void SiftDown(T* begin, T* end, size_t i) {
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;
  size_t largest = i;
  if ((begin + left) < end && *(begin + largest) < *(begin + left)) {
    largest = left;
  }
  if ((begin + right) < end && *(begin + largest) < *(begin + right)) {
    largest = right;
  }
  if (i < largest || largest < i) {
    T temp = *(begin + i);
    *(begin + i) = *(begin + largest);
    *(begin + largest) = temp;
    SiftDown(begin, end, largest);
  }
  return;
}

template <class T>
void SiftUp(T* begin, T* end, size_t i) {
  size_t parent = (i - 1) / 2;
  if (0 < i && *(begin + parent) < *(begin + i)) {
    T temp = *(begin + parent);
    *(begin + parent) = *(begin + i);
    *(begin + i) = temp;
    SiftUp(begin, end, parent);
  }
}

template <class T>
void PushHeap(T* begin, T* end) {
  size_t elem = end - 1 - begin;
  SiftUp(begin, end, elem);
}

template <class T>
void PopHeap(T* begin, T* end) {
  size_t i = 0;
  T temp = *begin;
  *begin = *(end - 1);
  *(end - 1) = temp;
  SiftDown(begin, end - 1, i);
}
#endif