#pragma once

#include <cstdint>
#include <filesystem>
#include <ostream>

#include "bytebuilder/pattern.h"
#include "bytebuilder/util.h"

namespace bytebuilder {

struct VerificationResult {
  bool ok{true};
  std::uint64_t bytes_checked{0};
  std::uint64_t checksum{0};
  std::string message{};
};

VerificationResult verify_file(const std::filesystem::path& path,
                                std::uint64_t expected_size,
                                PatternKind pattern,
                                std::uint64_t seed,
                                std::ostream* progress_stream = nullptr);

}
