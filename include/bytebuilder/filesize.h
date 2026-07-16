#pragma once

#include <cstdint>
#include <string>
#include <string_view>

#include "bytebuilder/util.h"

namespace bytebuilder {

std::uint64_t parse_size(std::string_view input, Status& status);

std::string format_size(std::uint64_t bytes);

}
