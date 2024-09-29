cmake_minimum_required(VERSION 3.0.0)
project(AMBFToVR)

set(target_libraries
  PRIVATE glfw 
  PRIVATE GLU 
  PRIVATE GL 
  PRIVATE Xrandr 
  # PRIVATE Xxf86vm 
  PRIVATE Xi 
  PRIVATE Xinerama 
  PRIVATE X11 
  PRIVATE rt 
  PRIVATE dl
  pthread
  PRIVATE GLEW
  PRIVATE z
  PRIVATE ${OpenVRSDK_SOURCE_DIR}/bin/linux64/libopenvr_api.so
  )

set(HEADER_DIR
  # include
  ${OpenVRSDK_SOURCE_DIR}/headers
)

set(project_name
  opengl_to_vr
)

set(SRC_FILES
  src/${project_name}.cpp
)

set(project_app ${project_name}_app)

ADD_EXECUTABLE(${project_app}
  ${SRC_FILES}
)


# target_precompile_headers(${project_app} PRIVATE ${pch_INCLUDE_DIR}/pch/pch.h)

target_include_directories(${project_app}
  PRIVATE ${HEADER_DIR}
#   # PRIVATE ${eigen_utils_lib_SOURCE_DIR}/include
)

#Set Linker flags
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

target_link_libraries(${project_app} 

  # PRIVATE eigen_utils_lib
  PRIVATE ${target_libraries}
  
)

set_target_properties(${project_app} PROPERTIES 
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED YES
)