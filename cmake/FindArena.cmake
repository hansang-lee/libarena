include(GNUInstallDirs)

if(${CMAKE_LIBRARY_ARCHITECTURE} MATCHES "x86_64")
  set(SUFFIX_Arena_LIB_DIR "lib64")
  set(SUFFIX_GenICam_LIB_DIR "GenICam/library/lib/Linux64_x64")
  set(SUFFIX_ffmpeg_LIB_DIR "ffmpeg")
elseif(${CMAKE_LIBRARY_ARCHITECTURE} MATCHES "aarch64")
  set(SUFFIX_Arena_LIB_DIR "lib")
  set(SUFFIX_GenICam_LIB_DIR "GenICam/library/lib/Linux64_ARM")
  set(SUFFIX_ffmpeg_LIB_DIR "ffmpeg")
else()
  message(FATAL_ERROR "[FindArena.cmake] Unknown Architecture: ${CMAKE_LIBRARY_ARCHITECTURE}")
endif()

set(FOUND_PACKAGE FALSE)
set(ARENA_INSTALL_DIRS
  "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
  "/usr/local/lib"
  "/usr/lib"
)

# INSTALLATION PATH
foreach(DIR IN LISTS ARENA_INSTALL_DIRS)
  if(NOT FOUND_PACKAGE)
    if(EXISTS ${DIR}/arena)
      set(ARENA_PACKAGE_DIR arena)
      set(ARENA_PACKAGE_INSTALL_DIR ${DIR})
      set(FOUND_PACKAGE TRUE)
      break()
    elseif(EXISTS ${DIR}/ArenaSDK_Linux_x64)
      set(ARENA_PACKAGE_DIR ArenaSDK_Linux_x64)
      set(ARENA_PACKAGE_INSTALL_DIR ${DIR})
      set(FOUND_PACKAGE TRUE)
      break()
    elseif(EXISTS ${DIR}/ArenaSDK_Linux_ARM64)
      set(ARENA_PACKAGE_DIR ArenaSDK_Linux_ARM64)
      set(ARENA_PACKAGE_INSTALL_DIR ${DIR})
      set(FOUND_PACKAGE TRUE)
      break()
    endif()
  else()
    break()
  endif()
endforeach()

if(FOUND_PACKAGE)
  message(STATUS "[FindArena.cmake] Found ArenaSDK: ${ARENA_PACKAGE_INSTALL_DIR}")
else()
  message(FATAL_ERROR "[FindArena.cmake] Not Found ArenaSDK")
endif()

# ARENA
find_path(
  ARENA_API_INCLUDE_DIR
    NAMES "ArenaApi.h"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "include/Arena"
    NO_DEFAULT_PATH
)
find_library(
  ARENA_LIBRARY
    NAMES "arena"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "${SUFFIX_Arena_LIB_DIR}"
    NO_DEFAULT_PATH
)
if(ARENA_API_INCLUDE_DIR AND ARENA_LIBRARY)
  message(STATUS "[FindArena.cmake] Found components for Arena")
  message(STATUS "[FindArena.cmake] ${ARENA_API_INCLUDE_DIR}")
  message(STATUS "[FindArena.cmake] ${ARENA_LIBRARY}")
endif()

# GENTL
find_path(
  GENTL_INCLUDE_DIR
    NAMES "GenTL.h"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "include/GenTL"
    NO_DEFAULT_PATH
)
find_library(
  GENTL_LIBRARY
    NAMES "gentl"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "${SUFFIX_Arena_LIB_DIR}"
    NO_DEFAULT_PATH
)
if(GENTL_INCLUDE_DIR AND GENTL_LIBRARY)
  message(STATUS "[FindArena.cmake] Found components for GenTL")
  message(STATUS "[FindArena.cmake] ${GENTL_INCLUDE_DIR}")
  message(STATUS "[FindArena.cmake] ${GENTL_LIBRARY}")
endif()

# GENICAM
find_path(
  GENICAM_INCLUDE_DIR
    NAMES "GenICam.h"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "GenICam/library/CPP/include"
    NO_DEFAULT_PATH
)
find_library(
  GenApi_gcc54_v3_3_LUCID_LIBRARY
    NAMES "GenApi_gcc54_v3_3_LUCID"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "${SUFFIX_GenICam_LIB_DIR}"
    NO_DEFAULT_PATH
)
find_library(
  GCBase_gcc54_v3_3_LUCID_LIBRARY
    NAMES "GCBase_gcc54_v3_3_LUCID"
    PATHS "${ARENA_PACKAGE_INSTALL_DIR}/${ARENA_PACKAGE_DIR}"
    PATH_SUFFIXES "${SUFFIX_GenICam_LIB_DIR}"
    NO_DEFAULT_PATH
)
if(GENICAM_INCLUDE_DIR AND GenApi_gcc54_v3_3_LUCID_LIBRARY AND GCBase_gcc54_v3_3_LUCID_LIBRARY)
  message(STATUS "[FindArena.cmake] Found components for GenICam")
  message(STATUS "[FindArena.cmake] ${GENICAM_INCLUDE_DIR}")
  message(STATUS "[FindArena.cmake] ${GenApi_gcc54_v3_3_LUCID_LIBRARY}")
  message(STATUS "[FindArena.cmake] ${GCBase_gcc54_v3_3_LUCID_LIBRARY}")
endif()

set(ARENA_INCLUDE_DIRS
  ${ARENA_API_INCLUDE_DIR}
  ${GENTL_INCLUDE_DIR}
  ${GENICAM_INCLUDE_DIR}
)

set(ARENA_LIBRARIES
  ${ARENA_LIBRARY}
  ${GENTL_LIBRARY}
  ${GenApi_gcc54_v3_3_LUCID_LIBRARY}
  ${GCBase_gcc54_v3_3_LUCID_LIBRARY}
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  Arena DEFAULT_MSG
    "ARENA_INCLUDE_DIRS"
    "ARENA_LIBRARIES"
)

if(NOT TARGET Arena::ArenaApi)
  add_library(
    Arena::ArenaApi
    UNKNOWN IMPORTED
  )
  set_target_properties(
    Arena::ArenaApi
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${ARENA_API_INCLUDE_DIR}"
      IMPORTED_LOCATION "${ARENA_LIBRARY}"
  )
endif()

if(NOT TARGET Arena::GenTL)
  add_library(
    Arena::GenTL
    UNKNOWN IMPORTED
  )
  set_target_properties(
    Arena::GenTL
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${GENTL_INCLUDE_DIR}"
      IMPORTED_LOCATION "${GENTL_LIBRARY}"
  )
endif()

if(NOT TARGET Arena::GenICam)
  add_library(
    Arena::GenICam
    UNKNOWN IMPORTED
  )
  set_target_properties(
    Arena::GenICam
    PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${GENICAM_INCLUDE_DIR}"
      IMPORTED_LOCATION "${GenApi_gcc54_v3_3_LUCID_LIBRARY}"
      IMPORTED_LOCATION "${GCBase_gcc54_v3_3_LUCID_LIBRARY}"
  )
endif()

if(NOT TARGET Arena)
  add_library(
    Arena
      INTERFACE IMPORTED
  )
  set_property(
    TARGET Arena
    PROPERTY INTERFACE_LINK_LIBRARIES
      "Arena::ArenaApi"
      "Arena::GenTL"
      "Arena::GenICam"
  )
endif()

mark_as_advanced(
  ARENA_INCLUDE_DIRS
  ARENA_LIBRARIES
)
