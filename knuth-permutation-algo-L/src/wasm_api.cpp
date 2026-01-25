#include <cstdint>
#include <emscripten/bind.h>
#include <permutation/trace.h>
#include <vector>

std::vector<permutation::TraceEvent>
permute_array(std::vector<int32_t> values) {
  std::vector<permutation::TraceEvent> events;
  events.reserve(values.size() * 8 + 16);

  TraceSink sink{};

#ifdef __EMSCRIPTEN__
  VecTraceCollector collector{&events};
  sink.emit = &VecTraceCollector::emit;
  sink.user = &collector;
#else
  sink.emi = nullptr;
  sink.user = nullptr;
#endif
  calculate_permutation_traced(values.begin(), values.end(), sink,
                               std::less<>{});
  return events;
}

EMSCRIPTEN_BINDINGS(permutation_module) {
  emscripten::function("permute_array", &permute_array);
}
