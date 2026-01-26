SET(FIBER_CORE_SOURCES
  Core/Fiber.cc
  Core/Handle.cc
)

SET(FIBER_FFS_SOURCES
  ExeCtrl/Go.cc
  ExeCtrl/Yield.cc
  ExeCtrl/SleepFor.cc
)


ADD_LIBRARY(Fiber STATIC
  ${FIBER_CORE_SOURCES}
  ${FIBER_FFS_SOURCES}
)


TARGET_INCLUDE_DIRECTORIES(Fiber PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/..
)


TARGET_LINK_LIBRARIES(Fiber PUBLIC
  third_party_vvv
  Coroutine
  RtCore
  Utils
)
