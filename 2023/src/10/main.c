#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct pipe_t pipe_t;

typedef struct point_t
{
    int x;
    int y;
} point_t;

struct pipe_t
{
    point_t position;
    pipe_t *connectedPipeA;
    pipe_t *connectedPipeB;
};

size_t getline_rinderud(char *buffer, size_t bufsize)
{
    char c;
    size_t characters;

    characters = 0;
    c = getchar();
    while (c != '\n' && c != EOF && characters < bufsize)
    {
        if (characters >= bufsize)
        {
            printf("Reached the end of the buffer.\n");
            return characters;
        }

        buffer[characters] = c;
        characters++;
        c = getchar();
    }
    buffer[characters] = '\0';
    return characters;
}

int main(void)
{
    size_t rows, columns, buf_size;
    char *buffer;
    char **matrix;

    buf_size = 200;
    buffer = malloc(buf_size * sizeof(*buffer));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    columns = getline_rinderud(buffer, buf_size);
    rows = columns; //? Assuming the matrix is a square and not rectangle.
    printf("%zu x %zu\n", rows, columns);

    matrix = malloc(rows * sizeof(*matrix));
    for (size_t i = 0; i < rows; i++)
    {
        matrix[i] = calloc(columns + 1, sizeof(**matrix)); // +1 to accomodate the \0
    }

    // Read into the matrix
    strcpy(matrix[0], buffer);
    for (size_t i = 1; i < rows; i++)
    {
        getline_rinderud(buffer, columns);
        strcpy(matrix[i], buffer);
    }

    // Print the matrix for validation
    for (size_t i = 0; i < rows; i++)
    {
        printf("%s\n", matrix[i]);
    }

    // Free
    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(buffer);

    return 0;
}
