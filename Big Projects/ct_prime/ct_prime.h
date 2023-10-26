#ifndef CT_PRIME_H
#define CT_PRIME_H

#include <iostream>

template <size_t N, size_t Low, size_t High, size_t Mid = (High + Low + 1) / 2>
struct Sqrt : Sqrt<N, (N < Mid * Mid ? Low : Mid), (N < Mid * Mid ? Mid - 1 : High)> {};

template <size_t N, size_t Ans>
struct Sqrt<N, Ans, Ans, Ans> : std::integral_constant<size_t, Ans> {};

template <size_t N>
inline const auto kSqrtV = Sqrt<N, 0, 1000000000>::value;

template <size_t N, size_t L, size_t R, size_t Mid = (L + R) / 2>
struct HasDivisorOnVTemp
    : std::bool_constant<HasDivisorOnVTemp<N, L, Mid>::value || HasDivisorOnVTemp<N, Mid + 1, R>::value> {};

template <size_t N, size_t R>
struct HasDivisorOnVTemp<N, R, R, R> : std::bool_constant<((R > 1 && N > 1) || N == 1) && N % R == 0> {};

template <size_t N, size_t L, size_t R>
struct HasDivisorOnV : std::bool_constant<N == 0 || HasDivisorOnVTemp<N, L, R>::value> {};

template <size_t N, size_t L, size_t R>
inline const auto kHasDivisorOnV = HasDivisorOnV<N, std::min(L, R), std::max(L, R)>::value;

template <size_t N>
inline const auto kIsPrimeV = !kHasDivisorOnV<N, 1, kSqrtV<N>>;
#endif