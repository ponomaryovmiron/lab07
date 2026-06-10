# Отчёт по лабораторной работе №3

## Цель работы

Цель лабораторной работы — разобраться с системой автоматизации сборки CMake и настроить сборку проекта с библиотекой и примерами.

## Подготовка проекта

За основу был взят репозиторий `lab02tut`. Он был склонирован в новую папку `lab03tut`, после чего был изменён удалённый репозиторий:

```bash
git clone https://github.com/ponomaryovmiron/lab02tut.git lab03tut
cd lab03tut
git remote remove origin
git remote add origin https://github.com/ponomaryovmiron/lab03tut.git
git branch -M main
```

Это нужно, чтобы использовать готовые исходные файлы из прошлой лабораторной работы, но отправлять результат уже в новый репозиторий.

## Ручная сборка проекта

Сначала проект был собран вручную через `g++`.

Файл библиотеки был скомпилирован в объектный файл:

```bash
g++ -std=c++11 -I./include -c sources/print.cpp
```

После этого из объектного файла была создана статическая библиотека:

```bash
ar rvs print.a print.o
```

Затем были собраны примеры:

```bash
g++ -std=c++11 -I./include -c examples/example1.cpp
g++ example1.o print.a -o example1

g++ -std=c++11 -I./include -c examples/example2.cpp
g++ example2.o print.a -o example2
```

Примеры были запущены для проверки. Первый пример выводил текст в консоль, второй записывал текст в файл `log.txt`.

После проверки временные файлы были удалены:

```bash
rm -rf example1.o example2.o print.o
rm -rf print.a
rm -rf example1 example2
rm -rf log.txt
```

## Настройка CMake

Для автоматической сборки был создан файл `CMakeLists.txt`.

В нём указаны минимальная версия CMake и стандарт C++:

```cmake
cmake_minimum_required(VERSION 3.10)

project(print)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

Далее была добавлена статическая библиотека `print`:

```cmake
add_library(print STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/sources/print.cpp
)

target_include_directories(print PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
```

Также были добавлены два исполняемых файла:

```cmake
add_executable(example1
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/example1.cpp
)

add_executable(example2
    ${CMAKE_CURRENT_SOURCE_DIR}/examples/example2.cpp
)

target_link_libraries(example1 print)
target_link_libraries(example2 print)
```

Команда `target_link_libraries` нужна для подключения библиотеки `print` к примерам.

## Сборка через CMake

После настройки CMake проект был собран командами:

```bash
cmake -S . -B _build
cmake --build _build
```

Также были отдельно собраны targets:

```bash
cmake --build _build --target print
cmake --build _build --target example1
cmake --build _build --target example2
```

После сборки были проверены результаты:

```bash
_build/example1 && echo
_build/example2
cat log.txt && echo
```

Оба примера работали корректно.

## Установка проекта

В `CMakeLists.txt` были добавлены правила установки:

```cmake
install(TARGETS print example1 example2
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
)
```

После этого была выполнена установка в папку `_install`:

```bash
cmake -S . -B _build -DCMAKE_INSTALL_PREFIX=_install
cmake --build _build --target install
tree _install
```

В результате появились папки `bin`, `lib` и `include`.

## Отправка на GitHub

Чтобы не добавлять временные файлы сборки, был создан `.gitignore`:

```text
*build*/
*install*/
*.swp
.idea/
log.txt
*.o
*.a
example1
example2
```

После проверки все изменения были добавлены в Git:

```bash
git add CMakeLists.txt README.md .gitignore
git commit -m "added CMakeLists.txt"
git push -u origin main
```

## Итог

В результате был создан репозиторий `lab03tut`.
В проект добавлена автоматическая сборка через CMake.
CMake собирает статическую библиотеку `print`, два примера `example1` и `example2`, а также поддерживает установку файлов в отдельную папку.


Сборка:
<pre>
[ 16%] Building CXX object CMakeFiles/print.dir/sources/print.cpp.o
[ 33%] Linking CXX static library libprint.a
[ 33%] Built target print
[ 50%] Building CXX object CMakeFiles/example1.dir/examples/example1.cpp.o
[ 66%] Linking CXX executable example1
[ 66%] Built target example1
[ 83%] Building CXX object CMakeFiles/example2.dir/examples/example2.cpp.o
[100%] Linking CXX executable example2
[100%] Built target example2
</pre>
