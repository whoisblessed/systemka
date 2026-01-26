#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Ошибка воркер: Не передан файл для обработки\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Ошибка воркер: Не удалось открыть файл");
        return 2;
    }

    int count = 0;
    int ch;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF)
    {
        if (isspace(ch))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
    }

    printf("[воркер] Файл '%s' содержит %d слов(а).\n", argv[1], count);

    fclose(file);
    return 0;
}
