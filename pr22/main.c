#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int is_txt_file(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    return (dot && strcmp(dot, ".txt") == 0);
}

int process_directory(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat entry_stat;
    int count = 0;
    char full_path[1024];

    if ((dir = opendir(path)) == NULL)
    {
        perror("Ошибка открытия каталога");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (lstat(full_path, &entry_stat) == -1)
        {
            continue;
        }

        if (S_ISDIR(entry_stat.st_mode))
        {
            int fd[2];
            if (pipe(fd) == -1)
            {
                perror("Pipe сломався");
                continue;
            }

            pid_t pid = fork();

            if (pid == -1)
            {
                perror("Форканье пида сломалось");
                close(fd[0]);
                close(fd[1]);
            }
            else if (pid == 0)
            {
                close(fd[0]);
                closedir(dir);

                int sub_count = process_directory(full_path);

                write(fd[1], &sub_count, sizeof(sub_count));
                close(fd[1]);

                exit(0);
            }
            else
            {
                close(fd[1]);

                int sub_result = 0;
                read(fd[0], &sub_result, sizeof(sub_result));
                close(fd[0]);


                wait(NULL);

                count += sub_result;
            }
        }
        else if (S_ISREG(entry_stat.st_mode))
        {
            if (is_txt_file(entry->d_name))
            {
                count++;
            }
        }
    }

    closedir(dir);
    return count;
}

int main(int argc, char *argv[])
{
    char *target_dir = ".";

    if (argc > 1)
    {
        target_dir = argv[1];
    }

    printf("Сканирование каталога: %s\n", target_dir);
    int total = process_directory(target_dir);
    printf("Всего файлов .txt: %d\n", total);

    return 0;
}
