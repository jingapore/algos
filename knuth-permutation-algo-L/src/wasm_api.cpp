#include "permutation/permutation.h"
#include <cstdint>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
#endif
#include <permutation/permutation.h>
#include <permutation/trace.h>

std::vector<permutation::TraceEvent>
permute_array(std::vector<int32_t> values) {
  std::vector<permutation::TraceEvent> events;
  events.reserve(values.size() * 8 + 16);

  permutation::Trace trace{};

#if defined(__EMSCRIPTEN__) || defined(IS_DEBUG)

  trace.emit = [](permutation::EventCode code, int32_t i, int32_t j,
                  void *user) {
    auto *out = static_cast<std::vector<permutation::TraceEvent> *>(user);
    out->push_back(permutation::TraceEvent{code, i, j});
  };
  trace.user = &events;
#else
  // in struct Trace,if emit is nullptr then when we call trace.event
  // emit does nothing
  trace.emit = nullptr;
  trace.user = nullptr;
#endif
  permutation::calculate_permutation_traced(values.begin(), values.end(), trace,
                                            std::less<>{});
  return events;
}

#ifdef IS_DEBUG
template class std::vector<int>;
int main() {
  std::vector<int> input_vec;
  // so that we can run expr within lldb
  volatile bool force_symbols = false;
  if (force_symbols) {
    int x = 5;
    input_vec.push_back(x);
    input_vec.push_back(5);
  }
  std::vector<permutation::TraceEvent> result_vec = permute_array(input_vec);
  return 0;
}
#endif

#ifdef __EMSCRIPTEN__
#ifndef NO_BINDINGS
EMSCRIPTEN_BINDINGS(permutation_module) {
  emscripten::enum_<permutation::EventCode>("EventCode")
      .value("STAGE1_FIND_NON_DECREASING_SEQ_BREAKPOINT_COMPARE",
             permutation::EventCode::
                 STAGE1_FIND_NON_DECREASING_SEQ_BREAKPOINT_COMPARE)
      .value("STAGE2_FIND_SWAPPOINT_COMPARE",
             permutation::EventCode::STAGE2_FIND_SWAPPOINT_COMPARE)
      .value("STAGE3_SWAP_WITH_PIVOT",
             permutation::EventCode::STAGE3_SWAP_WITH_PIVOT)
      .value("STAGE4_REVERSE_SWAP", permutation::EventCode::STAGE4_REVERSE_SWAP)
      .value("DONE", permutation::EventCode::DONE);

  emscripten::value_object<permutation::TraceEvent>("TraceEvent")
      .field("code", &permutation::TraceEvent::code)
      .field("idx_a", &permutation::TraceEvent::idx_a)
      .field("idx_b", &permutation::TraceEvent::idx_b);

  emscripten::register_vector<permutation::TraceEvent>("TraceEventVector");
  emscripten::register_vector<std::int32_t>("Int32Vector");

  emscripten::function("permute_array", &permute_array);
}
#endif
#endif
