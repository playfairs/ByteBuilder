#include <cassert>
#include <cstdint>

#include "bytebuilder/filesize.h"

int main() {
  bytebuilder::Status status;
  const std::uint64_t bytes = bytebuilder::parse_size("1MiB", status);
  assert(status.ok);
  assert(bytes == 1024ULL * 1024ULL);
  assert(bytebuilder::format_size(1536) == "1 KiB");
  return 0;
}
