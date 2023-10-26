#ifndef BIN_H
#define BIN_H

template <class T>
const T* LowerBound(const T* begin, const T* end, const T& value) {
  const T* l = begin - 1;
  const T* r = end;
  while (l < r - 1) {
    const T* mid = l + (r - l) / 2;
    if (*mid < value) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (*(end - 1) < value) {
    return end;
  }
  return r;
}
template <class T>
const T* UpperBound(const T* begin, const T* end, const T& value) {
  const T* l = begin - 1;
  const T* r = end;
  while (l < r - 1) {
    const T* mid = l + (r - l) / 2;
    if (!(value < *mid)) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (!(value < *(end - 1))) {
    return end;
  }
  return r;
}
template <class T>
bool BinarySearch(const T* begin, const T* end, const T& value) {
  const T* l = begin - 1;
  const T* r = end;
  while (l < r - 1) {
    const T* mid = l + (r - l) / 2;
    if (*mid < value) {
      l = mid;
    } else {
      r = mid;
    }
  }
  if (*(end - 1) < value) {
    return false;
  }
  return !(*r < value) && (!(value < *r));
}
#endif