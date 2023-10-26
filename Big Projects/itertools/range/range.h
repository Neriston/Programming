#ifndef RANGE_H
#define RANGE_H
#define REVERSE_RANGE_IMPLEMENTED

class RangeIterator {
  int current_, end_, step_;

 public:
  RangeIterator(const int& current, const int& end, const int& step = 1) : current_(current), end_(end), step_(step) {
  }

  int operator*() const {
    return current_;
  }

  RangeIterator& operator++() {
    current_ += step_;
    return *this;
  }

  bool operator!=(const RangeIterator& other) const {
    if (step_ > 0) {
      return current_ < other.current_;
    }
    return current_ > other.current_;
  }
};

class Range {
  int begin_, end_, step_;

 public:
  explicit Range(const int& end) : begin_(0), end_(end), step_(1) {
  }

  explicit Range(const int& begin, const int& end, const int& step = 1) : begin_(begin), end_(end), step_(step) {
    if (step == 0 || (begin < end && step < 0) || (begin > end && step > 0)) {
      begin_ = end_;
    }
  }

  RangeIterator begin() const {  // NOLINT
    return RangeIterator(begin_, end_, step_);
  }
  RangeIterator end() const {  // NOLINT
    return RangeIterator(end_, end_, step_);
  }

  RangeIterator rbegin() const {  //  NOLINT
    if ((step_ != 0 && (end_ - begin_) % step_ == 0) || step_ == 0) {
      return RangeIterator(end_ - step_, begin_ - step_, -step_);
    }
    return RangeIterator(end_ - (end_ - begin_) % step_, begin_ - step_, -step_);
  }

  RangeIterator rend() const {  //  NOLINT
    return RangeIterator(begin_ - step_, begin_ - step_, -step_);
  }
};
#endif