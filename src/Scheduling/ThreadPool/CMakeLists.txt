ADD_LIBRARY(ThreadPool STATIC ThreadPool.cc)

TARGET_LINK_LIBRARIES(ThreadPool PUBLIC Scheduling)


TARGET_INCLUDE_DIRECTORIES(
    ThreadPool
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include/renn/src/Scheduling/ThreadPool>
)
