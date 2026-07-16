#pragma once

#include <cstdint>
#include <filesystem>

#include "bytebuilder/util.h"

namespace bytebuilder {

Status ensure_sparse_file(const std::filesystem::path& path, std::uint64_t size_bytes);

}
