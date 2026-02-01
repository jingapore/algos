#pragma once
#include <cstdint>

namespace permutation {
enum class EventCode : int32_t {
  STAGE1_FIND_NON_DECREASING_SEQ_BREAKPOINT_COMPARE = 1,
  STAGE2_FIND_SWAPPOINT_COMPARE = 2,
  STAGE3_SWAP_WITH_PIVOT = 3,
  STAGE4_REVERSE_SWAP = 4,
  DONE = 9,
};
class TraceEvent {
public:
  EventCode code;
  int32_t idx_a;
  int32_t idx_b;
};
struct Trace {
  // user is what emit will mutate
  void *user = nullptr;
  void (*emit)(EventCode code, int32_t i, int32_t j, void *) = nullptr;
  // to mark that an event has occured. whether it emits anything depends
  // on how Trace was initialised.
  void event(EventCode code, int32_t i, int32_t j) const;
};
} // namespace permutation
