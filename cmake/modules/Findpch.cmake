find_path(pch_INCLUDE_DIR
  NAMES pch/pch.h
  HINTS ${CMAKE_SOURCE_DIR}/pchpkg
  PATH_SUFFIXES include
  )