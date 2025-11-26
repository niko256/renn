# =============================================
# === Core : header-only

ADD_LIBRARY(FutureCore INTERFACE)

TARGET_INCLUDE_DIRECTORIES(FutureCore INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
    $<INSTALL_INTERFACE:include/Future/Core>
)

IF (futex_like_POPULATED)
  TARGET_INCLUDE_DIRECTORIES(Future INTERFACE
    ${futex_like_SOURCE_DIR}/source
  )
ENDIF()

TARGET_LINK_LIBRARIES(FutureCore INTERFACE
  third_party_futex_like
  Utils
)

# =============================================
# === Combinators : compiled free functions ===

SET(COMBINATORS_SOURCES
  Combinators/Impl/Bind.cc
  Combinators/Impl/Detach.cc
  Combinators/Impl/FlatMap.cc
  Combinators/Impl/Flatten.cc
  Combinators/Impl/Get.cc
  Combinators/Impl/Just.cc
  Combinators/Impl/Map.cc
  Combinators/Impl/Spawn.cc
  Combinators/Impl/Value.cc
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

# =============================================
# === Umbrella target ===

ADD_LIBRARY(Future INTERFACE)

TARGET_LINK_LIBRARIES(Future INTERFACE
  FutureCore
  FutureCombinators
)
