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
    unsigned int distance;
    pipe_t *backPipe;
    pipe_t *nextPipe;
};

typedef struct
{
    pipe_t *A;
    pipe_t *B;
} connecting_pipes_t;

void push(pipe_t *old, pipe_t *new)
{
    old->nextPipe = new;
    new->backPipe = old;
    new->distance = old->distance + 1;
}

void destroy_LL(pipe_t *start)
{
    if (start == NULL)
    {
        return;
    }

    if (start->nextPipe == NULL)
    {
        free(start);
        return;
    }

    pipe_t *pipe;
    pipe = start;
    while (pipe->nextPipe != NULL)
    {
        pipe = pipe->nextPipe;
        free(pipe->backPipe);
    }
    free(pipe);
}

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

pipe_t find_start(char **matrix, size_t rows, size_t columns)
{
    point_t pos;
    char ch;
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < columns; j++)
        {
            pos = (point_t){.x = j, .y = i};
            ch = matrix[i][j];

            if (ch == 'S')
            {
                pipe_t start = (pipe_t){.position = pos, 0, NULL, NULL};
                return start;
            }
        }
    }
    perror("Could not find start");
    exit(1);
}

connecting_pipes_t check(pipe_t *start, char **matrix, size_t rows, size_t columns)
{
    pipe_t *pipe_A, *pipe_B;
    pipe_A = NULL;
    pipe_B = NULL;

    // Check around
    int x, y;
    point_t pos;
    char ch;

    // Left
    if (start->position.x > 0)
    {
        x = start->position.x - 1;
        y = start->position.y;
        ch = matrix[y][x];

        if (ch == 'F' || ch == '-' || ch == 'L' || ch == 'S') // The ones connecting to east
        {
            // Valid pipe, connect
            pos = (point_t){.x = x, .y = y};
            if (pipe_A)
            {
                pipe_B = malloc(sizeof(*pipe_B));
                *pipe_B = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
            else
            {
                pipe_A = malloc(sizeof(*pipe_A));
                *pipe_A = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
        }
    }

    // Right
    if (start->position.x < columns - 1)
    {
        x = start->position.x + 1;
        y = start->position.y;
        ch = matrix[y][x];

        if (ch == 'J' || ch == '-' || ch == '7' || ch == 'S') // The ones connecting to west
        {
            // Valid pipe, connect
            pos = (point_t){.x = x, .y = y};
            if (pipe_A)
            {
                pipe_B = malloc(sizeof(*pipe_B));
                *pipe_B = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
            else
            {
                pipe_A = malloc(sizeof(*pipe_A));
                *pipe_A = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
        }
    }

    // Up
    if (start->position.y > 0)
    {
        x = start->position.x;
        y = start->position.y - 1;
        ch = matrix[y][x];

        if (ch == '|' || ch == '7' || ch == 'F' || ch == 'S') // The ones connecting to south
        {
            // Valid pipe, connect
            pos = (point_t){.x = x, .y = y};
            if (pipe_A)
            {
                pipe_B = malloc(sizeof(*pipe_B));
                *pipe_B = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
            else
            {
                pipe_A = malloc(sizeof(*pipe_A));
                *pipe_A = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
        }
    }

    // Down
    if (start->position.y < rows - 1)
    {
        x = start->position.x;
        y = start->position.y + 1;
        ch = matrix[y][x];

        if (ch == '|' || ch == 'L' || ch == 'J' || ch == 'S') // The ones connecting to north
        {
            // Valid pipe, connect
            pos = (point_t){.x = x, .y = y};
            if (pipe_A)
            {
                pipe_B = malloc(sizeof(*pipe_B));
                *pipe_B = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
            else
            {
                pipe_A = malloc(sizeof(*pipe_A));
                *pipe_A = (pipe_t){.position = pos, .distance = 1, NULL, NULL};
            }
        }
    }
    if (pipe_A == NULL || pipe_B == NULL)
    {
        printf("Pipe is null!");
    }
    else
    {
        // printf("A: (%d,%d), B: (%d,%d)\n", pipe_A->position.x, pipe_A->position.y, pipe_B->position.x, pipe_B->position.y);
    }
    return (connecting_pipes_t){.A = pipe_A, .B = pipe_B};
}

int isDifferent(pipe_t *A, pipe_t *B)
{
    return (A->position.x - B->position.x) * 256 + (A->position.y - B->position.y);
}

int loop_back(pipe_t *start, char **matrix, size_t rows, size_t columns)
{
    pipe_t *pipe;
    start->distance = 1;
    pipe = start->backPipe;
    while (isDifferent(pipe->backPipe, start) && pipe->distance > pipe->nextPipe->distance)
    {
        if (pipe->distance > pipe->nextPipe->distance + 1)
        {
            pipe->distance = pipe->nextPipe->distance + 1;
        }
        else
        {
            return pipe->distance;
        }

        pipe = pipe->backPipe;
    }

    return start->distance;
}

int main(void)
{
    size_t rows, columns, buf_size;
    char *buffer;
    char **matrix;

    buf_size = 200;
    buffer = malloc(buf_size * sizeof(*buffer)); //! Doesn't check if null

    // Prepp
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

    /*
        // Print the matrix for validation
        for (size_t i = 0; i < rows; i++)
        {
            printf("%s\n", matrix[i]);
        }
    */

    // Find the starting location (S)
    pipe_t *start;
    start = malloc(sizeof(*start));
    *start = find_start(matrix, rows, columns);
    printf("Start position: (%d,%d)\n", start->position.x, start->position.y);

    connecting_pipes_t pipes;
    pipes = check(start, matrix, rows, columns);
    push(start, pipes.A);
    start->backPipe = pipes.B;

    pipe_t *pipe = start->nextPipe;
    while (isDifferent(pipe, start->backPipe))
    {
        pipes = check(pipe, matrix, rows, columns);
        if (pipes.A == NULL || pipes.B == NULL)
        {
            goto frees;
        }

        if (isDifferent(pipe->backPipe, pipes.A) && isDifferent(pipes.A, start))
        {
            push(pipe, pipes.A);
            free(pipes.B);
        }
        else if (isDifferent(pipes.B, start))
        {
            push(pipe, pipes.B);
            free(pipes.A);
        }
        else
        {
            printf("Faulty logic\n");
            goto frees;
        }
        pipe = pipe->nextPipe;
    }
    printf("length of full pipe: %d\n", pipe->distance + 1);
    int max_dist = loop_back(pipe, matrix, rows, columns);
    printf("farthest = %d", max_dist);

frees:
    // Free
    free(start->backPipe);
    destroy_LL(start);
    for (size_t i = 0; i < rows; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    free(buffer);

    return 0;
}
