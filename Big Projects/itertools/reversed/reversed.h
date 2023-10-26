#ifndef REVERSE_H
#define REVERSE_H
#define REVERSE_REVERSED_IMPLEMENTED
#define TEMPORARY_REVERSED_IMPLEMENTED

template <typename Container>
class ReverseFirst {
  Container& container_;

 public:
  explicit ReverseFirst(Container& container) : container_(container) {
  }

  auto begin() {  //  NOLINT
    return container_.rbegin();
  }

  auto end() {  //  NOLINT
    return container_.rend();
  }

  auto cbegin() const {  //  NOLINT
    return container_.crbegin();
  }

  auto cend() const {  //  NOLINT
    return container_.crend();
  }

  auto begin() const {  //  NOLINT
    return container_.rbegin();
  }

  auto end() const {  //  NOLINT
    return container_.rend();
  }

  auto rbegin() {  //  NOLINT
    return container_.begin();
  }

  auto rend() {  //  NOLINT
    return container_.end();
  }

  auto rbegin() const {  //  NOLINT
    return container_.begin();
  }

  auto rend() const {  //  NOLINT
    return container_.end();
  }
};

template <typename Container>
class ReverseSecond {
  Container container_;

 public:
  explicit ReverseSecond(Container&& container) : container_(std::move(container)) {
  }

  auto begin() {  //  NOLINT
    return container_.rbegin();
  }

  auto end() {  //  NOLINT
    return container_.rend();
  }

  auto begin() const {  //  NOLINT
    return container_.rbegin();
  }

  auto end() const {  //  NOLINT
    return container_.rend();
  }

  auto rbegin() {  //  NOLINT
    return container_.begin();
  }

  auto rend() {  //  NOLINT
    return container_.end();
  }

  auto rbegin() const {  //  NOLINT
    return container_.begin();
  }

  auto rend() const {  //  NOLINT
    return container_.end();
  }
};

template <class Container>
ReverseFirst<Container> Reversed(Container& container) {
  return ReverseFirst(container);
}

template <typename Container>
ReverseSecond<Container> Reversed(Container&& container) {
  return ReverseSecond<Container>(std::move(container));
}
#endif