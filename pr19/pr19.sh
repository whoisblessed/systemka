#!/bin/bash
if [ ! -d "Images" ]; then
    mkdir "Images"
    echo "Папка 'Images' создана."
fi

mv *.jpg "Images/" 2>/dev/null

if [ $? -eq 0 ]; then
    echo "Все файлы .jpg успешно перемещены в папку Images."
else
    echo "Файлы .jpg не найдены в текущей директории."
fi
