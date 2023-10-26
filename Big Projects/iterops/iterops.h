#ifndef ITEROPS_H
#define ITEROPS_H

#include <iterator>

template <class Iterator, class Distan = typename std::iterator_traits<Iterator>::difference_type>
void Advance(Iterator& iterator, Distan step) {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;
  if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
    iterator += step;
  } else {
    if (step > 0) {
      for (Distan i = 0; i < step; ++i) {
        ++iterator;
      }
    }
    if constexpr (!std::is_same_v<Category, std::forward_iterator_tag>) {
      for (Distan i = step; i < 0; ++i) {
        --iterator;
      }
    }
  }
}

template <class Iterator, class Distan = typename std::iterator_traits<Iterator>::difference_type>
Iterator Next(Iterator iterator, Distan dist = 1) {
  Advance(iterator, dist);
  return iterator;
}

template <class Iterator, class Distan = typename std::iterator_traits<Iterator>::difference_type>
Iterator Prev(Iterator iterator, Distan dist = 1) {
  Advance(iterator, -dist);
  return iterator;
}

template <class Iterator, class Distan = typename std::iterator_traits<Iterator>::difference_type>
Distan Distance(Iterator first, Iterator second) {
  using Category = typename std::iterator_traits<Iterator>::iterator_category;
  if constexpr (std::is_same_v<Category, std::random_access_iterator_tag>) {
    return second - first;
  } else {
    Distan dist = 0;
    while (first != second) {
      ++first;
      ++dist;
    }
    return dist;
  }
}
#endif