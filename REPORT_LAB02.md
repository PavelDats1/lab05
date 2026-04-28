# Отчет по лабораторной работе №2
## Системы контроля версий на примере Git

**Студент:** Дацковских Павел
**Дата выполнения:** 01.04.2026

---
## 1. Tuturial

### 1.1 Создание  README.md
```bash
cat > README.md << 'EOF'
> # Lab02
> ## Git Version Control System
> This repository contains laboratory work #2 on Git.
> EOF

cat README.md
pavel@pavel:~/workspace/projects/lab02$ cat README.md
# Lab02
## Git Version Control System
This repository contains laboratory work #2 on Git.
```
### 1.2 Первый коммит
```bash
git add README.md
git status
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
	new file:   README.md
git commit -m "initial commit"
[main (root-commit) e59fb8b] initial commit
 1 file changed, 3 insertions(+)
 create mode 100644 README.md
```
### 1.3 Отправка на Github
```bash
git push -u origin main
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 6, done.
Counting objects: 100% (6/6), done.
Delta compression using up to 2 threads
Compressing objects: 100% (4/4), done.
Writing objects: 100% (5/5), 595 bytes | 198.00 KiB/s, done.
Total 5 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/PavelDats1/lab02.git
   476216f..f23be2d  main -> main
```
### 1.4 Создание .gitignore
```bash
cat > .gitignore << 'EOF'
*build*/
*install*/
*.swp
.idea/
EOF

cat .gitignore
git add .gitignore
git commit -m "Add .gitignore"
git push origin main

#Output:
cat .gitignore
*build*/
*install*/
*.swp
.idea/

git commit -m "Add .gitignore"
[main d337ead] Add .gitignore
 1 file changed, 4 insertions(+)
 create mode 100644 .gitignore

git push origin main
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 2 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 342 bytes | 342.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/PavelDats1/lab02.git
   f23be2d..d337ead  main -> main
```
### 1.5 Создание структуры папок
```bash
mkdir sources include examples
ls -la

#Output:
total 40
drwxrwxr-x 6 pavel pavel 4096 Apr  1 14:52 .
drwxrwxr-x 3 pavel pavel 4096 Apr  1 12:06 ..
drwxrwxr-x 2 pavel pavel 4096 Apr  1 14:52 examples
drwxrwxr-x 8 pavel pavel 4096 Apr  1 14:48 .git
-rw-rw-r-- 1 pavel pavel   33 Apr  1 14:47 .gitignore
drwxrwxr-x 2 pavel pavel 4096 Apr  1 14:52 include
-rw-rw-r-- 1 pavel pavel 1067 Apr  1 14:18 LICENSE
-rw-rw-r-- 1 pavel pavel   90 Apr  1 12:29 README.md
-rw-rw-r-- 1 pavel pavel    0 Apr  1 14:21 REPORT.md
-rw-rw-r-- 1 pavel pavel 1024 Apr  1 14:22 .REPORT.md.swp
drwxrwxr-x 2 pavel pavel 4096 Apr  1 14:52 sources
```
### 1.6 Cоздание файлов исходного кода
```bash
cat > include/print.hpp << 'EOF'
#include <fstream>
#include <iostream>
#include <string>

void print(const std::string& text, std::ofstream& out);
void print(const std::string& text, std::ostream& out = std::cout);
EOF

cat > sources/print.cpp << 'EOF'
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

cat > examples/example1.cpp << 'EOF'
#include <print.hpp>

int main(int argc, char** argv)
{
  print("hello");
}
EOF

cat > examples/example2.cpp << 'EOF'
#include <print.hpp>

#include <fstream>

int main(int argc, char** argv)
{
  std::ofstream file("log.txt");
  print(std::string("hello"), file);
}
EOF
#Output:
cat include/print.hpp
#include <fstream>
#include <iostream>
#include <string>
void print(const std::string& text, std::ofstream& out);
void print(const std::string& text, std::ostream& out = std::cout);

cat sources/print.cpp
#include <print.hpp>
void print(const std::string& text, std::ostream& out)
{
  out << text;
}
void print(const std::string& text, std::ofstream& out)
{
  out << text;
}

cat examples/example1.cpp
#include <print.hpp>
int main(int argc, char** argv)
{
  print("hello");
}

cat examples/example2.cpp
#include <print.hpp>
#include <fstream>
int main(int argc, char** argv)
{
  std::ofstream file("log.txt");
  print(std::string("hello"), file);
}
```
### 1.6 Kоммит "added sources"
```bash
git add .
git status
#Output:
On branch main
Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
	new file:   REPORT.md
	new file:   examples/example1.cpp
	new file:   examples/example2.cpp
	new file:   include/print.hpp
	new file:   sources/print.cpp
git commit -m "added sources"
#Output:
[main e86dccc] added sources
 5 files changed, 26 insertions(+)
 create mode 100644 REPORT.md
 create mode 100644 examples/example1.cpp
 create mode 100644 examples/example2.cpp
 create mode 100644 include/print.hpp
 create mode 100644 sources/print.cpp
git push origin main
#Output: 
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 11, done.
Counting objects: 100% (11/11), done.
Delta compression using up to 2 threads
Compressing objects: 100% (7/7), done.
Writing objects: 100% (10/10), 1000 bytes | 1000.00 KiB/s, done.
Total 10 (delta 0), reused 0 (delta 0), pack-reused 0
To https://github.com/PavelDats1/lab02.git
   d337ead..e86dccc  main -> main
```
### 1.7 Обновление README.md
```bash
cat > README.md << 'EOF'
# Lab02
## Git Version Control System

This repository contains laboratory work #2 on Git.

## Project Structure
- **include/** - Header files
  - print.hpp - Function declarations for printing
- **sources/** - Source files
  - print.cpp - Function implementations for printing
- **examples/** - Example programs
  - example1.cpp - Prints to console
  - example2.cpp - Prints to file

## Description
The project implements simple printing functions that can output text
to either console (std::cout) or file (std::ofstream).

## Author
Pavel Dats
EOF

cat README.md
git add README.md
git commit -m "Update README.md with project structure"
git push origin main
#Output:
[main c992097] Update README.md with project structure
 1 file changed, 17 insertions(+)

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 582 bytes | 582.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/PavelDats1/lab02.git
   e86dccc..c992097  main -> main
```
## 2. Homework Part 1

