ADD_LIBRARY(RtMultiThread STATIC
  MtRuntime.cc
  TimerThread.cc
)

TARGET_INCLUDE_DIRECTORIES(RtMultiThread PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../..
)

TARGET_LINK_LIBRARIES(RtMultiThread PUBLIC
  RtCore
  RtTimers
  RtExe
)
