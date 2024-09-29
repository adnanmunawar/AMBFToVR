cmake_minimum_required(VERSION 3.0.0)
project(PCH)

add_subdirectory(external/openvr)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

set(PCH_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

# find_package(Eigen3 REQUIRED)
find_package(pch REQUIRED)