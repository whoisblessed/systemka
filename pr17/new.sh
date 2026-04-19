#!/bin/bash

mkdir -p students/source

mkdir -p "students/source/Комаров Сергей Юрьевич"
mkdir -p "students/source/Петров Василий Игоревич"
mkdir -p "students/source/Чесарова Дарья Михайловна"

touch "students/source/Комаров Сергей Юрьевич/zadacha otvet.txt"
touch "students/source/Петров Василий Игоревич/ответ.txt"
touch "students/source/Чесарова Дарья Михайловна/text-one.txt"

echo "Ответ Комарова по задаче..." > "students/source/Комаров Сергей Юрьевич/zadacha otvet.txt"
echo "Василий Петров: решение готово." > "students/source/Петров Василий Игоревич/ответ.txt"
echo "Текст работы Дарьи Чесаровой." > "students/source/Чесарова Дарья Михайловна/text-one.txt"

echo "Структура файлов успешно создана!"
