#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct {
    char title[50];
    int pages;
} Book;

void check_access_and_print(int fd, int total_records) {
    struct flock lock;
    Book book;
    int available_count = 0;

    printf("Проверка доступа к записям\n");

    for (int i = 0; i < total_records; i++) {
        lock.l_type = F_RDLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = i * sizeof(Book);
        lock.l_len = sizeof(Book);
        lock.l_pid = getpid();

        if (fcntl(fd, F_GETLK, &lock) == -1) {
            perror("Ошибка fcntl");
            continue;
        }

        if (lock.l_type == F_UNLCK) {
            lseek(fd, i * sizeof(Book), SEEK_SET);
            if (read(fd, &book, sizeof(Book)) > 0) {
                printf("[ДОСТУПНО] Запись %d: %s (%d стр.)\n", i + 1, book.title, book.pages);
                available_count++;
            }
        } else {
            printf("[ЗАБЛОКИРОВАНО] Запись %d (PID блокировки: %d)\n", i + 1, lock.l_pid);
        }
    }
    printf("Итого доступно записей: %d\n", available_count);
}

int main() {
    FILE *txtFile;
    int binFd;
    Book books[10];
    
    // 1. Чтение из текстового файла
    txtFile = fopen("books.txt", "r");
    if (!txtFile) { perror("Ошибка открытия books.txt"); return 1; }

    for (int i = 0; i < 10; i++) {
        fscanf(txtFile, "%s %d", books[i].title, &books[i].pages);
    }
    fclose(txtFile);

    // 2. Запись массива структур в бинарный файл
    binFd = open("books.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (binFd == -1) { perror("Ошибка создания books.bin"); return 1; }

    write(binFd, books, sizeof(Book) * 10);
    fsync(binFd); // Сброс буферов на диск

    // 3. Блокировка всего файла (Запретить чтение)
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    
    if (fcntl(binFd, F_SETLK, &fl) == -1) {
        perror("Ошибка блокировки файла");
        return 1;
    }
    printf("Файл полностью заблокирован на запись (exclusive lock).\n");

    
    // 4. Разрешить чтение третьей записи
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 2 * sizeof(Book);
    fl.l_len = sizeof(Book); 
    
    if (fcntl(binFd, F_SETLK, &fl) == -1) {
        perror("Ошибка разблокировки записи");
        return 1;
    }
    printf("Разблокирована запись №3.\n");

    // 5. Вывод содержимого
    
    printf("\nЧтение файла (текущий процесс видит всё, но 3-я запись теперь публична):\n");
    lseek(binFd, 2 * sizeof(Book), SEEK_SET);
    Book b;
    read(binFd, &b, sizeof(Book));
    printf("Содержимое 3-й записи: %s, %d стр.\n", b.title, b.pages);

    close(binFd);
    return 0;
}
