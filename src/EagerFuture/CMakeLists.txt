# === Core : header-only ===

ADD_LIBRARY(FutureCore INTERFACE)

TARGET_INCLUDE_DIRECTORIES(FutureCore INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
    $<INSTALL_INTERFACE:include/Future/Core>
)

TARGET_LINK_LIBRARIES(FutureCore INTERFACE
  third_party_futex_like
  Utils
)

# =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# =*= Combinators : compiled free functions =*=

SET(COMBINATORS_SOURCES
# ...
)

ADD_LIBRARY(FutureCombinators STATIC
  ${COMBINATORS_SOURCES}
)

TARGET_INCLUDE_DIRECTORIES(FutureCombinators PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Combinators>
  $<INSTALL_INTERFACE:include/Future/Combinators>
)

TARGET_LINK_LIBRARIES(FutureCombinators PUBLIC
  FutureCore
  Utils
)

# =*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*
# =*= Umbrella target =*=

ADD_LIBRARY(Future INTERFACE)

TARGET_LINK_LIBRARIES(Future INTERFACE
  FutureCore
  FutureCombinators
)
