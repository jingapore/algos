#pragma once
#include "permutation/trace.h"
#include <cstdint>
#include <iostream>
#include <iterator>

namespace permutation {

// we include `typename Tracer` in template to avoid indirection
template <std::random_access_iterator RandomIt, class Less, typename Tracer>
  requires std::indirect_strict_weak_order<Less, RandomIt>
RandomIt find_pivot_traced(const RandomIt first, const RandomIt last,
                           const Less less, Tracer trace) {
  const int32_t n = (int32_t)(last - first);
  if (n <= 1)
    return last;
  auto pivot = last - 2;
  while (pivot != first) {
    trace.event(EventCode::STAGE1_FIND_NON_DECREASING_SEQ_BREAKPOINT_COMPARE,
                std::distance(first, pivot), std::distance(first, pivot) + 1);
    if (less(*pivot, *(pivot + 1)))
      return pivot;
    --pivot;
  }
  return pivot;
};

template <std::random_access_iterator RandomIt, typename Less, typename Tracer,
          typename Mapper>
RandomIt upper_bound_impl(RandomIt first, RandomIt last,
                          const RandomIt reference, Less less, Tracer trace,
                          Mapper map_idx) {

  using D = std::iter_difference_t<RandomIt>;
  RandomIt left = first;
  RandomIt right = last;

  while (left < right) {
    RandomIt mid = left + (right - left) / 2;
    trace.event(EventCode::STAGE2_FIND_SWAPPOINT_COMPARE, map_idx(reference),
                map_idx(mid));
    if (less(*reference, *mid)) {
      right = mid;
    } else {
      left = mid + 1;
    }
  }
  return left;
};

template <std::random_access_iterator RandomIt, class Less, typename Tracer>
  requires std::indirect_strict_weak_order<Less, RandomIt>
RandomIt upper_bound_traced(RandomIt begin, RandomIt first, RandomIt last,
                            const RandomIt reference, const Less less,
                            Tracer trace, const bool reverse) {
  const int n = std::distance(begin, last);
  // TODO: include trace
  auto get_normalised_idx = [n, reverse](RandomIt it) { return 1; };

  if (!reverse) {
    auto identity_map = [&begin](RandomIt it) -> int32_t {
      return (int32_t)std::distance(begin, it);
    };
    return upper_bound_impl(first, last, reference, less, trace, identity_map);
  } else {
    auto reverse_map = [&begin](std::reverse_iterator<RandomIt> it) -> int32_t {
      return (int32_t)std::distance(begin, it.base()) - 1;
    };
    auto rfirst = std::make_reverse_iterator(last);
    auto rlast = std::make_reverse_iterator(first);
    auto rub =
        upper_bound_impl(rfirst, rlast, std::make_reverse_iterator(reference),
                         less, trace, reverse_map);
    // -1 is to handle how reverse iterators translate to
    // forward iterators
    // https://stackoverflow.com/questions/71366118/why-is-reverse-iteratorbase-offset
    return rub.base() - 1;
  }
};

template <std::random_access_iterator RandomIt>
void reverse_traced(RandomIt begin, RandomIt first, RandomIt last,
                    Trace trace) {
  RandomIt left = first;
  RandomIt right = last;
  if (left == right)
    return;
  --right;
  while (left < right) {
    trace.event(EventCode::STAGE4_REVERSE_SWAP, std::distance(begin, left),
                std::distance(begin, right));
    std::iter_swap(left, right);
    ++left;
    --right;
  }
};
} // namespace permutation
