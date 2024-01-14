# Используйте базовый образ Ubuntu
FROM ubuntu:latest

# Установите переменную окружения для избежания интерактивных запросов
ENV DEBIAN_FRONTEND=noninteractive

# Установите необходимые пакеты
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    valgrind \
    pkg-config \
    check  # Добавляем пакет check

# Установите gcovr
RUN apt-get install -y gcovr

# Установите рабочую директорию
WORKDIR /project

# Скопируйте файлы вашего проекта в контейнер
COPY . /project

# Пересоберите объектные файлы внутри контейнера
RUN make clean
RUN make test

# Вход в контейнер и выполнение valgrind
CMD [ "valgrind", "--leak-check=full", "--show-leak-kinds=all", "--track-origins=yes", "./s21_test" ]
