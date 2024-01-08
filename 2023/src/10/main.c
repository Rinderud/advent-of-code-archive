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

/*
The pipes are arranged in a two-dimensional grid of tiles:
    | is a vertical pipe connecting north and south.
    - is a horizontal pipe connecting east and west.
    L is a 90-degree bend connecting north and east.
    J is a 90-degree bend connecting north and west.
    7 is a 90-degree bend connecting south and west.
    F is a 90-degree bend connecting south and east.
    . is ground; there is no pipe in this tile.
    S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
*/
pipe_t find_start(char **matrix, size_t rows, size_t columns)
{
    point_t pos;
    char ch;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            pos = (point_t){.x = i, .y = j};
            ch = matrix[i][j];
            // printf("pos: (%d,%d) = %c\n", pos.x, pos.y, ch);

            if (ch == 'S')
            {
                pipe_t start = (pipe_t){.position = pos, NULL, NULL};
                return start;
            }
        }
    }
    perror("Could not find start");
    exit(1);
}

int main(void)
{
    size_t rows, columns, buf_size;
    char *buffer;
    char **matrix;

    buf_size = 200;
    buffer = malloc(buf_size * sizeof(*buffer)); //! Doesn't check if null

    // Prepp
    printf("Reading the matrix\n");
    columns = getline_rinderud(buffer, buf_size);
    rows = columns; //? Assuming the matrix is a square and not rectangle.
    printf("%zu x %zu\n", rows, columns);

    matrix = malloc(rows * sizeof(*matrix)); //! Doesn't check if null
    for (size_t i = 0; i < rows; i++)
    {
        //! Doesn't check if null
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

    // Find the starting location (S)
    pipe_t start;
    start = find_start(matrix, rows, columns);
    printf("Start position: (%d,%d)\n", start.position.x, start.position.y);

    // TODO(Rinderud): Traverse the matrix and connect the pipes.

    // Free
    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(buffer);

    return 0;
}
