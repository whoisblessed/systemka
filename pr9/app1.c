#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TARGET "03.05.2024"

int main() {
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        if (strncmp(buffer, TARGET, 10) == 0) {
            fputs(buffer, stdout);
        }
    }
    return 0;
}
