set(CMAKE_TOOLCHAIN_FILE CMakeModule/raspi_toolchain.cmake)

cmake_minimum_required (VERSION 3.0)

ENABLE_LANGUAGE(ASM-ATT)

set(CMAKE_VERBOSE_MAKEFILE on)

project(TestRaspiOS)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -std=c++17 -march=armv7-a -fno-rtti -fno-exceptions")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

file(GLOB_RECURSE sources_files src/*)

add_executable(${PROJECT_NAME} ${sources_files})


set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/src/linker.ld)
target_link_libraries(${PROJECT_NAME} gcc)
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT} -nostdlib")
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
