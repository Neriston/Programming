#ifndef MERGE
#define MERGE
template <class T, class U, class W>
void Merge(const T* first_begin, const T* first_end, const U* second_begin, const U* second_end, W* out) {
  int size1 = first_end - first_begin;
  int size2 = second_end - second_begin;
  int i1 = 0;
  int i2 = 0;
  int i3 = 0;
  while (i1 < size1 && i2 < size2) {
    if (first_begin[i1] < second_begin[i2]) {
      out[i3] = first_begin[i1];
      ++i1;
    } else {
      out[i3] = second_begin[i2];
      ++i2;
    }
    ++i3;
  }
  while (i1 < size1) {
    out[i3] = first_begin[i1];
    ++i1;
    ++i3;
  }
  while (i2 < size2) {
    out[i3] = second_begin[i2];
    ++i2;
    ++i3;
  }
}
#endif