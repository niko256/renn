CMAKE_MINIMUM_REQUIRED(VERSION 3.30)
PROJECT(Tests LANGUAGES CXX)

SET(CMAKE_BUILD_TYPE Debug)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

INCLUDE(GoogleTest)



ADD_EXECUTABLE(SpinlockTests SpinlockTests.cc)
TARGET_LINK_LIBRARIES(SpinlockTests PRIVATE
  Spinlock
  gtest_main
)
gtest_discover_tests(SpinlockTests)


ADD_EXECUTABLE(ThreadPoolTests ThreadPoolTests.cc)
TARGET_LINK_LIBRARIES(ThreadPoolTests PRIVATE
  ThreadPool
  WaitGroup
  gtest_main
  Scheduling
)
gtest_discover_tests(ThreadPoolTests)

ADD_EXECUTABLE(EventTest EventTest.cc)
TARGET_LINK_LIBRARIES(EventTest PRIVATE
  Event
)


ADD_EXECUTABLE(FiberTests FiberTests.cc)
TARGET_LINK_LIBRARIES(FiberTests PRIVATE
  Fiber
  ThreadPool
  WaitGroup
  Coroutine
  third_party_sure
  gtest_main
  third_party_futex_like
  # fmt::fmt
)
gtest_discover_tests(FiberTests)
