# Отчет по лабораторной работе №3

## Системы автоматизации сборки проекта на примере CMake

**Студент:** Павел Дацковских
**Дата выполнения:** 28.04.2026



## 1. Подготовка и настройка

### 1.1 Клонирование репозитория из lab02
```bash
git clone https://github.com/PavelDats1/lab02.git projects/lab03
Output:
Cloning into 'projects/lab03'...
remote: Enumerating objects: 50, done.
remote: Counting objects: 100% (50/50), done.
remote: Compressing objects: 100% (39/39), done.
remote: Total 50 (delta 15), reused 35 (delta 5), pack-reused 0 (from 0)
Receiving objects: 100% (50/50), 13.07 KiB | 1.87 MiB/s, done.
Resolving deltas: 100% (15/15), done.
```
### 1.2 Смена удаленного репозитория
```bash
cd projects/lab03
git remote remove origin
git remote add origin https://github.com/PavelDats1/lab03.git
git remote -v
Output:
origin	https://github.com/PavelDats1/lab03.git (fetch)
origin	https://github.com/PavelDats1/lab03.git (push)
```
### 1.3 Отправка в новый репозиторий
```bash
git push -u origin main
Output:
Enumerating objects: 50, done.
Counting objects: 100% (50/50), done.
Delta compression using up to 2 threads
Compressing objects: 100% (29/29), done.
Writing objects: 100% (50/50), 13.07 KiB | 13.07 MiB/s, done.
Total 50 (delta 15), reused 50 (delta 15), pack-reused 0
remote: Resolving deltas: 100% (15/15), done.
To https://github.com/PavelDats1/lab03.git
 * [new branch]      main -> main
branch 'main' set up to track 'origin/main'.
```

## 2. Tutorial

### 2.1 Компиляция библиотеки print
```bash
g++ -std=c++11 -I./include -c sources/print.cpp
ls print.o
Output:
print.o

nm print.o | grep print
Output:
0000000000000000 T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSo
000000000000002a T _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E

ar rvs print.a print.o
Output:
ar: creating print.a
a - print.o

file print.a
Output:
print.a: current ar archive
```
### 2.2 Компиляция примера 1
```bash
g++ -std=c++11 -I./include -c examples/example1.cpp
ls example1.o
Output:
example1.o

g++ example1.o print.a -o example1
./example1 && echo
Output:
hello
```
### 2.3 Компиляция примера 2
```bash
g++ -std=c++11 -I./include -c examples/example2.cpp
ls example2.o
nm example2.o
Output:
pavel@pavel:~/workspace/PavelDats1/projects/lab03$ nm example2.o
0000000000000000 V DW.ref.__gxx_personality_v0
                 U __gxx_personality_v0
0000000000000000 T main
                 U __stack_chk_fail
                 U _Unwind_Resume
                 U _Z5printRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERSt14basic_ofstreamIcS2_E
                 U _ZNSt14basic_ofstreamIcSt11char_traitsIcEEC1EPKcSt13_Ios_Openmode
                 U _ZNSt14basic_ofstreamIcSt11char_traitsIcEED1Ev
0000000000000000 W _ZNSt15__new_allocatorIcED1Ev
0000000000000000 W _ZNSt15__new_allocatorIcED2Ev
0000000000000000 n _ZNSt15__new_allocatorIcED5Ev
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EPKcRKS3_
                 U _ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev
                 U _ZSt21ios_base_library_initv
0000000000000000 r _ZStL19piecewise_construct

g++ example2.o print.a -o example2
./example2
cat log.txt && echo
Output:
hello

### 2.4 Очистка временных файлов
```bash
rm -rf example1.o example2.o print.o
rm -rf print.a
rm -rf example1 example2
rm -rf log.txt
ls -la
Output:
total 76
drwxrwxr-x 7 pavel pavel  4096 Apr 28 14:50 .
drwxrwxr-x 3 pavel pavel  4096 Apr 28 13:45 ..
-rw-rw-r-- 1 pavel pavel   490 Apr 28 13:54 CMakeLists.txt
drwxrwxr-x 2 pavel pavel  4096 Apr 28 13:45 examples
drwxrwxr-x 8 pavel pavel  4096 Apr 28 14:38 .git
-rw-rw-r-- 1 pavel pavel    33 Apr 28 13:45 .gitignore
-rw-rw-r-- 1 pavel pavel   398 Apr 28 13:45 hello_world.cpp
drwxrwxr-x 2 pavel pavel  4096 Apr 28 13:45 include
-rw-rw-r-- 1 pavel pavel  1067 Apr 28 13:45 LICENSE
drwxrwxr-x 3 pavel pavel  4096 Apr 28 14:13 projects
-rw-rw-r-- 1 pavel pavel   547 Apr 28 13:45 README.md
-rw-rw-r-- 1 pavel pavel     0 Apr 28 14:10 REPORT_LAB03.md
-rw-rw-r-- 1 pavel pavel  1024 Apr 28 14:11 .REPORT_LAB03.md.swp
-rw-rw-r-- 1 pavel pavel 21004 Apr 28 14:09 REPORT.md
drwxrwxr-x 2 pavel pavel  4096 Apr 28 13:45 sources
```
## 3. Создание CMakeLists.txt
### 3.1 Установка
```bash
sudo apt update
sudo apt install cmake -y
Output:
Get:1 file:/cdrom noble InRelease
Ign:1 file:/cdrom noble InRelease
Get:2 file:/cdrom noble Release
Err:2 file:/cdrom noble Release
  File not found - /cdrom/dists/noble/Release (2: No such file or directory)
