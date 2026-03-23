ADD_LIBRARY(
  Spinlock
    STATIC
      Spinlock.cc
)

TARGET_INCLUDE_DIRECTORIES(
  Spinlock
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/..
)

TARGET_LINK_LIBRARIES(
  Spinlock
    PUBLIC
      Utils
)
