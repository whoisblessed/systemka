#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int number_count = 0;
    int inside_number = 0;

    while ((ch = getchar()) != EOF) {
        if (isdigit(ch)) {
            if (!inside_number) {
                number_count++;
                inside_number = 1;
            }
        } else {
            inside_number = 0;
        }
    }

    printf("Количество найденных чисел: %d\n", number_count);
    return 0;
}
