# Отчет по лабораторной работе №5

## Изучение фреймворков для тестирования на примере GTest

**Студент:** Павел Д  
**Дата выполнения:** 13.05.2026

---

## 1. Подготовка и настройка

### 1.1 Клонирование репозитория из lab04

```bash
cd ~/workspace/PavelDats1
```

```bash
rm -rf projects/lab05
```

```bash
git clone https://github.com/PavelDats1/lab04.git projects/lab05

Cloning into 'projects/lab05'...
remote: Enumerating objects: 99, done.
remote: Counting objects: 100% (99/99), done.
remote: Compressing objects: 100% (68/68), done.
remote: Total 99 (delta 27), reused 95 (delta 23), pack-reused 0 (from 0)
Receiving objects: 100% (99/99), 24.70 KiB | 3.53 MiB/s, done.
Resolving deltas: 100% (27/27), done.

```

```bash
cd projects/lab05
```

```bash
git remote remove origin
```

```bash
git remote add origin https://github.com/PavelDats1/lab05.git
```

```bash
git push -u origin master

Enumerating objects: 14, done.
Counting objects: 100% (14/14), done.
Delta compression using up to 2 threads
Compressing objects: 100% (13/13), done.
Writing objects: 100% (14/14), 1.40 KiB | 479.00 KiB/s, done.
Total 14 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), done.
remote: 
remote: Create a pull request for 'master' on GitHub by visiting:
remote:      https://github.com/PavelDats1/lab05/pull/new/master
remote: 
To https://github.com/PavelDats1/lab05.git
 * [new branch]      master -> master
branch 'master' set up to track 'origin/master'.

```

### 1.2 Добавление Google Test

```bash
mkdir -p third-party
```

```bash
git submodule add https://github.com/google/googletest third-party/gtest
output:
Cloning into '/home/pavel/workspace/PavelDats1/third-party/gtest'...
remote: Enumerating objects: 28627, done.
remote: Counting objects: 100% (61/61), done.
remote: Compressing objects: 100% (46/46), done.
remote: Total 28627 (delta 32), reused 15 (delta 15), pack-reused 28566 (from 2)
Receiving objects: 100% (28627/28627), 13.74 MiB | 12.39 MiB/s, done.
Resolving deltas: 100% (21273/21273), done.

```

```bash
cd third-party/gtest && git checkout release-1.8.1 && cd ../..
output:
Note: switching to 'release-1.8.1'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by switching back to a branch.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -c with the switch command. Example:

  git switch -c <new-branch-name>

Or undo this operation with:

  git switch -

Turn off this advice by setting config variable advice.detachedHead to false

HEAD is now at 2fe3bd99 Merge pull request #1433 from dsacre/fix-clang-warnings
```

```bash
git add third-party/gtest
```

```bash
git commit -m "added gtest framework"
output:
[master 766211e] added gtest framework
 2 files changed, 4 insertions(+)
 create mode 100644 .gitmodules
 create mode 160000 workspace/PavelDats1/third-party/gtest
```

## 2. Обновление CMakeLists.txt

### 2.1 Добавление опции BUILD_TESTS

```bash
sed -i '/option(BUILD_EXAMPLES "Build examples" OFF)/a\
option(BUILD_TESTS "Build tests" OFF)
' CMakeLists.txt
```

### 2.2 Добавление конфигурации тестов

```bash
cat >> CMakeLists.txt <<'EOF'

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(third-party/gtest)
  file(GLOB ${PROJECT_NAME}_TEST_SOURCES tests/*.cpp)
  add_executable(check ${${PROJECT_NAME}_TEST_SOURCES})
  target_link_libraries(check ${PROJECT_NAME} gtest_main)
  target_include_directories(check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
  add_test(NAME check COMMAND check)
endif()
EOF
```

## 3. Создание тестов для функции print

### 3.1 Создание необходимых файлов

```bash
mkdir -p sources include tests
```

