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
class TraceEvent {
  EventCode code;
  int32_t idx_a;
  int32_t indx_b;
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
