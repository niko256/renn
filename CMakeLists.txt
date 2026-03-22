CMAKE_MINIMUM_REQUIRED(VERSION 3.25)

PROJECT(
  renn
    LANGUAGES
      CXX
)

# +---+---+---+---+---+---+---+---+---+---+---+---+---+

OPTION(RENN_BUILD_UNIT_TESTS "Build unit tests" OFF)
OPTION(RENN_BUILD_EXAMPLES "Build examples" OFF)
# OPTION(RENN_BUILD_ANALYSIS "Build benchmarks" OFF)
OPTION(RENN_WITH_TWIST "Build with Twist" OFF)
OPTION(RENN_ENABLE_ASAN "Enable Address Sanitizer" OFF)
OPTION(RENN_ENABLE_TSAN "Enable Thread Sanitizer" OFF)

# +---+---+---+---+---+---+---+---+---+---+---+---+---+

SET(CMAKE_CXX_STANDARD 23)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

ADD_SUBDIRECTORY(third_party)

# +---+---+---+---+---+---+---+---+---+---+---+---+---+

IF(MSVC)
  ADD_COMPILE_OPTIONS(/W4 /WX)
ELSE()
  ADD_COMPILE_OPTIONS(
    # -Wall
    # -Wextra
    -Wpedantic
    -Werror
  )
ENDIF()

IF(RENN_ENABLE_ASAN AND RENN_ENABLE_TSAN)
  MESSAGE(FATAL_ERROR "ASAN and TSAN are mutally exclusive")
ENDIF()

IF(RENN_ENABLE_ASAN)
  MESSAGE(STATUS "[renn] : Address sanitizer Enabled")
  ADD_COMPILE_OPTIONS(-fsanitize=address -g)
  ADD_LINK_OPTIONS(-fsanitize=address)
ENDIF()

IF(RENN_ENABLE_TSAN)
  MESSAGE(STATUS "[renn] : Thread sanitizer Enabled")
  ADD_COMPILE_OPTIONS(-fsanitize=thread -g)
  ADD_LINK_OPTIONS(-fsanitize=thread)
ENDIF()

# +---+---+---+---+---+---+---+---+---+---+---+---+---+

ADD_SUBDIRECTORY(src)

# +---+---+---+---+---+---+---+---+---+---+---+---+---+

IF(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  IF(RENN_BUILD_UNIT_TESTS OR RENN_WITH_TWIST)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(tests)
  ENDIF()
ENDIF()
