INCLUDE(GoogleTest)

SET(FiberTestsSrc
  FiberTests.cc
)

ADD_EXECUTABLE(FiberTests
  ${FiberTests.cc}
)

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
