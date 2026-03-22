INCLUDE(FetchContent)

# sure ^-^
FetchContent_Declare(
    sure
      GIT_REPOSITORY https://gitlab.com/Lipovsky/sure.git
      GIT_TAG master
)

# sure-stack
FetchContent_Declare(
    sure-stack
      GIT_REPOSITORY https://gitlab.com/Lipovsky/sure-stack.git
      GIT_TAG master
)

# ^_^
FetchContent_Declare(
  ntrusive
    GIT_REPOSITORY https://github.com/niko256/ntrusive.git
    GIT_TAG master
)

# fu2
FetchContent_Declare(
  function2
    GIT_REPOSITORY https://github.com/Naios/function2.git
    GIT_TAG master
)

# futex-like
FetchContent_Declare(
  futex_like
    GIT_REPOSITORY https://gitlab.com/Lipovsky/futex_like.git
    GIT_TAG master
)

IF(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  IF(RENN_BUILD_UNIT_TESTS OR RENN_WITH_TWIST)
    FetchContent_Declare(
      googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
    )
    SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
  ENDIF()

  IF(RENN_WITH_TWIST)
    MESSAGE(STATUS "[renn] : TWIST [ON]")

    SET(TWIST_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    SET(TWIST_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    SET(TWIST_FAULTY ON CACHE BOOL "ENABLES TWIST FAULT INJECTION" FORCE)
    SET(TWIST_SIM ON CACHE BOOL "ENABLES TWIST DETERMINISTIC SIMULATION" FORCE)

    FetchContent_Declare(
      twist
        GIT_REPOSITORY https://gitlab.com/Lipovsky/twist.git
        GIT_TAG master
    )
    FetchContent_MakeAvailable(twist)
  ENDIF()
ENDIF()

FetchContent_MakeAvailable(
  sure
  sure-stack
  ntrusive
  function2
  futex_like
)

#message(STATUS "function2 populated: ${function2_POPULATED}")
#message(STATUS "function2 source dir: ${function2_SOURCE_DIR}")

# ALIASES
IF(sure_POPULATED)
  ADD_LIBRARY(third_party_sure ALIAS sure)
ENDIF()

IF(sure-stack_POPULATED)
  ADD_LIBRARY(third_party_sure_stack INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(third_party_sure_stack INTERFACE
      ${sure-stack_SOURCE_DIR}/source)
ENDIF()

IF (ntrusive_POPULATED)
  ADD_LIBRARY(third_party_ntrusive INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(third_party_ntrusive INTERFACE
    ${ntrusive_SOURCE_DIR}/include)
ENDIF()

IF (function2_POPULATED)
  ADD_LIBRARY(third_party_function2 INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(third_party_function2 INTERFACE
      ${function2_SOURCE_DIR}/include)
ELSE()
  message(STATUS "Function2 include: ${function2_SOURCE_DIR}/include")
ENDIF()

IF (futex_like_POPULATED)
  ADD_LIBRARY(third_party_futex_like INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(third_party_futex_like INTERFACE
      ${futex_like_SOURCE_DIR}/source)
ENDIF()

message(STATUS "futex-like populated: ${futex_like_POPULATED}")
message(STATUS "futex-like source dir: ${futex_like_SOURCE_DIR}")
