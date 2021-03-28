cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE pkgs/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -Os")
set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

add_definitions(-DSPIDER_VERSION=${SPIDER_VERSION})

project(spider)

FILE(GLOB source src/*.cc src/application/*.cc src/database/*.cc)
add_executable(spider ${source})

if (UNIX AND NOT APPLE)
  target_link_libraries(spider PRIVATE stdc++fs)
endif ()

target_link_libraries(spider PRIVATE stdc++ pthread dl)

if (CMAKE_BUILD_TYPE STREQUAL release)
  add_custom_command(TARGET spider POST_BUILD COMMAND strip spider)
endif ()

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(spider PRIVATE nlohmann_json nlohmann_json::nlohmann_json)

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(spider PRIVATE spdlog::spdlog)

find_path(CPP_HTTPLIB_INCLUDE_DIRS "httplib.h")
target_include_directories(spider PRIVATE ${CPP_HTTPLIB_INCLUDE_DIRS})

target_include_directories(spider PRIVATE src/include)

message("System info: ${CMAKE_SYSTEM}")
message("System name: ${CMAKE_SYSTEM_NAME}")
message("System processor: ${CMAKE_SYSTEM_PROCESSOR}")
message("System host name: ${CMAKE_HOST_SYSTEM_NAME}")
message("CXX Standard: ${CMAKE_CXX_STANDARD}")
