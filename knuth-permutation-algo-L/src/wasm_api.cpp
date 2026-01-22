#include <cstdint>
#include <emscripten/bind.h>
#include <permutation/trace.h>
#include <vector>

extern "C" {
std::vector<permutation::TraceEvent> permute_array(int *data, int32_t length) {
  // TODO: return length
  return {};
}
}

EMSCRIPTEN_BINDINGS(permutation_module) {
  function("permute_array", &permute_array);
}
