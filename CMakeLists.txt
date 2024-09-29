cmake_minimum_required(VERSION 3.0.0)
project(main)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/out/bin)

# tbd rename to pch_pkg
add_subdirectory(pchpkg)

include_directories(
  ${pch_INCLUDE_DIR}
  ${eigen_inc_dir}
)

add_subdirectory(AMBFToVR)