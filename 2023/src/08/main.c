#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ID_SIZE (3)

typedef struct
{
    char id[ID_SIZE];
    char left[ID_SIZE];
    char right[ID_SIZE];
} map_choice_t;

void print_choice(map_choice_t x)
{
    size_t i;
    for (i = 0; i < ID_SIZE; i++)
    {
        printf("%c", x.id[i]);
    }
    printf(" = (");
    for (i = 0; i < ID_SIZE; i++)
    {
        printf("%c", x.left[i]);
    }
    printf(", ");
    for (i = 0; i < ID_SIZE; i++)
    {
        printf("%c", x.right[i]);
    }
    printf(")\n");
}

// TODO: what happends when the id does not exist in the array?
map_choice_t find_choice(char from[ID_SIZE], size_t N, map_choice_t *choices)
{
    size_t i, j;
    int t;
    map_choice_t choice;

    for (i = 0; i < N; i++)
    {
        choice = choices[i];
        t = 0;
        for (j = 0; j < ID_SIZE; j++)
        {
            if (from[j] == choice.id[j])
            {
                t++;
            }
        }
        if (t == ID_SIZE)
        {
            return choice;
        }
    }
    return choice;
}

/**
 * Got tired of getting the stdlib getline so made my own simple function for this particular application.
 */
int getline_rinderud(char *buffer, size_t *bufsize)
{
    int c, characters;

    characters = 0;
    c = getchar();
    while (c != '\n' && c != EOF)
    {
        if (characters >= *bufsize)
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
    size_t characters, dir_size, nbr_choices, choices_size, bufsize, i, j;
    char *buffer;
    char *directions;
    char curr_id[ID_SIZE];
    map_choice_t *choices;

    bufsize = 300;
    choices_size = 800;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if (buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    characters = getline_rinderud(buffer, &bufsize);

    printf("%zu characters were read.\n", characters);
    printf("Read: %s\n", buffer);

    dir_size = characters + 1;
    directions = (char *)malloc(dir_size * sizeof(char));
    if (directions == NULL)
    {
        perror("Unable to allocate for direction");
        exit(1);
    }

    directions = strcpy(directions, buffer);

    choices = (map_choice_t *)malloc(choices_size * sizeof(map_choice_t));
    nbr_choices = 0;

    characters = getline_rinderud(buffer, &bufsize); // get rid of the blank line
    map_choice_t choice;
    do
    {
        characters = getline_rinderud(buffer, &bufsize);
        if (characters == 0)
        {
            continue;
        }

        choice.id[0] = buffer[0];
        choice.id[1] = buffer[1];
        choice.id[2] = buffer[2];

        choice.left[0] = buffer[0 + 7];
        choice.left[1] = buffer[1 + 7];
        choice.left[2] = buffer[2 + 7];

        choice.right[0] = buffer[0 + 12];
        choice.right[1] = buffer[1 + 12];
        choice.right[2] = buffer[2 + 12];

        choices[nbr_choices] = choice;
        nbr_choices++;
    } while (characters > 0 && nbr_choices < choices_size);

    printf("%zu choices read\n", nbr_choices);
    printf("Here are the first 3:\n");
    print_choice(choices[0]);
    print_choice(choices[1]);
    print_choice(choices[2]);
    printf("and the last 2:\n");
    print_choice(choices[nbr_choices - 2]);
    print_choice(choices[nbr_choices - 1]);

    printf("Following the instructions\n");
    i = 0;
    j = 0;
    curr_id[0] = 'A';
    curr_id[1] = 'A';
    curr_id[2] = 'A';
    while (!(curr_id[0] == 'Z' && curr_id[1] == 'Z' && curr_id[2] == 'Z'))
    {
        if (!(i < dir_size-1))
        {
            i = 0;
        }

        choice = find_choice(curr_id, nbr_choices, choices);
        print_choice(choice);
        printf("i = %zu\n", i);
        printf("direction = %c\n", directions[i]);
        switch (directions[i])
        {
        case 'L':
            curr_id[0] = choice.left[0];
            curr_id[1] = choice.left[1];
            curr_id[2] = choice.left[2];
            break;
        case 'R':
            curr_id[0] = choice.right[0];
            curr_id[1] = choice.right[1];
            curr_id[2] = choice.right[2];
            break;

        default:
            printf("Direction is not read correctly\n");
            break;
        }

        j++;
        i++;
    }

    printf("Found after %zu (ZZZ):\n", j);
    print_choice(choice);

    // Frees
    free(choices);
    free(directions);
    free(buffer);

    return 0;
}
