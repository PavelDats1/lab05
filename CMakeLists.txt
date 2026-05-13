cmake_minimum_required(VERSION 3.10)
project(lab05)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTS "Build tests" OFF)

# Поддиректории (если есть)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_lib/CMakeLists.txt)
    add_subdirectory(formatter_lib)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/formatter_ex_lib/CMakeLists.txt)
    add_subdirectory(formatter_ex_lib)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/solver_lib/CMakeLists.txt)
    add_subdirectory(solver_lib)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/hello_world_application/CMakeLists.txt)
    add_subdirectory(hello_world_application)
endif()
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/solver_application/CMakeLists.txt)
    add_subdirectory(solver_application)
endif()

# Добавляем библиотеку print для тестов
add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)
target_include_directories(print PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
  
  file(GLOB TEST_SOURCES tests/*.cpp)
  add_executable(check ${TEST_SOURCES})
  
  # Линкуем с gtest_main (она содержит main) и gtest
  target_link_libraries(check print 
    GTest::gtest_main 
    GTest::gtest 
    pthread
  )
  
  target_include_directories(check PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  )
  
  add_test(NAME check COMMAND check)
endif()
