#ifndef STRING_VIEW
#define STRING_VIEW
#include <stdexcept>

class StringViewOutOfRange : public std::out_of_range {
 public:
  StringViewOutOfRange() : std::out_of_range("StringViewOutOfRange") {
  }
};

class StringView {
  const char* str_;
  size_t size_ = 0;

 public:
  StringView();

  StringView(const char* str);  // NOLINT

  StringView(const char* str, size_t size);  // NOLINT

  const char& operator[](size_t i) const;

  const char& At(size_t i) const;

  char Front() const;

  char Back() const;

  size_t Size() const;

  size_t Length() const;

  bool Empty() const;

  const char* Data() const;

  void Swap(StringView& other);

  void RemovePrefix(size_t prefix_size);

  void RemoveSuffix(size_t suffix_size);

  StringView Substr(size_t pos, size_t count = -1) const;
};
#endif