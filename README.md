# Мини-отчёт по ЛР4



## Что было сделано

За основу был взят проект из `lab03hw`.
Для новой лабораторной работы был создан репозиторий `lab04`.

```bash
git clone https://github.com/ponomaryovmiron/lab03hw.git lab04
cd lab04
git remote remove origin
git remote add origin https://github.com/ponomaryovmiron/lab04.git
git branch -M main
```

Эти команды склонировали прошлую лабораторную работу и подключили новый репозиторий.

## GitHub Actions

Для автоматической сборки был создан файл:

```text
.github/workflows/ci.yml
```

Файл `ci.yml` запускает сборку при `push`, `pull_request` и вручную через `workflow_dispatch`.

```yaml
name: CI

on:
  push:
    branches:
      - main
  pull_request:
    branches:
      - main
  workflow_dispatch:
```

## Сборка на Linux

Для Linux настроены две сборки:

```text
Linux gcc
Linux clang
```

В workflow используется matrix:

```yaml
matrix:
  include:
    - compiler: gcc
      cc: gcc
      cxx: g++
    - compiler: clang
      cc: clang
      cxx: clang++
```

Сначала устанавливаются нужные инструменты:

```yaml
- name: Install tools
  run: |
    sudo apt-get update
    sudo apt-get install -y cmake gcc g++ clang
```

Затем проект конфигурируется и собирается:

```yaml
- name: Configure
  run: |
    rm -rf _build
    cmake -S . -B _build \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=${{ matrix.cc }} \
      -DCMAKE_CXX_COMPILER=${{ matrix.cxx }}

- name: Build
  run: |
    cmake --build _build --config Release
```

После сборки запускаются программы:

```yaml
- name: Run hello_world
  run: |
    ./_build/hello_world_application/hello_world

- name: Run equation
  run: |
    echo "1 2 1" | ./_build/solver_application/equation
```

## Сборка на Windows

Для Windows также настроены две сборки:

```text
Windows gcc
Windows clang
```

Для этого используется MSYS2:

```yaml
- name: Setup MSYS2
  uses: msys2/setup-msys2@v2
  with:
    msystem: UCRT64
    update: true
```

Для `gcc` устанавливается пакет:

```text
mingw-w64-ucrt-x86_64-gcc
```

Для `clang` устанавливается пакет:

```text
mingw-w64-ucrt-x86_64-clang
```

Сборка выполняется через CMake и Ninja:

```yaml
- name: Configure
  run: |
    rm -rf _build
    cmake -S . -B _build -G Ninja \
      -DCMAKE_BUILD_TYPE=Release \
      -DCMAKE_C_COMPILER=${{ matrix.cc }} \
      -DCMAKE_CXX_COMPILER=${{ matrix.cxx }}

- name: Build
  run: |
    cmake --build _build --config Release
```

После сборки запускаются `.exe` файлы:

```yaml
- name: Run hello_world
  run: |
    ./_build/hello_world_application/hello_world.exe

- name: Run equation
  run: |
    echo "1 2 1" | ./_build/solver_application/equation.exe
```

## Итог

В результате GitHub Actions выполняет 4 проверки:

```text
Linux gcc
Linux clang
Windows gcc
Windows clang
```

Cборка:
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