```bash
cat > include/print.hpp <<'EOF'
#include <fstream>
#include <iostream>
#include <string>

void print(const std::string& text, std::ofstream& out);
void print(const std::string& text, std::ostream& out = std::cout);
EOF
```

```bash
cat > sources/print.cpp <<'EOF'
#include <print.hpp>

void print(const std::string& text, std::ostream& out)
{
    out << text;
}

void print(const std::string& text, std::ofstream& out)
{
    out << text;
}
EOF
```

### 3.2 Создание тестового файла

```bash
cat > tests/test1.cpp <<'EOF'
#include <print.hpp>
#include <gtest/gtest.h>

TEST(Print, InFileStream)
{
  std::string filepath = "file.txt";
  std::string text = "hello";
  std::ofstream out{filepath};

  print(text, out);
  out.close();

  std::string result;
  std::ifstream in{filepath};
  in >> result;

  EXPECT_EQ(result, text);
}
EOF
```

## 4. Сборка и запуск тестов

### 4.1 Конфигурация с включенными тестами

```bash
cmake -H. -B_build -DBUILD_TESTS=ON
```

**Листинг вывода:**

```
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
CMake Deprecation Warning at formatter_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at solver_lib/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at third-party/gtest/CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at third-party/gtest/googlemock/CMakeLists.txt:42 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Deprecation Warning at third-party/gtest/googletest/CMakeLists.txt:49 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


CMake Warning (dev) at third-party/gtest/googletest/cmake/internal_utils.cmake:239 (find_package):
  Policy CMP0148 is not set: The FindPythonInterp and FindPythonLibs modules
  are removed.  Run "cmake --help-policy CMP0148" for policy details.  Use
  the cmake_policy command to set the policy and suppress this warning.

Call Stack (most recent call first):
  third-party/gtest/googletest/CMakeLists.txt:84 (include)
This warning is for project developers.  Use -Wno-dev to suppress it.

-- Found PythonInterp: /usr/bin/python3 (found version "3.12.3") 
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- Configuring done (1.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/workspace/PavelDats1/projects/lab05/_build

```

### 4.2 Сборка проекта

```bash
cmake --build _build
```

**Листинг вывода:**

```
[  7%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 14%] Linking CXX static library libprint.a
[ 14%] Built target print
[ 21%] Building CXX object CMakeFiles/check.dir/tests/test1.cpp.o
[ 28%] Linking CXX executable check
[ 28%] Built target check
[ 35%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 42%] Linking CXX static library libformatter.a
[ 42%] Built target formatter
[ 50%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 57%] Linking CXX static library libformatter_ex.a
[ 57%] Built target formatter_ex
[ 64%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 71%] Linking CXX static library libsolver_lib.a
[ 71%] Built target solver_lib
[ 78%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 85%] Linking CXX executable hello_world
[ 85%] Built target hello_world
[ 92%] Building CXX object solver_application/CMakeFiles/solver.dir/solver.cpp.o
[100%] Linking CXX executable solver
[100%] Built target solver

```

### 4.3 Запуск тестов

```bash
./_build/check
```

**Листинг вывода:**

```
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from Print
[ RUN      ] Print.InFileStream
[       OK ] Print.InFileStream (0 ms)
[----------] 1 test from Print (0 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (0 ms total)
[  PASSED  ] 1 test.

```

```bash
cmake --build _build --target test
```

**Листинг вывода:**

```
Running tests...
Test project /home/pavel/workspace/PavelDats1/projects/lab05/_build
    Start 1: check
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.01 sec

```

```bash
cmake --build _build --target test -- ARGS=--verbose
```

**Листинг вывода:**

