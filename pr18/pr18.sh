#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Ошибка: Недостаточно аргументов."
    echo "Использование: $0 <целевой_каталог> <файл1> <файл2> ..."
    exit 1
fi

DEST_DIR="$1"

if [ -d "$DEST_DIR" ]; then
    echo "Ошибка: Целевой каталог '$DEST_DIR' уже существует. Укажите новый путь."
    exit 1
fi

mkdir -p "$DEST_DIR"

shift

count=1

for file_path in "$@"; do
    if [ ! -f "$file_path" ]; then
        echo "Файл '$file_path' не найден"
        continue
    fi

    extension="${file_path##*.}"
    
    new_name="video-$count.$extension"

    cp "$file_path" "$DEST_DIR/$new_name"
    
    echo "Файл '$file_path' скопирован как '$new_name'"

    count=$((count + 1))
done

echo "Обработка завершена. Результат в папке: $DEST_DIR"
