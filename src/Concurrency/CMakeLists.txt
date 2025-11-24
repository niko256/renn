ADD_SUBDIRECTORY(Spinlock)
ADD_SUBDIRECTORY(Scheduling)
# ADD_SUBDIRECTORY(WaitGroup)
ADD_SUBDIRECTORY(Fiber)
ADD_SUBDIRECTORY(Coroutine)

ADD_LIBRARY(Concurrency INTERFACE
  Spinlock
  # Scheduling
  Coroutine
  Fiber
  WaitGroup
)
