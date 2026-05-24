cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Библиотека banking
add_library(banking STATIC
    banking/src/Account.cpp
    banking/src/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/banking/include
)

# Подключаем GTest
enable_testing()
find_package(GTest REQUIRED)

# Тесты
add_executable(tests
    tests/test_account.cpp
    tests/test_transaction.cpp
)

target_link_libraries(tests banking GTest::GTest GTest::Main)
target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/banking/include
)

add_test(NAME BankingTests COMMAND tests)
