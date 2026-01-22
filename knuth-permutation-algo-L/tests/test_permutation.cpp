#include "permutation/permutation.h"
#include "permutation/trace.h"
#include <functional>
#include <gtest/gtest.h>
#include <vector>

TEST(KnuthPermutationAlgoTest, ArrayManipulation) {
  std::vector<int> v{1, 2, 3, -4, -5, -6};
  int32_t pivot_idx = permutation::find_pivot_index_traced(
      v.begin(), v.end(), std::less<int>{}, permutation::TraceSink{});

  ASSERT_EQ(pivot_idx, 1);
}
