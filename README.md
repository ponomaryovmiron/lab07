# Мини-отчёт по лабораторной работе №5

## Цель работы

Цель работы — добавить в проект тестирование с помощью GoogleTest и настроить сборку тестов через CMake.

## Подготовка проекта

За основу был взят проект из прошлой лабораторной работы `lab04`. Он был склонирован в новую папку `lab05tut`, после чего был изменён удалённый репозиторий:

```bash
git clone https://github.com/ponomaryovmiron/lab04.git lab05tut
cd lab05tut
git remote remove origin
git remote add origin https://github.com/ponomaryovmiron/lab05tut.git
git branch -M main
```

Эти команды нужны, чтобы продолжить работу с прошлым проектом, но отправлять результат уже в новый репозиторий.

## Добавление GoogleTest

Для тестирования был добавлен фреймворк GoogleTest как submodule:

```bash
mkdir -p third-party
git submodule add https://github.com/google/googletest third-party/gtest
cd third-party/gtest
git checkout release-1.8.1
cd ../..
```

После этого в проекте появилась папка:

```text
third-party/gtest
```

В ней находятся исходные файлы GoogleTest.

## Добавление тестов

Была создана папка для тестов:

```bash
mkdir -p tests
```

В неё были добавлены тесты для библиотек проекта.

Файл `tests/test_formatter.cpp` проверяет работу `formatter` и `formatter_ex`:

```cpp
#include <formatter.hpp>
#include <formatter_ex.hpp>

#include <gtest/gtest.h>
#include <string>

TEST(Formatter, SimpleText)
{
    EXPECT_EQ(format("hello"), "hello");
}

TEST(FormatterEx, ContainsText)
{
    std::string result = format_ex("hello");

    EXPECT_NE(result.find("hello"), std::string::npos);
}
```

Файл `tests/test_solver.cpp` проверяет работу библиотеки `solver`:

```cpp
#include <solver.hpp>

#include <gtest/gtest.h>

TEST(Solver, QuadraticEquation)
{
    double x1 = 0;
    double x2 = 0;

    solve(1, 2, 1, x1, x2);

    EXPECT_DOUBLE_EQ(x1, -1);
    EXPECT_DOUBLE_EQ(x2, -1);
}
```

## Изменение CMakeLists.txt

В главный `CMakeLists.txt` была добавлена опция для включения тестов:

```cmake
option(BUILD_TESTS "Build tests" OFF)
```

Также был добавлен блок сборки тестов:

```cmake
if(BUILD_TESTS)
    enable_testing()

    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    add_subdirectory(third-party/gtest)

    file(GLOB TEST_SOURCES tests/*.cpp)

    add_executable(check
        ${TEST_SOURCES}
    )

    target_link_libraries(check
        formatter
        formatter_ex
        solver
        gtest_main
    )

    add_test(NAME check COMMAND check)
endif()
```

Этот блок подключает GoogleTest, собирает исполняемый файл `check` и добавляет его в список тестов CMake.

## Проверка сборки

Для проверки проекта были выполнены команды:

```bash
rm -rf _build
cmake -S . -B _build -DBUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build _build
```

После сборки тесты запускались командой:

```bash
cmake --build _build --target test -- ARGS=--verbose
```

Также тестовый исполняемый файл можно было запустить напрямую:

```bash
./_build/check
```

## GitHub Actions

В файл `.github/workflows/ci.yml` была добавлена автоматическая сборка проекта с тестами.
В workflow используется параметр:

```bash
-DBUILD_TESTS=ON
```

Это нужно, чтобы на GitHub Actions проект не только собирался, но и запускал тесты.

## Отправка изменений

После проверки изменения были добавлены в Git:

```bash
git add .
git commit -m "added gtest framework and tests"
git push -u origin main
```

## Итог

В результате в проект был добавлен GoogleTest, созданы тесты для библиотек `formatter`, `formatter_ex` и `solver`, а также настроена сборка и запуск тестов через CMake.


<pre>
[  4%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
[  9%] Linking CXX static library libgtest.a
[  9%] Built target gtest
[ 14%] Building CXX object third-party/gtest/googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
[ 19%] Linking CXX static library libgtest_main.a
[ 19%] Built target gtest_main
[ 23%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 28%] Linking CXX static library libformatter.a
[ 28%] Built target formatter
[ 33%] Building CXX object solver_lib/CMakeFiles/solver.dir/solver.cpp.o
[ 38%] Linking CXX static library libsolver.a
[ 38%] Built target solver
[ 42%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 47%] Linking CXX static library libformatter_ex.a
[ 47%] Built target formatter_ex
[ 52%] Building CXX object CMakeFiles/check.dir/tests/test_formatter.cpp.o
[ 57%] Building CXX object CMakeFiles/check.dir/tests/test_solver.cpp.o
[ 61%] Linking CXX executable check
[ 61%] Built target check
[ 66%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 71%] Linking CXX executable hello_world
[ 71%] Built target hello_world
[ 76%] Building CXX object solver_application/CMakeFiles/equation.dir/equation.cpp.o
[ 80%] Linking CXX executable equation
[ 80%] Built target equation
[ 85%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock.dir/src/gmock-all.cc.o
[ 90%] Linking CXX static library libgmock.a
[ 90%] Built target gmock
[ 95%] Building CXX object third-party/gtest/googlemock/CMakeFiles/gmock_main.dir/src/gmock_main.cc.o
[100%] Linking CXX static library libgmock_main.a
[100%] Built target gmock_main</pre>



<pre>
Running tests...
UpdateCTestConfiguration  from :/home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab05tut/_build/DartConfiguration.tcl
UpdateCTestConfiguration  from :/home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab05tut/_build/DartConfiguration.tcl
Test project /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab05tut/_build
Constructing a list of tests
Done constructing a list of tests
Updating test list for fixtures
Added 0 tests to meet fixture requirements
Checking test dependency graph...
Checking test dependency graph end
test 1
    Start 1: check

1: Test command: /home/vboxuser/Рабочий\ стол/project/projects/ponomaryovmiron_labs/lab05tut/_build/check
1: Working Directory: /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab05tut/_build
1: Test timeout computed to be: 10000000
1: Running main() from /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab05tut/third-party/gtest/googletest/src/gtest_main.cc
1: [==========] Running 3 tests from 3 test cases.
1: [----------] Global test environment set-up.
1: [----------] 1 test from Formatter
1: [ RUN      ] Formatter.SimpleText
1: [       OK ] Formatter.SimpleText (0 ms)
1: [----------] 1 test from Formatter (0 ms total)
1: 
1: [----------] 1 test from FormatterEx
1: [ RUN      ] FormatterEx.ContainsText
1: [       OK ] FormatterEx.ContainsText (0 ms)
1: [----------] 1 test from FormatterEx (0 ms total)
1: 
1: [----------] 1 test from Solver
1: [ RUN      ] Solver.QuadraticEquation
1: [       OK ] Solver.QuadraticEquation (0 ms)
1: [----------] 1 test from Solver (0 ms total)
1: 
1: [----------] Global test environment tear-down
1: [==========] 3 tests from 3 test cases ran. (0 ms total)
1: [  PASSED  ] 3 tests.
1/1 Test #1: check ............................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 1

Total Test time (real) =   0.00 sec</pre>
