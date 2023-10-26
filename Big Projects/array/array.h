#ifndef ARRAY
#define ARRAY
#include <stdexcept>

class ArrayOutOfRange : public std::out_of_range {
 public:
  ArrayOutOfRange() : std::out_of_range("ArrayOutOfRange") {
  }
};

template <typename T, size_t N>
class Array {
 public:
  T array[N];

  const T& operator[](size_t i) const {
    return array[i];
  }

  T& operator[](size_t i) {
    return array[i];
  }

  const T& At(size_t idx) const {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  T& At(size_t idx) {
    if (idx >= N) {
      throw ArrayOutOfRange{};
    }
    return array[idx];
  }

  const T& Front() const {
    return array[0];
  }

  T& Front() {
    return array[0];
  }

  const T& Back() const {
    return array[N - 1];
  }

  T& Back() {
    return array[N - 1];
  }

  T* Data() {
    return array;
  }

  const T* Data() const {
    return array;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      array[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      std::swap(array[i], other[i]);
    }
  }
};
#endif