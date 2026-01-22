#pragma once
#include <cstdint>

namespace permutation {
enum class EventCode : int32_t {
  L1_COMPARE = 1,
  L2_COMPARE = 2,
  L3_SWAP = 3,
  L4_SWAP = 4,
  DONE = 9,
};
class TraceEvent {};
struct TraceSink {};
void emit_trace(TraceSink sink, EventCode code, int32_t idx_a, int32_t idx_b);
} // namespace permutation
