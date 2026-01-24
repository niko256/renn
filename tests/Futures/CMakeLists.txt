INCLUDE(GoogleTest)

SET(LFutureTestsSrc
  LazyFutureTests.cc
)

ADD_EXECUTABLE(LFutureTests
  ${LFutureTestsSrc}
)

TARGET_LINK_LIBRARIES(LFutureTests PRIVATE
  # Fiber
  LazyFuture
  ThreadPool
  gtest_main
)

gtest_discover_tests(LFutureTests)
