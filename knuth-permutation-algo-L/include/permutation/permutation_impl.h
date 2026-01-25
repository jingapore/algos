#pragma once
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {
template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
RandomIt find_pivot_traced(const RandomIt first, const RandomIt last,
                           const Less less, Trace trace) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1)
    return last;
  auto pivot = last - 2;
  while (pivot != first) {
    trace.event(EventCode::L1_COMPARE, distance(first, pivot),
                distance(first, pivot) + 1);
    if (less(*pivot, *(pivot + 1)))
      return pivot;
    --pivot;
  }
  return pivot;
};

template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
RandomIt upper_bound_traced(RandomIt begin, RandomIt first, RandomIt last,
                            const std::iter_value_t<RandomIt> &value,
                            const Less less, Trace trace, const bool reverse) {
  const int n = std::distance(first, last);
  // TODO: include trace
  auto get_normalised_idx = [n, reverse](RandomIt it) { return 1; };
  auto upper_bound_impl =
      [&less, &n, &value](auto it_first, auto it_last) -> decltype(it_first) {
    using It = decltype(it_first);
    using D = std::iter_difference_t<It>;
    It left = it_first;
    It right = it_last;

    while (left < right) {
      It mid = left + (right - left) / 2;
      if (less(value, *mid)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  };
  if (!reverse) {
    return upper_bound_impl(first, last);
  } else {
    auto rfirst = std::make_reverse_iterator(last);
    auto rlast = std::make_reverse_iterator(first);
    auto rub = upper_bound_impl(rfirst, rlast);
    return rub.base();
  }
};
} // namespace permutation
