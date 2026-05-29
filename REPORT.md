# Laboratory work 6: CPack

## Author
Павел Дацковских 
GitHub: PavelDats1

---

## Tutorial

### 1. 

```bash
$ cp -rf /home/pavel/workspace/PavelDats1/projects/lab05/. .
$ ls -la
```
```bash
total 152
drwxrwxr-x 10 pavel pavel  4096 May 29 14:36 .
drwxrwxr-x 10 pavel pavel  4096 May 29 13:44 ..
-rw-rw-r--  1 pavel pavel   212 May 29 14:36 .appveyor.yml
drwxrwxr-x  6 pavel pavel  4096 May 29 14:19 banking
drwxrwxr-x  8 pavel pavel  4096 May 29 14:36 _build
-rw-rw-r--  1 pavel pavel   700 May 29 14:36 CMakeLists.txt
-rw-rw-r--  1 pavel pavel   757 May 29 14:36 CMakeLists.txt.tutorial
-rw-rw-r--  1 pavel pavel     5 May 29 14:36 file.txt
drwxrwxr-x  9 pavel pavel  4096 May 29 14:19 .git
drwxrwxr-x  3 pavel pavel  4096 May 29 14:19 .github
-rw-rw-r--  1 pavel pavel   168 May 29 14:36 .gitignore
drwxrwxr-x  2 pavel pavel  4096 May 29 14:19 include
-rw-rw-r--  1 pavel pavel  1067 May 29 14:36 LICENSE
-rw-rw-r--  1 pavel pavel   308 May 29 14:36 README.md
-rw-rw-r--  1 pavel pavel 21004 May 29 14:36 REPORT_LAB02.md
-rw-rw-r--  1 pavel pavel 20900 May 29 14:36 REPORT_LAB03.md
-rw-rw-r--  1 pavel pavel 27389 May 29 14:36 REPORT.md
-rw-rw-r--  1 pavel pavel  1024 May 29 14:32 .REPORT.md.swp
drwxrwxr-x  2 pavel pavel  4096 May 29 14:19 sources
drwxrwxr-x  3 pavel pavel  4096 May 29 14:19 tests
drwxrwxr-x  2 pavel pavel  4096 May 29 14:19 third-party
-rw-rw-r--  1 pavel pavel   139 May 29 14:36 .travis.yml
```

### 3. Добавление версионирования в CMakeLists.txt
```bash
$ grep -E "PRINT_VERSION" CMakeLists.txt
```
### 4. Создание DESCRIPTION и ChangeLog.md
```bash
echo "static C++ library for printing" > DESCRIPTION
$ cat DESCRIPTION
```
```bash
output:
static C++ library for printing
```
### 5. Создание CPackConfig.cmake
```bash
$ head -20 CPackConfig.cmake
```

```bash
output:
include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_CONTACT "pavel@example.com")
set(CPACK_PACKAGE_VERSION_MAJOR 0)
set(CPACK_PACKAGE_VERSION_MINOR 1)
set(CPACK_PACKAGE_VERSION_PATCH 0)
set(CPACK_PACKAGE_VERSION_TWEAK 0)
set(CPACK_PACKAGE_VERSION "0.1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/DESCRIPTION")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "static C++ library for printing")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

set(CPACK_RPM_PACKAGE_NAME "print-devel")
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "print")
set(CPACK_RPM_CHANGELOG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ChangeLog.md")
set(CPACK_RPM_PACKAGE_RELEASE 1)

set(CPACK_DEBIAN_PACKAGE_NAME "libprint-dev")

```
### 6. Подключение CPackConfig.cmake в CMakeLists.txt
```bash
cat > CPackConfig.cmake << 'EOF'
tail -3 CMakeLists.txt
```
```bash
output:
add_test(NAME BankingTests COMMAND tests)
```
### 7. Очистка и сборка
```bash
$ rm -rf _build
$ cmake -H. -B_build
```
```bash
output:
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
-- Configuring done (1.0s)
-- Generating done (0.0s)
-- Build files have been written to: /home/pavel/PavelDats1/workspace/lab06/_build

```
```bash
cmake --build _build
```
```bash
[100%] Built target solver
```

### 8. Создание пакетов через CPack
```bash
$ cd _build
$ cpack -G "TGZ"
```

```bash
output:
CPack: Create package using TGZ
CPack: Install projects
CPack: - Run preinstall target for: solver
CPack: - Install project: solver []
CPack: Create package
CPack: - package: /home/pavel/PavelDats1/workspace/lab06/_build/solver-0.1.0.0-Linux.tar.gz generated.

```
```bash
$ cpack -G "DEB"
```
```bash
output:
CPack: Create package using DEB
CPack: Install projects
CPack: - Run preinstall target for: solver
CPack: - Install project: solver []
CPack: Create package
-- CPACK_DEBIAN_PACKAGE_DEPENDS not set, the package will have no dependencies.
CPack: - package: /home/pavel/PavelDats1/workspace/lab06/_build/solver-0.1.0.0-Linux.deb generated.

```
```bash
cpack -G "RPM"
```
```bash
output:
CPack: Create package using RPM
CPack: Install projects
CPack: - Run preinstall target for: solver
CPack: - Install project: solver []
CPack: Create package
CPackRPM: Will use GENERATED spec file: /home/pavel/PavelDats1/workspace/lab06/_build/_CPack_Packages/Linux/RPM/SPECS/solver.spec
CPack: - package: /home/pavel/PavelDats1/workspace/lab06/_build/solver-0.1.0.0-Linux.rpm generated.
```
### 9. Сбор артефактов
```bash
$ mkdir -p artifacts
$ mv _build/*.tar.gz _build/*.deb artifacts/ 2>/dev/null
$ tree artifacts
```
```bash
output:
artifacts
├── solver-0.1.0.0-Linux.deb
└── solver-0.1.0.0-Linux.tar.gz

1 directory, 2 files

```
### 10. Отправка на GitHub
```bash
$ git add .
$ git commit -m "Add CPack configuration and packages"
```
```bash
output:
[main 1a9c20f] Add CPack configuration and packages
 6 files changed, 60 insertions(+), 22 deletions(-)
 create mode 100644 CPackConfig.cmake
 create mode 100644 DESCRIPTION
 create mode 100644 artifacts/solver-0.1.0.0-Linux.deb
 create mode 100644 artifacts/solver-0.1.0.0-Linux.tar.gz
 create mode 100644 solver.cpp
```
```bash
$ git push origin main
```
```bash
output:

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 11, done.
Counting objects: 100% (11/11), done.
Delta compression using up to 2 threads
Compressing objects: 100% (8/8), done.
Writing objects: 100% (9/9), 7.24 KiB | 1.21 MiB/s, done.
Total 9 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 1 local object.
To https://github.com/PavelDats1/lab05.git
   2d9a1d6..1a9c20f  main -> main
```
### 11. Создание тега для релиза
```bash
$ git tag -a v0.1.0.0 -m "First CPack release"
$ git push origin v0.1.0.0
```

```bash
output:
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 1, done.
Counting objects: 100% (1/1), done.
Writing objects: 100% (1/1), 173 bytes | 173.00 KiB/s, done.
Total 1 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/PavelDats1/lab05.git
 * [new tag]         v0.1.0.0 -> v0.1.0.0

```
