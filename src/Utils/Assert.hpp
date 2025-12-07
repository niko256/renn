#pragma once

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <source_location>
#include <string_view>

namespace renn {

[[noreturn]]
inline void ASSERT_IMPL(bool condition,
                        std::string_view message = "ASSERTION FAILED",
                        std::source_location loc = std::source_location::current()) {
    if (!condition) {

        std::cerr << "ASSERT FAILED :   " << message << std::endl
                  << " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- " << std::endl
                  << " | FILE | :   " << loc.file_name() << std::endl
                  << " | LINE | :   " << loc.line() << std::endl
                  << " | FUNC | :   " << loc.function_name() << std::endl
                  << " -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- " << std::flush;

        std::abort();
    }
}

#define RENN_ASSERT(condition, ...)                               \
    do {                                                          \
        if (!(condition)) {                                       \
            ::renn::ASSERT_IMPL(false, __VA_ARGS__,               \
                                std::source_location::current()); \
        }                                                         \
    } while (0)

};  // namespace renn
