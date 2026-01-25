#include "permutation/permutation.h"
#include "permutation/trace.h"
#include <functional>
#include <gtest/gtest.h>
#include <vector>

TEST(KnuthPermutationAlgoTest, ArrayManipulation) {
  std::vector<int> v{1, 2, 3, -4, -5, -6};
  auto pivot_itr = permutation::find_pivot_traced(
      v.begin(), v.end(), std::less<int>{}, permutation::Trace{});

  ASSERT_EQ(distance(v.begin(), pivot_itr), 1);

  auto swap_itr = permutation::upper_bound_traced(
      v.begin(), pivot_itr + 1, v.end(), *pivot_itr, std::less<>{},
      permutation::Trace{}, true);
  ASSERT_EQ(distance(v.begin(), swap_itr), 2);
}