```
Running tests...
UpdateCTestConfiguration  from :/home/pavel/workspace/PavelDats1/projects/lab05/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/pavel/workspace/PavelDats1/projects/lab05/_build/DartConfiguration.tcl
Test project /home/pavel/workspace/PavelDats1/projects/lab05/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/pavel/workspace/PavelDats1/projects/lab05/_build/check
1: Working Directory: /home/pavel/workspace/PavelDats1/projects/lab05/_build
1: Test timeout computed to be: 10000000
1: Running main() from ./googletest/src/gtest_main.cc
1: [==========] Running 1 test from 1 test suite.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Print
1: [ RUN      ] Print.InFileStream
1: [       OK ] Print.InFileStream (1 ms)
1: [----------] 1 test from Print (1 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 1 test from 1 test suite ran. (1 ms total)
1: [  PASSED  ] 1 test.
1/1 Test #1: check ............................   Passed    0.01 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.02 sec
```

### 4.4 Установка проекта

```bash
cmake --build _build --target install
output:
[ 14%] Built target print
[ 28%] Built target check
[ 42%] Built target formatter
[ 57%] Built target formatter_ex
[ 71%] Built target solver_lib
[ 85%] Built target hello_world
[100%] Built target solver
Install the project...
-- Install configuration: ""
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab05/_install/bin/hello_world
-- Up-to-date: /home/pavel/workspace/PavelDats1/projects/lab05/_install/bin/hello_world
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab05/_install/bin/solver
-- Up-to-date: /home/pavel/workspace/PavelDats1/projects/lab05/_install/bin/solver

```

```bash
tree _install
output:
_install
└── bin
    ├── hello_world
    └── solver

2 directories, 2 files

```

### 4.5 Сохранение изменений в Git

```bash
git add tests
```

```bash
git commit -m "added tests"
output:
[main 172b2b8] added tests
 1 file changed, 19 insertions(+)
 create mode 100644 tests/test1.cpp

```

```bash
git push origin main
output:
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 9, done.
Counting objects: 100% (9/9), done.
Delta compression using up to 2 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (8/8), 887 bytes | 887.00 KiB/s, done.
Total 8 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 1 local object.
To https://github.com/PavelDats1/lab04.git
   8e9e376..172b2b8  main -> main

```

## 5. Домашнее задание (библиотека banking)

### 5.1 Создание директории и класса Account

```bash
mkdir -p banking
```

```bash
cd banking
```

```bash
cat > Account.h <<'EOF'
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <stdexcept>

class Account {
private:
    int id;
    std::string name;
    double balance;

public:
    Account(int id, const std::string& name, double initialBalance = 0.0);
    virtual ~Account() = default;

    int getId() const;
    std::string getName() const;
    double getBalance() const;

    virtual void deposit(double amount);
    virtual void withdraw(double amount);
    void transfer(Account& to, double amount);
};

#endif
EOF
```

```bash
cat > Account.cpp <<'EOF'
#include "Account.h"

Account::Account(int id, const std::string& name, double initialBalance)
    : id(id), name(name), balance(initialBalance) {}

int Account::getId() const { return id; }
std::string Account::getName() const { return name; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive");
    }
    balance += amount;
}

void Account::withdraw(double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    balance -= amount;
}

void Account::transfer(Account& to, double amount) {
    withdraw(amount);
    to.deposit(amount);
}
EOF
```

### 5.2 Создание класса Transaction

```bash
cat > Transaction.h <<'EOF'
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

class Transaction {
private:
    int fromId;
    int toId;
    double amount;
    std::time_t timestamp;
    std::string status;

public:
    Transaction(int fromId, int toId, double amount);

    int getFromId() const;
    int getToId() const;
    double getAmount() const;
    std::time_t getTimestamp() const;
    std::string getStatus() const;

    void execute();
    void rollback();
};

#endif
EOF
```

