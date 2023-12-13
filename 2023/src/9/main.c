#include <stdio.h>
#include <ctype.h>

typedef struct
{
    size_t i;
    char c;
} size_char_t;

size_char_t read_numbers(long unsigned *nums, size_t N)
{
    size_t i;
    int c;
    long unsigned new;

    new = 0;
    c = '?';
    i = 0;
    while (c != '\n' && c != '@' && i < N)
    {
        c = getchar();
        switch (c)
        {
        case EOF:
            printf("EOF\n");
            c = '@';
        case '\n':
        case ' ':
            nums[i] = new;
            i++;
            new = 0;
            break;

        default:
            if (isdigit(c))
            {
                new *= 10;
                new += c - '0';
            }
            break;
        }
    }

    if (i > 0)
    {
        printf("last num = %lu\n", nums[i - 1]);
    }

    size_char_t ret = {i, c};
    return ret;
}

int main(void)
{
    size_t cols;
    size_t N = 25;
    long unsigned *nums;

    nums = calloc(N, sizeof(*nums));

    size_char_t ret = {0, '?'};
    while (ret.c != '@')
    {
        ret = read_numbers(nums, N);
        cols = ret.i;
        printf("i:%zu c:%c\n", ret.i, ret.c);
    }

    printf("Read %zu numbers\n", cols);

    //! Frees
    free(nums);

    return 0;
}
