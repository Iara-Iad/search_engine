cmake_minimum_required(VERSION 3.5.0)
project(search_engine VERSION 0.1.0 LANGUAGES C CXX)

set(JSON_BuildTests OFF CACHE INTERNAL "")
set(gtest_disable_pthreads on)

include(FetchContent)

add_subdirectory(nlohmann_json)

FetchContent_Declare(
googletest
URL
https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# allow VERSION argument in project()
cmake_policy(SET CMP0048 NEW)

# Avoid warnings in CMake 3.24.0:
if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
		cmake_policy(SET CMP0135 NEW)
endif()



add_executable(search_engine main.cpp 
                            converterJSON.cpp
                            converterJSON.h
                            invertedIndex.cpp 
                            invertedIndex.h 
                            searchServer.cpp 
                            searchServer.h
                            tests.cpp)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(search_engine PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine)
