#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Использование: %s <путь_к_файлу>\n", argv[0]);
        return 1;
    }

    const char* filepath = argv[1];
    FILE *file;

    printf("Проверка прав доступа для файла: %s\n", filepath);

    printf("Попытка открыть файл для чтения... ");
    file = fopen(filepath, "r");

    if (file) {
        printf("УСПЕХ.\n");
        fclose(file);
    } else {
        printf("ОШИБКА.\n");
        perror("Подробности ошибки чтения");
    }
    printf("Попытка открыть файл для записи... ");
    // Используем "a" (append) для проверки права на изменение/добавление
    file = fopen(filepath, "a");

    if (file) {
        printf("УСПЕХ.\n");
        // Если файл открылся успешно, сразу закрываем его, чтобы не оставлять открытых дескрипторов
        fclose(file);
    } else {
        printf("ОШИБКА.\n");
        perror("Подробности ошибки записи");
    }

    return 0;
}
