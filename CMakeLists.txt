cmake_minimum_required(VERSION 3.16)
project(libarena)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 7)
    set(CMAKE_CXX_STANDARD 17)
  else()
    set(CMAKE_CXX_STANDARD 14)
  endif()
  set(CMAKE_CXX_STANDARD_REQUIRED True)
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Threads REQUIRED)
find_package(Arena REQUIRED)

add_library(${PROJECT_NAME} SHARED
  include/camera/api/lucid.h
  include/camera/exception.h
  include/camera/factory.h
  include/camera/device.h
  include/camera/image.h
  include/camera/system.h
  include/camera/lucid/config.hpp
  include/camera/lucid/device.hpp
  include/camera/lucid/system.hpp
  include/camera/lucid/spec.h
  include/camera/lucid/types.h
  include/camera/lucid/utils/model.h

  internal/camera/lucid/spec/common.hpp
  internal/camera/lucid/spec/htp003s_001.hpp
  internal/camera/lucid/spec/phx016s_c.hpp
  internal/camera/lucid/spec/tri028s_c.hpp
  internal/camera/lucid/network.hpp
  internal/camera/lucid/spec.hpp

  src/camera/lucid/config.cpp
  src/camera/lucid/device.cpp
  src/camera/lucid/network.cpp
  src/camera/lucid/spec.cpp
  src/camera/lucid/system.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/internal>
    $<INSTALL_INTERFACE:internal>
)

target_link_libraries(${PROJECT_NAME}
  PUBLIC
    Threads::Threads
    Arena
)

set_target_properties(${PROJECT_NAME}
  PROPERTIES
    OUTPUT_NAME "lucid"
    DEBUG_POSTFIX d
)

add_library(
  camera::lucid
    ALIAS ${PROJECT_NAME}
)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(IS_TOP_LEVEL True)
endif()

if (IS_TOP_LEVEL OR ENABLE_${PROJECT_NAME}_APP)
  add_subdirectory(app)
endif()

if (IS_TOP_LEVEL OR ENABLE_${PROJECT_NAME}_TEST)
  add_subdirectory(test)
endif()
