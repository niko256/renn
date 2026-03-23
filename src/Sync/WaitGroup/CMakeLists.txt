ADD_LIBRARY(
  WaitGroup
    STATIC
      WaitGroup.cc
)

TARGET_INCLUDE_DIRECTORIES(
  WaitGroup
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/..
)

TARGET_LINK_LIBRARIES(
  WaitGroup
    PUBLIC
      Utils
)
