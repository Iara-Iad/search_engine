cmake_minimum_required (VERSION 3.5.0)

set(Src
	"converterJSON.cpp"
	"searchServer.cpp"
	"invertedIndex.cpp"
	"main.cpp"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(search_engine ${Src})

target_link_libraries(search_engine nlohmann_json::nlohmann_json)
target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})