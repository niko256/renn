#pragma once

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <source_location>
#include <string_view>

namespace renn::utils {

[[noreturn]]
inline void ASSERT_IMPL(bool condition,
                        std::string_view message = "ASSERTION FAILED",
                        std::source_location loc = std::source_location::current()) {

    std::cerr << "ASSERT FAILED :   " << message << std::endl
              << " -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- " << std::endl
              << " | FILE | :   " << loc.file_name() << std::endl
              << " | LINE | :   " << loc.line() << std::endl
              << " | FUNC | :   " << loc.function_name() << std::endl
              << " -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- -*- " << std::flush;

    std::abort();
}

}  // namespace renn::utils

#define RENN_ASSERT(condition, ...)                                      \
    do {                                                                 \
        if (!(condition)) {                                              \
            ::renn::utils::ASSERT_IMPL(false, __VA_ARGS__,               \
                                       std::source_location::current()); \
        }                                                                \
    } while (0)
