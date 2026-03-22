ADD_LIBRARY(ThreadPool STATIC
  ThreadPool.cc
)

TARGET_INCLUDE_DIRECTORIES(ThreadPool PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)

TARGET_LINK_LIBRARIES(ThreadPool PUBLIC
  RtCore
  Utils
  third_party_ntrusive
)
