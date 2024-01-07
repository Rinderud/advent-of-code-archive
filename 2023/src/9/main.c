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
            // printf("EOF\n");
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

    /*
    if (i > 0)
    {
        printf("last num = %lu\n", nums[i - 1]);
    }
    */

    size_char_t ret = {i, c};
    return ret;
}

long unsigned sum(long unsigned *nums, size_t cols)
{
    long unsigned sum = 0;
    for (size_t i = 0; i < cols; i++)
    {
        sum += nums[i];
    }
    return sum;
}

long unsigned recur(long unsigned *nums, size_t cols)
{
    size_t i;
    /*for (i = 0; i < cols; i++)
    {
        printf("%lu ", nums[i]);
    }
    printf("\n");
*/
    if (cols <= 1 || sum(nums, cols) == 0)
    {
        // printf("returning\n\n");
        return 0;
    }

    long unsigned *newrow;
    long unsigned a, b, diff;

    newrow = calloc((cols - 1), sizeof(*newrow));

    a = nums[0];
    for (i = 1; i < cols; i++)
    {
        b = a;
        a = nums[i];
        diff = a - b;
        // printf("%lu - %lu = %lu\n", a, b, diff);

        newrow[i - 1] = diff;
    }

    long unsigned newdiff, newnewdiff;
    newdiff = recur(newrow, cols - 1);
    newnewdiff = newdiff + nums[cols - 1];

    //printf("%lu + %lu = %lu\n", nums[cols - 1], newdiff, newnewdiff);

    free(newrow);
    return newnewdiff;
}

int main(void)
{
    size_t cols, N, i;
    long unsigned sum, newdiff;
    long unsigned *nums;

    N = 25;
    nums = calloc(N, sizeof(*nums));

    size_char_t ret = {0, '?'};
    sum = 0;
    i = 0;
    while (ret.c != '@')
    {
        ret = read_numbers(nums, N);
        cols = ret.i;
        // printf("%lu\n", nums[cols-1]);

        newdiff = recur(nums, cols);
        printf("%zu: %lu\n",i, newdiff);
        sum += newdiff;
        i++;
    }

    printf("total = %lu", sum);

    //! Frees
    free(nums);

    return 0;
}