```bash
cat > Transaction.cpp <<'EOF'
#include "Transaction.h"
#include <iostream>

Transaction::Transaction(int fromId, int toId, double amount)
    : fromId(fromId), toId(toId), amount(amount), status("pending") {
    timestamp = std::time(nullptr);
}

int Transaction::getFromId() const { return fromId; }
int Transaction::getToId() const { return toId; }
double Transaction::getAmount() const { return amount; }
std::time_t Transaction::getTimestamp() const { return timestamp; }
std::string Transaction::getStatus() const { return status; }

void Transaction::execute() {
    if (status == "pending") {
        status = "completed";
        std::cout << "Transaction executed: " << fromId << " -> " << toId 
                  << " amount: " << amount << std::endl;
    }
}

void Transaction::rollback() {
    if (status == "completed") {
        status = "rolled_back";
        std::cout << "Transaction rolled back: " << fromId << " -> " << toId 
                  << " amount: " << amount << std::endl;
    }
}
EOF
```

### 5.3 Создание CMakeLists.txt для banking

```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_library(banking STATIC Account.cpp Transaction.cpp)
target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(../third-party/gtest ${CMAKE_BINARY_DIR}/gtest)
    file(GLOB BANKING_TEST_SOURCES tests/*.cpp)
    add_executable(banking_check ${BANKING_TEST_SOURCES})
    target_link_libraries(banking_check banking gtest_main gmock_main)
    target_include_directories(banking_check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME banking_check COMMAND banking_check)
endif()
EOF
```

### 5.4 Создание тестов для Account

```bash
mkdir -p tests
```

```bash
cat > tests/test_account.cpp <<'EOF'
#include <gtest/gtest.h>
#include "Account.h"

TEST(AccountTest, ConstructorAndGetters) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_EQ(acc.getId(), 1);
    EXPECT_EQ(acc.getName(), "John Doe");
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1000.0);
}

TEST(AccountTest, Deposit) {
    Account acc(1, "John Doe", 1000.0);
    acc.deposit(500.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 1500.0);
}

TEST(AccountTest, DepositNegativeAmount) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_THROW(acc.deposit(-100.0), std::invalid_argument);
}

TEST(AccountTest, Withdraw) {
    Account acc(1, "John Doe", 1000.0);
    acc.withdraw(300.0);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 700.0);
}

TEST(AccountTest, WithdrawInsufficientFunds) {
    Account acc(1, "John Doe", 100.0);
    EXPECT_THROW(acc.withdraw(200.0), std::runtime_error);
}

TEST(AccountTest, WithdrawNegativeAmount) {
    Account acc(1, "John Doe", 1000.0);
    EXPECT_THROW(acc.withdraw(-50.0), std::invalid_argument);
}

TEST(AccountTest, Transfer) {
    Account from(1, "John Doe", 1000.0);
    Account to(2, "Jane Smith", 500.0);
    from.transfer(to, 300.0);
    EXPECT_DOUBLE_EQ(from.getBalance(), 700.0);
    EXPECT_DOUBLE_EQ(to.getBalance(), 800.0);
}

TEST(AccountTest, TransferInsufficientFunds) {
    Account from(1, "John Doe", 100.0);
    Account to(2, "Jane Smith", 500.0);
    EXPECT_THROW(from.transfer(to, 200.0), std::runtime_error);
}
EOF
```

### 5.5 Создание тестов для Transaction

```bash
cat > tests/test_transaction.cpp <<'EOF'
#include <gtest/gtest.h>
#include "Transaction.h"

TEST(TransactionTest, ConstructorAndGetters) {
    Transaction tx(1, 2, 500.0);
    EXPECT_EQ(tx.getFromId(), 1);
    EXPECT_EQ(tx.getToId(), 2);
    EXPECT_DOUBLE_EQ(tx.getAmount(), 500.0);
    EXPECT_EQ(tx.getStatus(), "pending");
}

TEST(TransactionTest, Execute) {
    Transaction tx(1, 2, 500.0);
    tx.execute();
    EXPECT_EQ(tx.getStatus(), "completed");
}

TEST(TransactionTest, Rollback) {
    Transaction tx(1, 2, 500.0);
    tx.execute();
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "rolled_back");
}

TEST(TransactionTest, CannotRollbackPending) {
    Transaction tx(1, 2, 500.0);
    tx.rollback();
    EXPECT_EQ(tx.getStatus(), "pending");
}
EOF
```

