if(EXISTS "C:/develVSCode/cpp-projects/searchEngine/build/search_engine[1]_tests.cmake")
  include("C:/develVSCode/cpp-projects/searchEngine/build/search_engine[1]_tests.cmake")
else()
  add_test(search_engine_NOT_BUILT search_engine_NOT_BUILT)
endif()
