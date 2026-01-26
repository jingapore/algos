#include "permutation/permutation.h"
#include "permutation/trace.h"
#include <array>
#include <functional>
#include <gtest/gtest.h>
#include <iterator>

// TODO: use test fixtures
TEST(KnuthPermutationAlgoTest, ArrayManipulation) {
  std::array<int, 6> v{1, 2, 3, -4, -5, -6};
  auto pivot_itr = permutation::find_pivot_traced(
      v.begin(), v.end(), std::less<int>{}, permutation::Trace{});

  ASSERT_EQ(std::distance(v.begin(), pivot_itr), 1);

  auto swap_itr = permutation::upper_bound_traced(
      v.begin(), pivot_itr + 1, v.end(), *pivot_itr, std::less<>{},
      permutation::Trace{}, true);
  ASSERT_EQ(std::distance(v.begin(), swap_itr), 2);

  std::iter_swap(pivot_itr, swap_itr);

  ASSERT_EQ(*pivot_itr, 3);
  ASSERT_EQ(*swap_itr, 2);

  permutation::reverse_traced(v.begin(), pivot_itr + 1, v.end(),
                              permutation::Trace{});

  constexpr std::array<int, 4> expected_arr{-6, -5, -4, 2};
  ASSERT_TRUE(std::equal(pivot_itr + 1, v.end(), expected_arr.begin(),
                         expected_arr.end()));
}
