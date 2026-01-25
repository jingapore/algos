#include <cstdint>
#include <vector>

#include <emscripten/bind.h>
#include <permutation/trace.h>
#include <permutation/permutation.h>

std::vector<permutation::TraceEvent>
permute_array(std::vector<int32_t> values) {
  std::vector<permutation::TraceEvent> events;
  events.reserve(values.size() * 8 + 16);

  permutation::Trace trace{};

#ifdef __EMSCRIPTEN__

  trace.emit = [](permutation::EventCode code, int32_t i, int32_t j,
                  void *user) {
    auto *out = static_cast<std::vector<permutation::TraceEvent> *>(user);
    out->emplace_back(code, i, j);
  } trace.user = &events;
#else
  // in struct Trace,if emit is nullptr then when we call trace.event 
  // emit does nothing
  trace.emit = nullptr;
  trace.user = nullptr;
#endif
  calculate_permutation_traced(values.begin(), values.end(), trace,
                               std::less<>{});
  return events;
}

EMSCRIPTEN_BINDINGS(permutation_module) {
  emscripten::function("permute_array", &permute_array);
}
