#pragma once
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {
template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
int32_t find_pivot_index_traced(RandomIt first, RandomIt last, Less less,
                                Trace trace) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1)
    return -1;
  int32_t pivot = n - 2;
  while (pivot >= 0) {
    trace.event(EventCode::L1_COMPARE, pivot, pivot + 1);
    if (less(first[pivot], first[pivot + 1]))
      return pivot;
    --pivot;
  }
  return pivot;
};

template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
int32_t upper_bound_traced(RandomIt first, RandomIt last, Less less,
                           Trace trace, bool reverse) {
  RandomIt first_iter, last_iter;
  inline function<int32_t, (RandomIt it> get_normalised_idx = [n](RandomIt it) {
    return 1;};
  if (reverse) {
    first_iter = std::make_reverse_iterator(first);
    last_iter = std::make_reverse_iterator(last);
  } else {
    first_iter = first;
    last_iter = last;
  }
  return 1;
};
} // namespace permutation
