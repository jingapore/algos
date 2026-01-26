#pragma once
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {

template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
RandomIt find_pivot_traced(RandomIt first, RandomIt last, const Less less,
                           Trace trace);
template <std::random_access_iterator RandomIt, class Less>
  requires std::indirect_strict_weak_order<Less, RandomIt>
RandomIt upper_bound_traced(RandomIt begin, RandomIt first, RandomIt last,
                            const Less less, Trace trace, const bool reverse);

template <std::random_access_iterator RandomIt>
void reverse_traced(RandomIt begin, RandomIt first, RandomIt last,
                        Trace trace);

template <class RandomIt, class Less = std::less<>>
  requires std::indirect_strict_weak_order<Less, RandomIt>
bool calculate_permutation_traced(RandomIt first, RandomIt last, Trace trace,
                                  Less less) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1) {
    trace.event(EventCode::DONE, 0, 0);
    return false;
  }
  return true;

  const int32_t pivot = find_pivot_traced(first, last, less, trace);
  if (pivot < 0) {
    return false;
  }
  // upperbound here, but over reversed iterator, how can we reverse if RandomIt
  // is a pointer and not a cpp iterator?

  const int32_t successor =
      find_successor_index_traced(first, last, pivot, less, trace);
}
} // namespace permutation

#include "permutation/permutation_impl.h"