### 5.6 Создание mock-тестов

```bash
cat > tests/test_mock.cpp <<'EOF'
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Account.h"

class MockAccount : public Account {
public:
    MockAccount(int id, const std::string& name, double balance)
        : Account(id, name, balance) {}

    MOCK_METHOD(void, deposit, (double amount), (override));
    MOCK_METHOD(void, withdraw, (double amount), (override));
};

TEST(MockAccountTest, DepositMock) {
    MockAccount acc(1, "Test", 1000);
    EXPECT_CALL(acc, deposit(500)).Times(1);
    acc.deposit(500);
}

TEST(MockAccountTest, WithdrawMock) {
    MockAccount acc(1, "Test", 1000);
    EXPECT_CALL(acc, withdraw(300)).Times(1);
    acc.withdraw(300);
}
EOF
```

### 5.7 Сборка и запуск тестов banking

```bash
cd banking
```

```bash
mkdir -p _build && cd _build
```

```bash
cmake .. -DBUILD_TESTS=ON
```
output:
```
-- The C compiler identification is GNU 13.3.0
-- The CXX compiler identification is GNU 13.3.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/cc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Found GTest: /usr/lib/x86_64-linux-gnu/cmake/GTest/GTestConfig.cmake (found version "1.14.0")  
-- Configuring done (0.8s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/workspace/PavelDats1/projects/lab05/banking/_build

```

```bash
cmake --build .
```
output:
```
[ 16%] Building CXX object CMakeFiles/banking.dir/Account.cpp.o
[ 33%] Building CXX object CMakeFiles/banking.dir/Transaction.cpp.o
[ 50%] Linking CXX static library libbanking.a
[ 50%] Built target banking
[ 66%] Building CXX object CMakeFiles/banking_check.dir/tests/test_account.cpp.o
[ 83%] Building CXX object CMakeFiles/banking_check.dir/tests/test_transaction.cpp.o
[100%] Linking CXX executable banking_check
[100%] Built target banking_check

```

```bash
./banking_check
```

output:
```
[ 16%] Building CXX object CMakeFiles/banking.dir/Account.cpp.o
[ 33%] Building CXX object CMakeFiles/banking.dir/Transaction.cpp.o
[ 50%] Linking CXX static library libbanking.a
[ 50%] Built target banking
[ 66%] Building CXX object CMakeFiles/banking_check.dir/tests/test_account.cpp.o
[ 83%] Building CXX object CMakeFiles/banking_check.dir/tests/test_transaction.cpp.o
[100%] Linking CXX executable banking_check
[100%] Built target banking_check
pavel@pavel:~/workspace/PavelDats1/projects/lab05/banking/_build$ ./banking_check
Running main() from ./googletest/src/gtest_main.cc
[==========] Running 12 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 8 tests from AccountTest
[ RUN      ] AccountTest.ConstructorAndGetters
[       OK ] AccountTest.ConstructorAndGetters (0 ms)
[ RUN      ] AccountTest.Deposit
[       OK ] AccountTest.Deposit (0 ms)
[ RUN      ] AccountTest.DepositNegativeAmount
[       OK ] AccountTest.DepositNegativeAmount (0 ms)
[ RUN      ] AccountTest.Withdraw
[       OK ] AccountTest.Withdraw (0 ms)
[ RUN      ] AccountTest.WithdrawInsufficientFunds
[       OK ] AccountTest.WithdrawInsufficientFunds (0 ms)
[ RUN      ] AccountTest.WithdrawNegativeAmount
[       OK ] AccountTest.WithdrawNegativeAmount (0 ms)
[ RUN      ] AccountTest.Transfer
[       OK ] AccountTest.Transfer (0 ms)
[ RUN      ] AccountTest.TransferInsufficientFunds
[       OK ] AccountTest.TransferInsufficientFunds (0 ms)
[----------] 8 tests from AccountTest (0 ms total)

[----------] 4 tests from TransactionTest
[ RUN      ] TransactionTest.ConstructorAndGetters
[       OK ] TransactionTest.ConstructorAndGetters (0 ms)
[ RUN      ] TransactionTest.Execute
Transaction executed: 1 -> 2 amount: 500
[       OK ] TransactionTest.Execute (0 ms)
[ RUN      ] TransactionTest.Rollback
Transaction executed: 1 -> 2 amount: 500
Transaction rolled back: 1 -> 2 amount: 500
[       OK ] TransactionTest.Rollback (0 ms)
[ RUN      ] TransactionTest.CannotRollbackPending
[       OK ] TransactionTest.CannotRollbackPending (0 ms)
[----------] 4 tests from TransactionTest (0 ms total)

[----------] Global test environment tear-down
[==========] 12 tests from 2 test suites ran. (0 ms total)
[  PASSED  ] 12 tests.

```

