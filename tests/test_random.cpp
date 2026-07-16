#include <cassert>
#include <cstdint>

#include "bytebuilder/random.h"

int main() {
  const std::uint64_t seed = bytebuilder::make_seed("12345", 7);
  assert(seed == 12345ULL);
  std::uint64_t state = seed;
  assert(bytebuilder::next_random(state) != bytebuilder::next_random(state));
  return 0;
}
