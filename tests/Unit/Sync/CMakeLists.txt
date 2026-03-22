INCLUDE(GoogleTest)

SET(SyncSrc
  EventTests.cc
  SpinlockTests.cc
  WaitGroupTests.cc
)

ADD_EXECUTABLE(SyncTests
  ${SyncSrc}
)

TARGET_LINK_LIBRARIES(SyncTests PRIVATE
  Event
  Spinlock
  gtest_main
)

gtest_discover_tests(SyncTests)
