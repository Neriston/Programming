#include <cstring>
#include "string_view.h"

StringView::StringView() : str_(nullptr), size_(0) {
}

StringView::StringView(const char* str) : str_(str), size_(std::strlen(str)) {
}

StringView::StringView(const char* str, size_t size) : str_(str), size_(size) {
}

const char& StringView::operator[](size_t i) const {
  return str_[i];
}

const char& StringView::At(size_t i) const {
  if (i >= size_) {
    throw StringViewOutOfRange{};
  }
  return str_[i];
}

char StringView::Front() const {
  return str_[0];
}

char StringView::Back() const {
  return str_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return size_ == 0;
}

const char* StringView::Data() const {
  return str_;
}

void StringView::Swap(StringView& other) {
  std::swap(str_, other.str_);
  std::swap(size_, other.size_);
}

void StringView::RemovePrefix(size_t prefix_size) {
  str_ += prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) const {
  if (pos >= size_) {
    throw StringViewOutOfRange{};
  }
  return StringView(str_ + pos, std::min(count, Size() - pos));
}