cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_library(banking STATIC Account.cpp Transaction.cpp)
target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTS)
    enable_testing()
    find_package(GTest REQUIRED)
    
    file(GLOB BANKING_TEST_SOURCES tests/*.cpp)
    add_executable(banking_check ${BANKING_TEST_SOURCES})
    
    target_link_libraries(banking_check banking 
        GTest::gtest_main
        GTest::gtest
        pthread
    )
    
    target_include_directories(banking_check PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    # ЭТА СТРОКА РЕГИСТРИРУЕТ ТЕСТ
    add_test(NAME BankingTests COMMAND banking_check)
endif()
