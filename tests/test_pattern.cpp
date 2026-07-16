#include <array>
#include <cassert>

#include "bytebuilder/pattern.h"

int main() {
  bytebuilder::PatternGenerator generator(bytebuilder::PatternKind::Zero);
  std::array<std::byte, 4> buffer{};
  generator.fill(buffer, 0);
  assert(buffer[0] == std::byte{0});
  assert(buffer[3] == std::byte{0});

  bytebuilder::PatternGenerator incrementing(bytebuilder::PatternKind::Incrementing);
  std::array<std::byte, 4> incremented{};
  incrementing.fill(incremented, 0);
  assert(incremented[0] == std::byte{0});
  assert(incremented[3] == std::byte{3});
  return 0;
}
