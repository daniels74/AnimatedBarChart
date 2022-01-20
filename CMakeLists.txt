cmake_minimum_required(VERSION 3.22) # version can be different

project(project_3) #name of your project

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

#add_executable(mytests mytests.cpp) # add this executable

#//target_link_libraries(mytests PRIVATE gtest) # link google test to this executable

enable_testing()

add_executable(
  tests
  tests.cpp
)
target_link_libraries(
  tests
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

add_executable(
  application
  application.cpp
)
