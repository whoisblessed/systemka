#!/bin/bash

if [ -z "$1" ]; then
    echo "Ошибка: укажите папку со студентами (например: ./students)"
    exit 1
fi

DATA_DIR="$1"

if [ ! -d "$DATA_DIR" ]; then
    echo "Ошибка: путь '$DATA_DIR' не найден"
    exit 1
fi

SRC="$DATA_DIR/source"
RES="$DATA_DIR/results"

if [ ! -d "$SRC" ]; then
    echo "Ошибка: в каталоге нет папки source"
    exit 1
fi

for student_folder in "$SRC"/*; do
    [ -d "$student_folder" ] || continue
    
    name=$(basename "$student_folder")
    echo "Обработка студента: $name"

    file_count=$(find "$student_folder" -maxdepth 1 -type f | wc -l)
    
    if [ "$file_count" -ne 1 ]; then
        echo "Пропуск: в папке должно быть ровно 1 файл (сейчас $file_count)"
        continue
    fi

    work_file=$(find "$student_folder" -maxdepth 1 -type f)

    is_text=$(file -b --mime-type "$work_file" | grep "text/")
    if [ -z "$is_text" ]; then
        echo "Ошибка: файл не текстовый!"
        continue
    fi

    echo "Открываю файл через less"
    sleep 1
    less "$work_file"

    echo -n "Оценку для $name (0-6)? "
    read grade

    mkdir -p "$RES/$grade"
    mv "$student_folder" "$RES/$grade/"

    echo "Студент перемещен в папку с оценкой $grade"
done

echo "Все работы проверены."
