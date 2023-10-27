#ifndef ENUM
#define ENUM

#include <utility>

template <typename T>
class Enumerate {
  T& container_;

 public:
  using ValueType = typename T::value_type;
  using IteratorType = typename T::iterator;
  using ConstIteratorType = typename T::const_iterator;

  explicit Enumerate(T& container) : container_(container) {
  }

  class Iterator : public std::pair<IteratorType, int> {
   public:
    using Base = std::pair<IteratorType, int>;

    Iterator(IteratorType&& it, int&& index) : Base(it, index) {
    }

    bool operator!=(const Iterator& other) const {
      return this->first != other.first;
    }

    void operator++() {
      ++this->first;
      ++this->second;
    }

    auto operator*() const {
      return std::pair<int, ValueType&>(this->second, *this->first);
    }
  };

  class ConstIterator : public std::pair<ConstIteratorType, int> {
   public:
    using Base = std::pair<ConstIteratorType, int>;

    ConstIterator(ConstIteratorType it, int index) : Base(it, index) {
    }

    bool operator!=(ConstIteratorType& other) const {
      return this->first != other->first;
    }

    void operator++() {
      ++this->first;
      ++this->second;
    }

    auto operator*() const {
      return std::pair<int, const ValueType&>(this->second, *this->first);
    }
  };

  Iterator begin() {  //  NOLINT
    return Iterator(container_.begin(), 0);
  }

  Iterator end() {  //  NOLINT
    return Iterator(container_.end(), std::distance(container_.begin(), container_.end()));
  }

  ConstIterator begin() const {  //  NOLINT
    return ConstIterator(container_.cbegin(), 0);
  }

  ConstIterator end() const {  //  NOLINT
    return ConstIterator(container_.cend(), std::distance(container_.cbegin(), container_.cend()));
  }
};

template <typename T>
class Enumerate<const T> {
  const T& container_;

 public:
  using ValueType = typename T::value_type;
  using ConstIteratorType = typename T::const_iterator;

  explicit Enumerate(const T& container) : container_(container) {
  }
  class ConstIterator : public std::pair<ConstIteratorType, int> {
   public:
    using Base = std::pair<ConstIteratorType, int>;

    ConstIterator(ConstIteratorType it, int index) : Base(it, index) {
    }

    bool operator!=(ConstIteratorType& other) const {
      return this->first != other->first;
    }

    void operator++() {
      ++this->first;
      ++this->second;
    }

    auto operator*() const {
      return std::pair<int, const ValueType&>(this->second, *this->first);
    }
  };

  ConstIterator begin() const {  //  NOLINT
    return ConstIterator(container_.cbegin(), 0);
  }

  ConstIterator end() const {  //  NOLINT
    return ConstIterator(container_.cend(), std::distance(container_.cbegin(), container_.cend()));
  }
};
#endif