#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define ROWS 5
#define COLS 5

int matA[ROWS][COLS];
int matB[ROWS][COLS];
int matC[ROWS][COLS];

void *add_row(void *arg)
{
    int row_idx = *(int *)arg;

    for (int j = 0; j < COLS; j++)
    {
        matC[row_idx][j] = matA[row_idx][j] + matB[row_idx][j];
    }

    return NULL;
}

int main()
{
    pthread_t threads[ROWS];
    int thread_args[ROWS];

    srand(time(NULL));

    printf("Матрица A:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
            printf("%d ", matA[i][j]);
        }
        printf("\n");
    }

    printf("\nМатрица B:\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", matB[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < ROWS; i++)
    {
        thread_args[i] = i;

        if (pthread_create(&threads[i], NULL, add_row, &thread_args[i]) != 0)
        {
            perror("Ошибка создания потока");
            return 1;
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nРезультирующая матрица C (A + B):\n");
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }

    return 0;
}
