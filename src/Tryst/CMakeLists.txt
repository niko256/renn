# =*= Core : header-only =*=

ADD_LIBRARY(TrystCore INTERFACE)

TARGET_INCLUDE_DIRECTORIES(TrystCore INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Core>
    $<INSTALL_INTERFACE:include/Tryst/Core>
)

IF (futex_like_POPULATED)
  TARGET_INCLUDE_DIRECTORIES(TrystCore INTERFACE
    ${futex_like_SOURCE_DIR}/source
  )
ENDIF()

TARGET_LINK_LIBRARIES(TrystCore INTERFACE
  Utils
)

SET(TrystImpl
  Impl/Contract.cc
  Impl/Get.cc
)

ADD_LIBRARY(TrystImpl STATIC)

TARGET_LINK_LIBRARIES(TrystImpl PUBLIC
  Event
  Utils
)
