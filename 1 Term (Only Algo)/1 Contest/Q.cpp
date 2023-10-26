#ifndef QUICKSORT
#define QUICKSORT
template <class T>
void Sort(T* begin, T* end) {
  int i = 0;
  int size = end - begin;
  int j = size - 1;
  T mid = begin[size / 2];
  while (i <= j) {
    while (begin[i] < mid) {
      i++;
    }
    while (mid < begin[j]) {
      j--;
    }
    if (!(j < i)) {
      T temp = begin[i];
      begin[i] = begin[j];
      begin[j] = temp;
      i++;
      j--;
    }
  }
  if (0 < j) {
    Sort(begin, begin + j + 1);
  }
  if (i < size) {
    Sort(begin + i, begin + size);
  }
}
#endif