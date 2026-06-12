# Отчёт по лабораторной работе №6


## Подготовка проекта

Для лабораторной работы был создан репозиторий `lab06`. За основу был взят предыдущий проект, после чего он был упрощён до одного приложения `solver`.

```bash
git clone https://github.com/ponomaryovmiron/lab05tut.git lab06
cd lab06
git remote remove origin
git remote add origin https://github.com/ponomaryovmiron/lab06.git
git branch -M main
```

Приложение `solver` считывает два числа и вычисляет гипотенузу по формуле:

```text
c = sqrt(a * a + b * b)
```

## Настройка CMake

В проекте был создан основной `CMakeLists.txt`. В нём указана версия проекта, добавлено приложение `solver` и подключён файл настройки CPack.

```cmake
cmake_minimum_required(VERSION 3.10)

project(lab06 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver
    solver_application/solver.cpp
)

install(TARGETS solver
    RUNTIME DESTINATION bin
    BUNDLE DESTINATION .
)

include(CPackConfig.cmake)
```

## Настройка CPack

Для создания пакетов был добавлен файл `CPackConfig.cmake`. В нём были указаны название пакета, версия, автор, описание, лицензия и параметры для разных форматов пакетов.

Проект поддерживает сборку следующих пакетов:

```text
.tar.gz
.zip
.deb
.rpm
.dmg
.msi
```

Локальная проверка выполнялась командами:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
echo "3 4" | ./build/solver
cpack --config build/CPackConfig.cmake -G TGZ -B artifacts
```

## GitHub Actions и релизы

Для автоматической сборки был создан workflow:

```text
.github/workflows/release.yml
```

Он выполняет сборку проекта, проверяет запуск `solver`, а при появлении git-тега собирает пакеты и загружает их в GitHub Releases.

Релиз создаётся после отправки тега:

```bash
git tag v0.1.0
git push origin v0.1.0
```

После этого GitHub Actions автоматически собирает пакеты и прикрепляет их к релизу.

## Итог

В результате был создан проект `lab06`, настроена упаковка приложения `solver` через CPack и добавлена автоматическая публикация релизов через GitHub Actions. При создании нового тега в репозитории появляется релиз с архивами исходного кода и пакетами для разных операционных систем.
