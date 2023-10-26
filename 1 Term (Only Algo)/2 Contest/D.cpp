#include <iostream>
#ifndef HEAP
#define HEAP

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

template <class T>
int Parent(T i) {
  return (i - 1) / 2;
}

template <class T>
int LeftChild(T i) {
  return 2 * i + 1;
}

template <class T>
int RightChild(T i) {
  return 2 * i + 2;
}

template <class T>
void SiftDown(T* begin, T* end, int i) {
  int size = end - begin;
  int left = LeftChild(i);
  int right = RightChild(i);
  int largest = i;
  if (left < size && begin[largest] < begin[left]) {
    largest = left;
  }
  if (right < size && begin[largest] < begin[right]) {
    largest = right;
  }
  if (largest != i) {
    Swap(begin[i], begin[largest]);
    SiftDown(begin, end, largest);
  }
  return;
}

template <class T>
void MakeHeap(T* begin, T* end) {
  int size = end - begin;
  for (int i = (size - 1) / 2; i >= 0; --i) {
    SiftDown(begin, end, i);
  }
}

template <class T>
void SortHeap(T* begin, T* end) {
  int size = end - begin;
  MakeHeap(begin, end);
  for (int i = size - 1; i >= 1; --i) {
    Swap(begin[0], begin[i]);
    --size;
    end = begin + size;
    SiftDown(begin, end, 0);
  }
}
#endif