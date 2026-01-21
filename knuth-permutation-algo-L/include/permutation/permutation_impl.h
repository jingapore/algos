#pragma once
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {
template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
int32_t find_pivot_index_traced(RandomIt first, RandomIt last, Less less,
                                TraceSink sink) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1)
    return -1;
  int32_t pivot = n - 2;
  while (pivot >= 0) {
    emit_trace(sink, EventCode::L1_COMPARE, pivot, pivot + 1);
    if (less(first[pivot], first[pivot + 1]))
      return pivot;
    --pivot;
  }
  return pivot;
};
} // namespace permutation
