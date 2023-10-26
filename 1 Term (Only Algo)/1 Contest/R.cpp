#ifndef STATIC
#define STATIC
template <class T>
T* Partition(T* begin, T* end) {
  T p_value = *(begin + (end - begin) / 2);
  T* i = begin;
  T* j = end;
  while (i <= j) {
    while (*i < p_value) {
      ++i;
    }
    while (p_value < *j) {
      --j;
    }
    if (j < i) {
      break;
    }
    T temp = *i;
    *i = *j;
    *j = temp;
    ++i;
    --j;
  }
  return j;
}

template <class T>
void KthElement(T* begin, T* k, T* end) {
  T* l = begin;
  T* r = end - 1;
  while (l < r - 1) {
    T* mid = Partition(l, r);
    if (mid == k) {
      return;
    } else if (k < mid) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }
}
#endif