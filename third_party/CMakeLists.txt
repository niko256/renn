INCLUDE(FetchContent)

# GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)


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

# Horovod ^_^
FetchContent_Declare(
    vvv
    GIT_REPOSITORY https://gitlab.com/Lipovsky/vvv.git
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


FetchContent_MakeAvailable(
  googletest
  sure
  sure-stack
  vvv
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

IF (vvv_POPULATED)
  ADD_LIBRARY(third_party_vvv INTERFACE)
  TARGET_INCLUDE_DIRECTORIES(third_party_vvv INTERFACE
    ${vvv_SOURCE_DIR}/source)
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
