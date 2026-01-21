ADD_LIBRARY(RtSandBox STATIC
  SandBox.cc
  TimerQueue.cc
)

TARGET_INCLUDE_DIRECTORIES(RtSandBox PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

TARGET_LINK_LIBRARIES(RtSandBox PUBLIC
  RtCore
  RtTimers
  third_party_vvv
)
