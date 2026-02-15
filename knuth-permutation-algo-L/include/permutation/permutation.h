#pragma once
#include "permutation/permutation_impl.h"
#include "permutation/trace.h"
#include <cstdint>
#include <iterator>

namespace permutation {

template <class RandomIt, class Less = std::less<>>
  requires std::indirect_strict_weak_order<Less, RandomIt> &&
           std::random_access_iterator<RandomIt>
bool calculate_permutation_traced(RandomIt first, RandomIt last, Trace trace,
                                  Less less) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1) {
    trace.event(EventCode::DONE, 0, 0);
    return false;
  }
  auto pivot_it = find_pivot_traced(first, last, less, trace);
  // TODO: if no pivot found then end
  // first param is an anchor for us to calculate pivots
  auto swappoint_it = upper_bound_traced(first, pivot_it + 1, last, pivot_it,
                                         less, trace, true);
  trace.event(EventCode::STAGE3_SWAP_WITH_PIVOT, std::distance(first, pivot_it),
              std::distance(first, swappoint_it));
  std::iter_swap(pivot_it, swappoint_it);
  reverse_traced(first, pivot_it + 1, last, trace);
  trace.event(EventCode::DONE, 0, 0);
  return true;
}
} // namespace permutation
