add_library(RtTimers STATIC
    TimerQueue.cc
)

target_include_directories(RtTimers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(RtTimers PUBLIC
    RtCore
)
