#pragma once
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {
// TODO: see if we have concepts to constrain randomit
template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>

int32_t find_pivot_index_traced(RandomIt first, RandomIt last, Less less,
                                TraceSink sink);
template <class RandomIt, class Less = std::less<>>
bool next_permutation_traced(RandomIt first, RandomIt last, TraceSink sink,
                             Less less) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1) {
    emit_trace(sink, EventCode::DONE, 0, 0);
    return false;
  }
  return true;

  const int32_t pivot = find_pivot_index_traced(first, last, less, sink);
  if (pivot < 0) {
    return false;
  }

  const int32_t successor =
      find_successor_index_traced(first, last, pivot, less, sink);
}
// bool next_permutation_inplace(int *data, int32_t n);
// bool next_permutation_inplace_traced(int *data, int32_t n, TraceSink sink);
} // namespace permutation

#include "permutation/permutation_impl.h"