```bash
cd ../..
```

## 6. Настройка GitHub Actions

```bash
mkdir -p .github/workflows
```

```bash
cat > .github/workflows/ci.yml <<'EOF'
name: CI

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build-and-test:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4
      with:
        submodules: recursive

    - name: Install dependencies
      run: |
        sudo apt update
        sudo apt install -y cmake g++

    - name: Configure CMake for main tests
      run: cmake -H. -B_build -DBUILD_TESTS=ON

    - name: Build main tests
      run: cmake --build _build

    - name: Run main tests
      run: cmake --build _build --target test -- ARGS=--verbose

    - name: Configure banking tests
      run: |
        cd banking
        cmake -H. -B_build -DBUILD_TESTS=ON
        cd ..

    - name: Build banking tests
      run: |
        cd banking
        cmake --build _build
        cd ..

    - name: Run banking tests
      run: |
        cd banking/_build
        ./banking_check
        cd ../..
EOF
```

## 7. Настройка Coveralls.io

```bash
cat > .github/workflows/coveralls.yml <<'EOF'
name: Coveralls

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  coverage:
    runs-on: ubuntu-latest

    steps:
    - uses: actions/checkout@v4
      with:
        submodules: recursive

    - name: Install dependencies
      run: |
        sudo apt update
        sudo apt install -y cmake g++ lcov

    - name: Configure with coverage
      run: |
        cd banking
        cmake -H. -B_build -DBUILD_TESTS=ON -DCMAKE_CXX_FLAGS="--coverage"
        cd ..

    - name: Build and run tests
      run: |
        cd banking
        cmake --build _build
        cd _build
        ./banking_check
        cd ../..

    - name: Collect coverage
      run: |
        cd banking
        lcov --capture --directory . --output-file coverage.info
        lcov --remove coverage.info '/usr/*' '*/third-party/*' '*/_build/*' --output-file coverage.info
        cd ..

    - name: Upload to Coveralls
      uses: coverallsapp/github-action@v2
      with:
        file: banking/coverage.info
EOF
```

## 8. Обновление .gitignore

```bash
cat > .gitignore <<'EOF'
`# Build directories
_build/
banking/_build/
build/
*_build/

`# Object files
*.o
*.a
*.so
*.exe

`# IDE files
.vscode/
.idea/
*.swp
*.swo

`# OS files
.DS_Store
Thumbs.db
EOF
```

## 9. Обновление README.md

```bash
sed -i 's/lab04/lab05/g' README.md
```

## 10. Финальный коммит и push

```bash
git add .
```

```bash
git commit -m "lab05 completed: GTest, banking library with 14 tests, mock objects, GitHub Actions CI, Coveralls.io"
```

```bash
git push origin main

output:

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 30, done.
Counting objects: 100% (30/30), done.
Delta compression using up to 2 threads
Compressing objects: 100% (20/20), done.
Writing objects: 100% (26/26), 15.23 KiB | 2.18 MiB/s, done.
Total 26 (delta 3), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (3/3), completed with 2 local objects.
To https://github.com/PavelDats1/lab04.git
   172b2b8..9599703  main -> main

```
