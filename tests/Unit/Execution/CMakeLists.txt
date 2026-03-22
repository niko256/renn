INCLUDE(GoogleTest)

SET(ExecutionTestsSrc
  ThreadPoolTests.cc
)

ADD_EXECUTABLE(ExecutionTests
  ${ExecutionTestsSrc}
)

TARGET_LINK_LIBRARIES(ExecutionTests PRIVATE
  ThreadPool
  WaitGroup
  gtest_main
  RtExe
)

gtest_discover_tests(ExecutionTests)
