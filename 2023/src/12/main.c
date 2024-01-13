#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum condition_t
{
    GOOD,
    BAD,
    UNKNOWN,
} condition_t;

typedef struct condition_record_t
{
    condition_t *conditions;
    unsigned int *replication;
    size_t N[2];
} condition_record_t;

typedef struct arr_siz_t
{
    void *arr;
    size_t N;
} arr_siz_t;

void destroy_condition_record(condition_record_t *condition_record)
{
    free(condition_record->conditions);
    free(condition_record->replication);
    free(condition_record);
}

/**
 * Create an array of conditions read from stdin.
 * Return the number of allocated elements and the array.
 */
arr_siz_t read_conditions(void)
{
    size_t i, N;
    char ch;
    condition_t *conditions;
    condition_t cond;

    N = 1;
    conditions = malloc(N * sizeof(*conditions));

    i = 0;
    while ((ch = getchar()) != ' ')
    {
        if (i >= N)
        {
            N *= 2; // Double the available space
            conditions = realloc(conditions, N * sizeof(*conditions));
        }

        switch (ch)
        {
        case '.':
            cond = GOOD;
            break;
        case '#':
            cond = BAD;
            break;
        case '?':
            cond = UNKNOWN;
            break;

        default:
            printf("The read char was not as expected!\n");
            cond = UNKNOWN;
            break;
        }

        conditions[i] = cond;
        i++;
    }

    N = i;
    conditions = realloc(conditions, N * sizeof(*conditions)); //? Does this work?

    return (arr_siz_t){.arr = conditions, .N = N};
}

/**
 * Create an array of replication numbers read from stdin.
 * Return the number of allocated elements and the array.
 */
arr_siz_t read_replications(void)
{
    size_t i, N;
    char ch;
    unsigned int *replications;
    unsigned int number;

    N = 10;
    replications = malloc(N * sizeof(*replications));

    i = 0;
    ch = getchar();
    number = 0;
    while (ch != '\n' && ch != EOF)
    {
        if (i >= N)
        {
            N *= 2; // Double the available space
            replications = realloc(replications, N * sizeof(*replications));
        }

        if (isdigit(ch))
        {
            number = 10 * number + ch - '0';
        }
        else if (ch == ',')
        {
            replications[i] = number;
            i++;
            number = 0;
        }
        ch = getchar();
    }
    if (number != 0)
    {
        replications[i] = number;
        i++;
    }

    N = i;
    replications = realloc(replications, N * sizeof(*replications)); //? Does this work?

    return (arr_siz_t){.arr = replications, .N = N};
}

condition_record_t *read_record(void)
{
    size_t N1, N2;
    arr_siz_t ret;
    condition_t *conditions;
    unsigned int *replications;
    condition_record_t *record;

    ret = read_conditions();
    N1 = ret.N;
    conditions = ret.arr;

    ret = read_replications();
    N2 = ret.N;
    replications = ret.arr;

    record = malloc(sizeof(*record));
    record->conditions = conditions;
    record->replication = replications;
    record->N[0] = N1;
    record->N[1] = N2;

    return record;
}
int main(void)
{
    condition_record_t *record;

    for (size_t i = 0; i < 5; i++)
    {
        record = read_record();

        destroy_condition_record(record);
    }

    return 0;
}
