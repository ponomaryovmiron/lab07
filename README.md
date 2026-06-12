# Отчёт по лабораторной работе №7

## Подготовка проекта

Для работы был создан репозиторий `lab07`. За основу был взят предыдущий проект `lab06`, после чего удалены лишние файлы CMake/CPack и добавлены файлы для Docker-проекта.

```bash
git clone https://github.com/ponomaryovmiron/lab06.git lab07
cd lab07
git remote remove origin
git remote add origin https://github.com/ponomaryovmiron/lab07.git
git branch -M main
```

## Создание приложения

В проект был добавлен файл `main.py`.
Приложение написано на Flask. При запуске оно выводит сообщение:

```text
Hello, Docker!
```

Также приложение подключается к базе данных MySQL и выводит список задач из таблицы `tasks`.

Основной адрес приложения:

```text
http://localhost:5555
```

## Файл зависимостей

Был создан файл `requirements.txt`, в котором указаны библиотеки Python:

```text
flask
pymysql
requests
```

`flask` используется для web-приложения, `pymysql` — для подключения к MySQL, `requests` добавлен как дополнительная библиотека по примеру задания.

## Dockerfile

Для сборки Docker-образа был создан файл `Dockerfile`.

```dockerfile
FROM python:3.9-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    && rm -rf /var/lib/apt/lists/*

COPY requirements.txt .

RUN pip install --no-cache-dir -r requirements.txt

COPY . .

EXPOSE 5000

CMD ["python", "main.py"]
```

В этом файле указывается базовый образ Python, рабочая папка `/app`, установка зависимостей и команда запуска приложения.

## Настройка базы данных

Для базы данных был создан файл:

```text
db/init.sql
```

В нём создаётся база `labdb`, таблица `tasks` и добавляются начальные записи:

```sql
INSERT INTO tasks (name) VALUES
('Пример 1'),
('Пример 2');
```

## Docker Compose

Для запуска приложения и базы данных был создан файл `docker-compose.yml`.

В нём описаны два сервиса:

```text
app
db
```

Сервис `app` собирает Flask-приложение из `Dockerfile`.

Сервис `db` использует образ MySQL 8.0.

Для приложения был настроен проброс порта:

```text
5555:5000
```

Это значит, что внутри контейнера приложение работает на порту `5000`, а на компьютере открывается через порт `5555`.

## Запуск проекта

Проект запускался командой:

```bash
sudo docker compose up --build
```

Для полного пересоздания контейнеров и базы данных использовалась команда:

```bash
sudo docker compose down -v
```

После запуска приложение открывалось в браузере:

```text
http://localhost:5555
```

На странице отображался список из базы данных:

```text
Пример 1
Пример 2
```

## Проверка контейнера

Также была выполнена проверка копирования файла в контейнер:

```bash
sudo docker cp README.md lab07_app:/home/README.md
sudo docker exec -it lab07_app bash
```

Внутри контейнера проверялось наличие файла:

```bash
ls -la /home
cat /home/README.md
```

## Возникшая проблема

При запуске возникала ошибка скачивания образа:

```text
failed to fetch anonymous token
lookup auth.docker.io on 127.0.0.53:53: server misbehaving
```

Причина была не в проекте, а в DNS-настройках Docker/Ubuntu. Для исправления был настроен DNS для Docker через файл:

```text
/etc/docker/daemon.json
```

После перезапуска Docker образ `python:3.9-slim` смог скачаться корректно.

## Отправка на GitHub

После проверки файлы проекта были добавлены в Git:

```bash
git add .
git commit -m "complete docker homework"
git push -u origin main
```

## Итог

В результате был создан проект `lab07`, в котором настроено Flask-приложение, база данных MySQL и запуск через Docker Compose. Приложение работает на порту `5555` и выводит данные из таблицы MySQL.


<img width="1280" height="800" alt="VirtualBox_Ubunta_13_06_2026_00_20_08" src="https://github.com/user-attachments/assets/23bd4fbe-4064-4448-b347-d6cd4e00247d" />
