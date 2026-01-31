#pragma once
#include "permutation/permutation_impl.h"
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {

template <std::random_access_iterator RandomIt>
void reverse_traced(RandomIt begin, RandomIt first, RandomIt last, Trace trace);

template <class RandomIt, class Less = std::less<>>
  requires std::indirect_strict_weak_order<Less, RandomIt>
bool calculate_permutation_traced(RandomIt first, RandomIt last, Trace trace,
                                  Less less) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1) {
    trace.event(EventCode::DONE, 0, 0);
    return false;
  }
  find_pivot_traced(first, last, less, trace);
  trace.event(EventCode::DONE, 0, 0);
  return true;
}
} // namespace permutation
