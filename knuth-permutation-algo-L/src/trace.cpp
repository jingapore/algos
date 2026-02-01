#include <permutation/trace.h>

namespace permutation {
void Trace::event(EventCode code, int32_t i, int32_t j) const {
#ifdef __EMSCRIPTEN__
  if (emit)
    emit(code, i, j, user);
#else
  // to silence unused param warnings
  (void)code;
  (void)i;
  (void)j;
#endif
}
}; // namespace permutation