### 2.1 Создаем hello_world.cpp с плохим стилем
```bash
cat > hello_world.cpp << 'EOF'
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello, World!" << endl;
    return 0;
}
EOF

cat hello_world.cpp
git add hello_world.cpp
git commit -m "Add hello world program with bad style"
git push origin main
#Output:
[main 46245a5] Add hello world program with bad style
 1 file changed, 8 insertions(+)
 create mode 100644 hello_world.cpp

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 401 bytes | 401.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/PavelDats1/lab02.git
   c992097..46245a5  main -> main
```
### 2.2 Добавляем ввод имени
```bash
cat > hello_world.cpp << 'EOF'
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "Hello world from " << name << endl;
    return 0;
}
EOF

cat hello_world.cpp
git commit -am "Add user input to hello world program"
git push origin main
#Output:
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string name;
    cout << "Enter your name: ";
   cin >> name;
    cout << "Hello world from " << name << endl;
    return 0;
}

[main 52d5c38] Add user input to hello world program
 1 file changed, 5 insertions(+), 1 deletion(-)

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 410 bytes | 410.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/PavelDats1/lab02.git
   46245a5..52d5c38  main -> main
```
## Homework Part 2

### 3.1 Создаем ветку patch1
```bash
git checkout -b patch1
git branch
#Output:
Switched to a new branch 'patch1'

  main
* patch1
```
### 3.2 Убираем using namespace std
```bash
cat > hello_world.cpp << 'EOF'
#include <iostream>
#include <string>

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}
EOF

cat hello_world.cpp
git commit -am "Remove using namespace std"
#Output:
#include <iostream>
#include <string>
int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}

[patch1 3b1cec4] Remove using namespace std
 1 file changed, 4 insertions(+), 6 deletions(-)
```
### 3.3 Отправляем ветку patch1 на GitHub
```bash
git push origin patch1
#Output:
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 399 bytes | 399.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
remote: 
remote: Create a pull request for 'patch1' on GitHub by visiting:
remote:      https://github.com/PavelDats1/lab02/pull/new/patch1
remote: 
To https://github.com/PavelDats1/lab02.git
 * [new branch]      patch1 -> patch1
```
### 3.4 Добавляем комментарии в hello_world.cpp
```bash
cat > hello_world.cpp << 'EOF'
#include <iostream>
#include <string>

int main()
{
    // Variable to store user's name
    std::string name;
    
    // Prompt user for input
    std::cout << "Enter your name: ";
    std::cin >> name;
    
    // Display greeting
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}
EOF

cat hello_world.cpp
git commit -am "Add comments to code"
git push origin patch1
#Output:
#include <iostream>
#include <string>
int main()
{
    // Variable to store user's name
    std::string name;
    // Prompt user for input
    std::cout << "Enter your name: ";
    std::cin >> name;

    // Display greeting
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}

[patch1 3230ca9] Add comments to code
 1 file changed, 4 insertions(+)

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 446 bytes | 446.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/PavelDats1/lab02.git
   3b1cec4..3230ca9  patch1 -> patch1
```
### 3.5 Создаем Pull Request на GitHub и удаляем ветку
```bash
git checkout main
git pull origin main
git branch -d patch1
git branch
#Output:
Switched to branch 'main'

remote: Enumerating objects: 1, done.
remote: Counting objects: 100% (1/1), done.
remote: Total 1 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (1/1), 881 bytes | 293.00 KiB/s, done.
From https://github.com/PavelDats1/lab02
 * branch            main       -> FETCH_HEAD
   52d5c38..f2f61bb  main       -> origin/main
Updating 52d5c38..f2f61bb
Fast-forward
 hello_world.cpp | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

Deleted branch patch1 (was 3230ca9).

* main
```
## Homework Part 3

