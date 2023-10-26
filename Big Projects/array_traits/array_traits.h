#ifndef ARRAY_TRAITS_H
#define ARRAY_TRAITS_H

#include <iostream>
#include <type_traits>

template <class T>
struct IsArray : std::false_type {};

template <class T>
struct IsArray<T[]> : std::true_type {};

template <class T, size_t N>
struct IsArray<T[N]> : std::true_type {};

template <class T>
inline constexpr bool kIsArrayV = IsArray<T>::value;

template <class T>
struct Rank : std::integral_constant<size_t, 0> {};

template <class T>
struct Rank<T[]> : std::integral_constant<size_t, Rank<T>::value + 1> {};

template <class T, size_t N>
struct Rank<T[N]> : std::integral_constant<size_t, Rank<T>::value + 1> {};

template <class T>
inline constexpr size_t kRankV = Rank<T>::value;

template <class T>
struct Size : std::integral_constant<size_t, 1> {};

template <class T>
struct Size<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct Size<T[N]> : std::integral_constant<size_t, N> {};

template <class T>
inline constexpr size_t kSizeV = Size<T>::value;

template <class T>
struct TotalSize : std::integral_constant<size_t, 1> {};

template <class T>
struct TotalSize<T[]> : std::integral_constant<size_t, 0> {};

template <class T, size_t N>
struct TotalSize<T[N]> : std::integral_constant<size_t, kSizeV<T[N]> * TotalSize<T>::value> {};

template <class T>
inline constexpr std::size_t kTotalSizeV = TotalSize<T>::value;

template <class T>
struct RemoveArray {
  using Type = T;
};

template <class T>
struct RemoveArray<T[]> {
  using Type = T;
};

template <class T, size_t N>
struct RemoveArray<T[N]> {
  using Type = T;
};

template <class T>
using RemoveArrayT = typename RemoveArray<T>::Type;

template <class T>
struct RemoveAllArrays {
  using Type = T;
};

template <class T>
struct RemoveAllArrays<T[]> {
  using Type = T;
};

template <class T, size_t N>
struct RemoveAllArrays<T[N]> {
  using Type = T;
};

template <class T, size_t K>
struct RemoveAllArrays<T[][K]> {
  using Type = typename RemoveAllArrays<T[K]>::Type;
};

template <class T, size_t N, size_t K>
struct RemoveAllArrays<T[N][K]> {
  using Type = typename RemoveAllArrays<T[K]>::Type;
};

template <class T>
using RemoveAllArraysT = typename RemoveAllArrays<T>::Type;
#endif