Можно вставить в отчёт вот так:

## Основные созданные CMake-файлы


### Главный `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)

project(lab03hw)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_application)
add_subdirectory(solver_application)

install(TARGETS formatter formatter_ex solver hello_world equation
    RUNTIME DESTINATION bin
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
```

Этот файл является главным для всего проекта.
В нём подключаются все подпроекты: библиотеки `formatter`, `formatter_ex`, `solver`, а также приложения `hello_world` и `equation`.

### `formatter_lib/CMakeLists.txt`

```cmake
add_library(formatter STATIC
    formatter.cpp
)

target_include_directories(formatter PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Этот файл собирает статическую библиотеку `formatter` из файла `formatter.cpp`.
Также здесь указывается путь к заголовочным файлам библиотеки.

### `formatter_ex_lib/CMakeLists.txt`

```cmake
add_library(formatter_ex STATIC
    formatter_ex.cpp
)

target_include_directories(formatter_ex PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(formatter_ex PUBLIC
    formatter
)
```

Этот файл собирает библиотеку `formatter_ex`.
Она использует библиотеку `formatter`, поэтому подключается через `target_link_libraries`.

### `solver_lib/CMakeLists.txt`

```cmake
add_library(solver STATIC
    solver.cpp
)

target_include_directories(solver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
```

Этот файл собирает статическую библиотеку `solver`, в которой находится функция решения квадратного уравнения.

### `hello_world_application/CMakeLists.txt`

```cmake
add_executable(hello_world
    hello_world.cpp
)

target_link_libraries(hello_world
    formatter_ex
)
```

Этот файл создаёт исполняемый файл `hello_world`.
Программа использует библиотеку `formatter_ex` для красивого вывода текста.

### `solver_application/CMakeLists.txt`

```cmake
add_executable(equation
    equation.cpp
)

target_link_libraries(equation
    solver
    formatter_ex
)
```

Этот файл создаёт приложение `equation`.
Оно использует библиотеку `solver` для вычислений и `formatter_ex` для вывода результата.

## Итог

<pre>
[ 10%] Building CXX object formatter_lib/CMakeFiles/formatter.dir/formatter.cpp.o
[ 20%] Linking CXX static library libformatter.a
[ 20%] Built target formatter
[ 30%] Building CXX object formatter_ex_lib/CMakeFiles/formatter_ex.dir/formatter_ex.cpp.o
[ 40%] Linking CXX static library libformatter_ex.a
[ 40%] Built target formatter_ex
[ 50%] Building CXX object solver_lib/CMakeFiles/solver.dir/solver.cpp.o
[ 60%] Linking CXX static library libsolver.a
[ 60%] Built target solver
[ 70%] Building CXX object hello_world_application/CMakeFiles/hello_world.dir/hello_world.cpp.o
[ 80%] Linking CXX executable hello_world
[ 80%] Built target hello_world
[ 90%] Building CXX object solver_application/CMakeFiles/equation.dir/equation.cpp.o
[100%] Linking CXX executable equation
[100%] Built target equation
</pre>


----------------
hello, world
----------------


----------------
x1 = -1.000000
----------------
----------------
x2 = -1.000000
----------------


<pre>
[ 20%] Built target formatter
[ 40%] Built target formatter_ex
[ 60%] Built target solver
[ 80%] Built target hello_world
[100%] Built target equation
Install the project...
-- Install configuration: ""
-- Installing: /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab03hw/_install/lib/libformatter.a
-- Installing: /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab03hw/_install/lib/libformatter_ex.a
-- Installing: /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab03hw/_install/lib/libsolver.a
-- Installing: /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab03hw/_install/bin/hello_world
-- Installing: /home/vboxuser/Рабочий стол/project/projects/ponomaryovmiron_labs/lab03hw/_install/bin/equation
</pre>

