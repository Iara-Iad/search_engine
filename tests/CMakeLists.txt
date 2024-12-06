cmake_minimum_required (VERSION 3.5.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SrcFiles
	${MY_SRC_DIR}/invertedIndex.cpp
	${MY_SRC_DIR}/searchServer.cpp
	${MY_SRC_DIR}/converterJSON.cpp
)

set(TestsFiles
	invertedIndex_test.cpp
	searchServer_test.cpp
)

add_executable(GtestTests ${TestsFiles} ${SrcFiles})
target_link_libraries(GtestTests nlohmann_json::nlohmann_json GTest::gtest_main)
include(GoogleTest)
target_include_directories(GtestTests PUBLIC ${MY_INCLUDE_DIR})
gtest_discover_tests(GtestTests)