### 4.1 Создаем ветку patch2
```bash
git checkout -b patch2
git branch
#Output:
Switched to a new branch 'patch2'

  main
* patch2
```
### 4.2  Устанавливаем clang-format
```bash
sudo apt install clang-format -y
clang-format --version
#Output: 
Reading package lists... Done
Building dependency tree... Done
Reading state information... Done
The following additional packages will be installed:
  clang-format-18
The following NEW packages will be installed:
  clang-format clang-format-18
0 upgraded, 2 newly installed, 0 to remove and 48 not upgraded.
Need to get 59.7 kB of archives.
After this operation, 269 kB of additional disk space will be used.
Get:1 http://ru.archive.ubuntu.com/ubuntu noble-updates/universe amd64 clang-format-18 amd64 1:18.1.3-1ubuntu1 [53.8 kB]
Get:2 http://ru.archive.ubuntu.com/ubuntu noble/universe amd64 clang-format amd64 1:18.0-59~exp2 [5970 B]
Fetched 59.7 kB in 0s (320 kB/s)
Selecting previously unselected package clang-format-18.
(Reading database ... 211556 files and directories currently installed.)
Preparing to unpack .../clang-format-18_1%3a18.1.3-1ubuntu1_amd64.deb ...
Unpacking clang-format-18 (1:18.1.3-1ubuntu1) ...
Selecting previously unselected package clang-format:amd64.
Preparing to unpack .../clang-format_1%3a18.0-59~exp2_amd64.deb ...
Unpacking clang-format:amd64 (1:18.0-59~exp2) ...
Setting up clang-format-18 (1:18.1.3-1ubuntu1) ...
Setting up clang-format:amd64 (1:18.0-59~exp2) ...
Processing triggers for man-db (2.12.0-4build2) ...

Ubuntu clang-format version 18.1.3 (1ubuntu1)
```
### 4.3 Форматируем код в стиле Mozilla
```bash
clang-format -style=Mozilla -i hello_world.cpp
cat hello_world.cpp
#Output:
#include <iostream>
#include <string>
int
main()
{
  // Variable to store user's name
  std::string name;
  // Prompt user for input
  std::cout << "Enter your name: ";
  std::cin >> name;

  // Display greeting
  std::cout << "Hello world from " << name << std::endl;
  return 0;
}
```
### 4.4 Patch2 
```bash
git commit -am "Apply Mozilla code style"
git push origin patch2
#Output:
[patch2 23602ca] Apply Mozilla code style
 1 file changed, 10 insertions(+), 9 deletions(-)

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 388 bytes | 388.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
remote: 
remote: Create a pull request for 'patch2' on GitHub by visiting:
remote:      https://github.com/PavelDats1/lab02/pull/new/patch2
remote: 
To https://github.com/PavelDats1/lab02.git
 * [new branch]      patch2 -> patch2
```
### 4.5 Создаем конфликт в ветке
```bash
git checkout main
cat > hello_world.cpp << 'EOF'
#include <iostream>
#include <string>

int main()
{
    // Переменная для хранения имени пользователя
    std::string name;
    
    // Запрос имени у пользователя
    std::cout << "Enter your name: ";
    std::cin >> name;
    
    // Вывод приветствия
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}
EOF

cat hello_world.cpp
git commit -am "Translate comments to Russian"
git push origin main
#Output:
#include <iostream>

#include <string>
int main()
{

    // Переменная для хранения имени пользователя

    std::string name;

    // Запрос имени у пользователя

    std::cout << "Enter your name: ";

    std::cin >> name;

    // Вывод приветствия

    std::cout << "Hello world from " << name << std::endl;
     return 0;
}

[main 15209bb] Translate comments to Russian
 1 file changed, 11 insertions(+), 4 deletions(-)

Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 514 bytes | 257.00 KiB/s, done.
Total 3 (delta 1), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/PavelDats1/lab02.git
   f2f61bb..15209bb  main -> main
```
### 4.6 Переключаемся на patch2 и делаем rebase
```bash
git checkout patch2
git pull --rebase origin main
#Output:
Switched to branch 'patch2'

From https://github.com/PavelDats1/lab02
 * branch            main       -> FETCH_HEAD
Auto-merging hello_world.cpp
CONFLICT (content): Merge conflict in hello_world.cpp
error: could not apply 23602ca... Apply Mozilla code style
hint: Resolve all conflicts manually, mark them as resolved with
hint: "git add/rm <conflicted_files>", then run "git rebase --continue".
hint: You can instead skip this commit: run "git rebase --skip".
hint: To abort and get back to the state before "git rebase", run "git rebase --abort".
Could not apply 23602ca... Apply Mozilla code style
```
### 4.7 Разрешаем конфликт
```bash
cat > hello_world.cpp << 'EOF'
#include <iostream>
#include <string>

int
main()
{
    // Переменная для хранения имени пользователя
    std::string name;

    // Запрос имени у пользователя
    std::cout << "Enter your name: ";
    std::cin >> name;

    // Вывод приветствия
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}
EOF

cat hello_world.cpp
git add hello_world.cpp
git rebase --continue
#Output:
#include <iostream>
#include <string>
int main()
{
    // Переменная для хранения имени пользователя
    std::string name;

    // Запрос имени у пользователя
    std::cout << "Enter your name: ";
    std::cin >> name;

    // Вывод приветствия
    std::cout << "Hello world from " << name << std::endl;
    return 0;
}

[detached HEAD c15820b] Apply Mozilla code style
 1 file changed, 1 insertion(+), 7 deletions(-)
Successfully rebased and updated refs/heads/patch2.
```
### 4.8 Force push 
```bash
git push --force origin patch2
#Output:
Username for 'https://github.com': PavelDats1
Password for 'https://PavelDats1@github.com': 
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 2 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 339 bytes | 339.00 KiB/s, done.
Total 3 (delta 2), reused 0 (delta 0), pack-reused 0
remote: Resolving deltas: 100% (2/2), completed with 2 local objects.
To https://github.com/PavelDats1/lab02.git
 + 23602ca...c15820b patch2 -> patch2 (forced update)
```
### 4.9 Создаем Pull Request и вмерживаем
```bash
git checkout main
git pull origin main
git branch -d patch2
git branch
git log --oneline
#Output:
remote: Enumerating objects: 1, done.
remote: Counting objects: 100% (1/1), done.
remote: Total 1 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Unpacking objects: 100% (1/1), 898 bytes | 898.00 KiB/s, done.
From https://github.com/PavelDats1/lab02
 * branch            main       -> FETCH_HEAD
   15209bb..9ae0b7c  main       -> origin/main
Updating 15209bb..9ae0b7c
Fast-forward
 hello_world.cpp | 8 +-------
 1 file changed, 1 insertion(+), 7 deletions(-)

Deleted branch patch2 (was c15820b).

* main

9ae0b7c (HEAD -> main, origin/main) Merge pull request #2 from PavelDats1/patch2
c15820b (origin/patch2) Apply Mozilla code style
15209bb Translate comments to Russian
f2f61bb Merge pull request #1 from PavelDats1/patch1
3230ca9 (origin/patch1) Add comments to code
3b1cec4 Remove using namespace std
52d5c38 Add user input to hello world program
46245a5 Add hello world program with bad style
c992097 Update README.md with project structure
e86dccc added sources
d337ead Add .gitignore
f23be2d Merge branch 'main' of https://github.com/PavelDats1/lab02
e59fb8b initial commit
476216f Initial commit
```

