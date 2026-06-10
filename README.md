# Отчёт по лабораторной работе №2 Tutorial

## Настройка репозитория

Сначала была создана папка проекта и инициализирован Git-репозиторий:

```bash
mkdir lab02tut
cd lab02tut
git init
git branch -M main
```

Эти команды создали локальный репозиторий и сделали основной веткой `main`.

Далее были указаны данные пользователя Git:

```bash
git config --global user.name "ponomaryovmiron"
git config --global user.email "godgezuru@gmail.com"
```

После этого был подключён удалённый репозиторий GitHub:

```bash
git remote add origin https://github.com/ponomaryovmiron/lab02tut.git
```

## Создание README и .gitignore

Был создан файл `README.md`:

```bash
cat > README.md
```

В нём было кратко описано, что находится в проекте.

Также был создан файл `.gitignore`:

```bash
cat > .gitignore
```

В него были добавлены временные файлы и папки, которые не нужно отправлять в GitHub:

```text
*build*/
*install*/
*.swp
.idea/
```

Это нужно, чтобы в репозиторий не попадали файлы сборки и настройки редакторов.

## Создание структуры проекта

Для проекта были созданы три папки:

```bash
mkdir sources
mkdir include
mkdir examples
```

Папка `sources` нужна для файлов с реализацией кода.
Папка `include` нужна для заголовочных файлов.
Папка `examples` нужна для примеров использования библиотеки.

## Создание функции print

В папке `sources` был создан файл `print.cpp`:

```bash
cat > sources/print.cpp
```

В этом файле была написана реализация функции `print`.
Функция выводит переданный текст либо в консоль, либо в файл.

В папке `include` был создан файл `print.hpp`:

```bash
cat > include/print.hpp
```

В этом файле были объявлены функции `print`, чтобы их можно было использовать в других `.cpp` файлах.

## Создание примеров

Были созданы два примера.

Первый пример:

```bash
cat > examples/example1.cpp
```

Он выводит текст `hello` в консоль.

Второй пример:

```bash
cat > examples/example2.cpp
```

Он создаёт файл `log.txt` и записывает в него текст `hello`.

## Проверка компиляции

Чтобы проверить, что программа работает, были выполнены команды компиляции:

```bash
mkdir -p build
g++ -std=c++11 sources/print.cpp examples/example1.cpp -Iinclude -o build/example1
g++ -std=c++11 sources/print.cpp examples/example2.cpp -Iinclude -o build/example2
```

Первая команда создаёт папку `build`.
Вторая команда собирает первый пример.
Третья команда собирает второй пример.

После этого были запущены программы:

```bash
./build/example1
./build/example2
cat log.txt
```

Первый пример вывел `hello` в консоль.
Второй пример записал `hello` в файл `log.txt`.

## Отправка на GitHub

После проверки временный файл `log.txt` был удалён:

```bash
rm -f log.txt
```

Затем все файлы были добавлены в Git:

```bash
git add .
```

Был создан коммит:

```bash
git commit -m "added sources"
```

После этого проект был отправлен на GitHub:

```bash
git push -u origin main
```

## Итог

В результате был создан репозиторий `lab02tut`, в который добавлены:

```text
README.md
.gitignore
include/print.hpp
sources/print.cpp
examples/example1.cpp
examples/example2.cpp
```

В проекте реализована простая функция `print` и два примера её использования: вывод текста в консоль и запись текста в файл.
