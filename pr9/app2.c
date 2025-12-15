#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        int words = 0;
        int in_word = 0;

        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isspace(buffer[i])) {
                if (!in_word) {
                    words++;
                    in_word = 1;
                }
            } else {
                in_word = 0;
            }
        }

        buffer[strcspn(buffer, "\n")] = 0;
        
        printf("%s %d\n", buffer, words);
    }
    return 0;
}
