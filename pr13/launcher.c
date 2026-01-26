#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];

    printf("[Лаунфер] Запускаю процесс подсчета слов...\n");

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {

        execl("./worker", "worker", filename, NULL);

        perror("Exec failed");
        exit(1);
    }
    else
    {

        int status;

        wait(&status);

        if (WIFEXITED(status))
        {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0)
            {
                printf("[Лаунфер] Программа успешно завершилась (код 0).\n");
            }
            else
            {
                printf("[Лаунфер] Программа завершилась с ошибкой (код %d).\n", exit_code);
            }
        }
        else
        {
            printf("[Лаунфер] Программа завершилась аварийно.\n");
        }
    }

    return 0;
}