Hit:3 http://ru.archive.ubuntu.com/ubuntu noble InRelease
Get:4 http://ru.archive.ubuntu.com/ubuntu noble-updates InRelease [126 kB]
Hit:5 http://ru.archive.ubuntu.com/ubuntu noble-backports InRelease            
Get:6 http://security.ubuntu.com/ubuntu noble-security InRelease [126 kB]  
Get:7 http://ru.archive.ubuntu.com/ubuntu noble-updates/main amd64 Packages [1919 kB]
Get:8 http://ru.archive.ubuntu.com/ubuntu noble-updates/universe amd64 Packages [1685 kB]
Get:9 http://security.ubuntu.com/ubuntu noble-security/universe amd64 c-n-f Metadata [23.1 kB]
Reading package lists... Done                                   
E: The repository 'file:/cdrom noble Release' no longer has a Release file.
N: Updating from such a repository can't be done securely, and is therefore disabled by default.
N: See apt-secure(8) manpage for repository creation and user configuration details.

```
### 3.2 Проверка установки
```bash
cmake --version
Output:
cmake version 3.28.3

CMake suite maintained and supported by Kitware (kitware.com/cmake).
```
### Создание базового CMakeLists.txt
```bash
cat > CMakeLists.txt <<'EOF'
cmake_minimum_required(VERSION 3.4)
project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(print STATIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
EOF
```
### 3.4 Первая сборка с CMake
```bash
cmake -H. -B_build
Output:
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


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
-- Configuring done (0.8s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/workspace/PavelDats1/projects/lab03/_build

cmake --build _build
Output:
[ 50%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[100%] Linking CXX static library libprint.a
[100%] Built target print
```
### 3.5 Добавление исполняемых файлов в CMakeLists.txt
```bash
cat >> CMakeLists.txt <<'EOF'

add_executable(example1 ${CMAKE_CURRENT_SOURCE_DIR}/examples/example1.cpp)
add_executable(example2 ${CMAKE_CURRENT_SOURCE_DIR}/examples/example2.cpp)

target_link_libraries(example1 print)
target_link_libraries(example2 print)
EOF
```
### 3.6 Полная сборка
```bash
cmake --build _build
Output:
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/workspace/PavelDats1/projects/lab03/_build
[ 33%] Built target print
[ 50%] Building CXX object CMakeFiles/example1.dir/examples/example1.cpp.o
[ 66%] Linking CXX executable example1
[ 66%] Built target example1
[ 83%] Building CXX object CMakeFiles/example2.dir/examples/example2.cpp.o
[100%] Linking CXX executable example2
[100%] Built target example2
```
### 3.7 Проверка созданных файлов
```bash
ls -la _build/libprint.a
Output:
-rw-rw-r-- 1 pavel pavel 2246 Apr 28 15:15 _build/libprint.a
./_build/example1 && echo
Output:
hello
./_build/example2
cat log.txt && echo
Output:
hello
```
### 3.8 Установка библиотеки с префиксом
```bash
cmake -H. -B_build -DCMAKE_INSTALL_PREFIX=_install
Output:
CMake Deprecation Warning at CMakeLists.txt:1 (cmake_minimum_required):
  Compatibility with CMake < 3.5 will be removed from a future version of
  CMake.

  Update the VERSION argument <min> value or use a ...<max> suffix to tell
  CMake that the project does not need compatibility with older versions.


-- Configuring done (0.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/workspace/PavelDats1/projects/lab03/_build

cmake --build _build --target install
Output:
[ 33%] Built target print
[ 66%] Built target example1
[100%] Built target example2
Install the project...
-- Install configuration: ""
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_install/lib/libprint.a
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_install/include
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_install/include/print.hpp
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_install/bin/example1
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_install/bin/example2

```
### 3.9 Установка tree и просмотр структуры
```bash
sudo apt install tree -y
Output:
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following NEW packages will be installed:
  tree
0 upgraded, 1 newly installed, 0 to remove and 116 not upgraded.
Need to get 47.4 kB of archives.
After this operation, 111 kB of additional disk space will be used.
Get:1 http://ru.archive.ubuntu.com/ubuntu noble-updates/universe amd64 tree amd64 2.1.1-2ubuntu3.24.04.2 [47.4 kB]
Fetched 47.4 kB in 0s (518 kB/s)
Selecting previously unselected package tree.
(Reading database ... 247248 files and directories currently installed.)
Preparing to unpack .../tree_2.1.1-2ubuntu3.24.04.2_amd64.deb ...
Unpacking tree (2.1.1-2ubuntu3.24.04.2) ...
Setting up tree (2.1.1-2ubuntu3.24.04.2) ...
Processing triggers for man-db (2.12.0-4build2) ...

tree _install
Output:
_install
├── bin
│   ├── example1
│   └── example2
├── include
│   └── print.hpp
└── lib
    └── libprint.a

4 directories, 4 files

```
### 3.10 Сохранение CMakeLists.txt в Git
```bash
git add CMakeLists.txt
git status
Output:
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	new file:   CMakeLists.txt

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
	modified:   examples/example1.cpp
	modified:   examples/example2.cpp

Untracked files:
  (use "git add <file>..." to include in what will be committed)
	REPORT_LAB03.md
	example2
	example2.o
	log.txt
	print.a
	print.o
	projects/

git commit -m "added CMakeLists.txt"
Output:
[main d8f2ec2] added CMakeLists.txt
 1 file changed, 22 insertions(+)
 create mode 100644 CMakeLists.txt

git push -u origin main
Output:
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 614 bytes | 614.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/PavelDats1/lab03.git
   3a63a8c..d8f2ec2  main -> main
branch 'main' set up to track 'origin/main'.
```
## 4. Домашнее задание

### 4.1 Создание библиотеки formatter_lib
```bash
mkdir -p formatter_lib
cd formatter_lib
cat > formatter.h << 'EOF'
```#pragma once
```#include <string>
std::string formatter(const std::string& message);
EOF

cat > formatter.cpp << 'EOF'
```#include "formatter.h"
std::string formatter(const std::string& message)
{
    std::string res;
    res += "-------------------------\n";
    res += message + "\n";
    res += "-------------------------\n";
    return res;
}
EOF

cat > CMakeLists.txt << 'EOF'
> cmake_minimum_required(VERSION 3.4)
> project(formatter)
> set(CMAKE_CXX_STANDARD 11)
> set(CMAKE_CXX_STANDARD_REQUIRED ON)
> add_library(formatter STATIC formatter.cpp)
> EOF

cd ..
```
### 4.2 Создание библиотеки formatter_ex_lib
```bash
mkdir -p formatter_ex_lib
cd formatter_ex_lib

cat > formatter_ex.h << 'EOF'
> #pragma once
> #include <string>
> #include "../formatter_lib/formatter.h"
> std::string formatter_ex(const std::string& message);
> EOF

cat > formatter_ex.cpp << 'EOF'
> #include "formatter_ex.h"
> std::string formatter_ex(const std::string& message)
> {
>     return formatter(message);
> }
> EOF

cat > CMakeLists.txt << 'EOF'
> cmake_minimum_required(VERSION 3.10)
> project(formatter_ex)
> set(CMAKE_CXX_STANDARD 11)
> set(CMAKE_CXX_STANDARD_REQUIRED ON)
> add_library(formatter_ex STATIC formatter_ex.cpp)
> target_link_libraries(formatter_ex PUBLIC formatter)
> EOF
```

### 4.3 Создание приложения hello_world_application
```bash
mkdir -p hello_world_application
cd hello_world_application
cat > hello_world.cpp << 'EOF'
> #include <iostream>
> #include "../formatter_ex_lib/formatter_ex.h"
> int main()
> {
>     std::cout << formatter_ex("Hello, World!");
>     return 0;
> }
> EOF

cat > CMakeLists.txt << 'EOF'
> cmake_minimum_required(VERSION 3.10)
> project(hello_world)
> set(CMAKE_CXX_STANDARD 11)
> set(CMAKE_CXX_STANDARD_REQUIRED ON)
> add_executable(hello_world hello_world.cpp)
> target_include_directories(hello_world PRIVATE
>     ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib
>     ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib
> )
> target_link_libraries(hello_world PRIVATE formatter_ex formatter)
> install(TARGETS hello_world
>     RUNTIME DESTINATION bin
> )
> EOF
```
### 4.4 Создание библиотеки solver_lib
```bash
mkdir -p solver_lib
cd solver_lib
cat > solver.h << 'EOF'
> #pragma once
> class Solver
> {
> public:
>     double findRoot(double a, double b, double c, double eps,
>                     double x1 = -1000, double x2 = 1000);
> };
> EOF

cat solver.cpp
#include "solver.h"
#include <cmath>
#include <algorithm>

double Solver::findRoot(double a, double b, double c, double eps, 
                        double x1, double x2)
{
    if (x1 > x2) {
        std::swap(x1, x2);
    }

    while (std::abs(x2 - x1) > eps)
    {
        double mid = (x1 + x2) / 2;
        double f_mid = a * mid * mid + b * mid + c;
        double f_x1 = a * x1 * x1 + b * x1 + c;

        if (std::abs(f_mid) < eps)
        {
            return mid;
        }
        else if (f_x1 * f_mid < 0)
        {
            x2 = mid;
        }
        else
        {
            x1 = mid;
        }
    }

    return (x1 + x2) / 2;
}

cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.4)
project(solver_lib)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(solver_lib STATIC solver.cpp)
EOF

```
### 4.5 Создание приложения solver_application
```bash
mkdir -p solver_application
cd solver_application

cat > solver.cpp << 'EOF'
> #include <iostream>
> #include <string>
>#include "../formatter_ex_lib/formatter_ex.h"
>#include "../solver_lib/solver.h"

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        std::cerr << "Usage: solver <a> <b> <c> <eps> [x1] [x2]" << std::endl;
        return 1;
    }

    double a = std::stod(argv[1]);
    double b = std::stod(argv[2]);
    double c = std::stod(argv[3]);
    double eps = (argc >= 5) ? std::stod(argv[4]) : 1e-6;
    double x1 = (argc >= 6) ? std::stod(argv[5]) : -1000;
    double x2 = (argc >= 7) ? std::stod(argv[6]) : 1000;

    std::cout << "Searching root on interval [" << x1 << ", " << x2 << "]" << std::endl;

    Solver solver;
}   return 0; << formatter_ex("Root: " + std::to_string(root));

cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.10)
project(solver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver solver.cpp)

target_link_libraries(solver PRIVATE 
    formatter_ex formatter solver_lib)

install(TARGETS solver
    RUNTIME DESTINATION bin
```
### 4.6 Обновление корневого CMakeLists.txt
```bash
mv CMakeLists.txt CMakeLists.txt.tutorial

cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.10)
project(lab03)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
```
### 4.7 Обновление CMakeLists.txt для папки examples
```bash
cat > examples/CMakeLists.txt << 'EOF'
add_executable(example1 example1.cpp)
add_executable(example2 example2.cpp)

target_link_libraries(example1 PRIVATE formatter)
target_link_libraries(example2 PRIVATE formatter_ex formatter)

install(TARGETS example1 example2
    RUNTIME DESTINATION bin
)

```
### 4.8 Финальная чистая сборка всего проекта
```bash
rm -rf _build
mkdir _build
cd _build
cmake .. -DCMAKE_INSTALL_PREFIX=_install
Output:
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


-- Configuring done (1.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/workspace/PavelDats1/projects/lab03/_build

cmake --build . --target install
Output:
[ 10%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 20%] Linking CXX static library libformatter.a
[ 20%] Built target formatter
[ 30%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 40%] Linking CXX static library libformatter_ex.a
[ 40%] Built target formatter_ex
[ 50%] Building CXX object solver_lib/CMakeFiles/solver_lib.dir/solver.cpp.o
[ 60%] Linking CXX static library libsolver_lib.a
[ 60%] Built target solver_lib
[ 70%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 80%] Linking CXX executable hello_world
[ 80%] Built target hello_world
[ 90%] Building CXX object solver_application/CMakeFiles/solver.dir/solver.cpp.o
[100%] Linking CXX executable solver
[100%] Built target solver
Install the project...
-- Install configuration: ""
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_build/_install/bin/hello_world
-- Installing: /home/pavel/workspace/PavelDats1/projects/lab03/_build/_install/bin/solver
```
### 4.10 Проверка
```bash
./_install/bin/hello_world
Output:
Hello, World!

./_install/bin/solver 1 0 -4 0.001 -10 0
Output:
Root: -2.000122

./_install/bin/solver 1 0 -4 0.001 0 10
Output:
Root: 2.000122

```
