#pragma once

#include <cstdint>
#include <string_view>

namespace bytebuilder {

std::uint64_t make_seed(std::string_view input, std::uint64_t fallback);

std::uint64_t next_random(std::uint64_t& state);

}
