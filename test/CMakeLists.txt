execute_process(
    COMMAND wget --spider -q --tries=1 --timeout=5 google.com
    RESULT_VARIABLE INTERNET_CONNECTIVITY
)

if(INTERNET_CONNECTIVITY EQUAL 0)
  if(NOT TARGET Catch2::Catch2WithMain)
    include(FetchContent)
    FetchContent_Declare(
      Catch2
      URL https://github.com/catchorg/Catch2/archive/refs/tags/v3.13.0.tar.gz
    )
    FetchContent_MakeAvailable(
      Catch2
    )
    enable_testing()
    include(Catch)
  endif()
else()
  message(WARNING "internet seems not to be connected, so skipping fetching catch2")
endif()

get_filename_component(DIRECTORY_PATH ${CMAKE_CURRENT_LIST_DIR} ABSOLUTE)
string(REPLACE "/" "_" DIRECTORY_NAME ${DIRECTORY_PATH})
macro(BUILD_TEST "NAME")
  set("APP" ${DIRECTORY_NAME}_${NAME})
  add_executable(
    ${APP}
      ${NAME}.cpp
  )
  target_link_libraries(
    ${APP} PRIVATE
      Catch2::Catch2WithMain
      camera::lucid
  )
  set_target_properties(
    ${APP} PROPERTIES
      OUTPUT_NAME ${NAME}
      DEBUG_POSTFIX d
  )
endmacro()

if(TARGET Catch2::Catch2WithMain)
  BUILD_TEST(init)
  # BUILD_TEST(multi-sync)
  # BUILD_TEST(multi-async)
  BUILD_TEST(stream)
endif()
