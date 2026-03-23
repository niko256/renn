ADD_LIBRARY(Event STATIC
  Event.cc
)


TARGET_INCLUDE_DIRECTORIES(
  Event
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/..
)

TARGET_LINK_LIBRARIES(
  Event
    PUBLIC
      third_party_futex_like
      Utils
)
