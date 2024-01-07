#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    size_t i;
    char c;
} size_char_t;

/**
 * Returns a size_char struct with the last char read and the number of read numbers.
 * The read numbers are added to the nums array.
*/
size_char_t read_numbers(long signed *nums, size_t N)
{
    size_t i;
    int c, sign;
    long signed new;

    new = 0;
    sign = 1;
    c = '?';
    i = 0;
    while (c != '\n' && c != '@' && i < N)
    {
        c = getchar();
        switch (c)
        {
        case EOF:
            c = '@';
        case '\n':
        case ' ':
            nums[i] = new *sign;
            i++;
            new = 0;
            sign = 1;
            break;
        case '-':
            sign = -1;
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

    size_char_t ret = {i, c};
    return ret;
}

/**
 * Return the manhattan distance of the nums arrays first cols elements.
*/
long signed mandist(long signed *nums, size_t cols)
{
    long signed sum = 0;
    for (size_t i = 0; i < cols; i++)
    {
        sum += abs(nums[i]);
    }
    return sum;
}

/**
 * Recursive function that returns the new predicted value as per the AOC task.
*/
long signed recur(long signed *nums, size_t cols)
{
    if (cols <= 1 || mandist(nums, cols) == 0)
    {
        return 0;
    }

    size_t i;
    long signed *newrow;
    long signed a, b, diff, newdiff, newnewdiff;

    newrow = calloc((cols - 1), sizeof(*newrow));

    a = nums[0];
    for (i = 1; i < cols; i++)
    {
        b = a;
        a = nums[i];
        diff = a - b;
        newrow[i - 1] = diff;
    }

    newdiff = recur(newrow, cols - 1);
    newnewdiff = newdiff + nums[cols - 1];

    free(newrow);
    return newnewdiff;
}

int main(void)
{
    size_t N, i;
    long signed sum, newdiff;
    long signed *nums;
    size_char_t ret;

    N = 25;
    nums = calloc(N, sizeof(*nums));

    ret = (size_char_t){0, '?'};
    sum = 0;
    i = 0;
    while (ret.c != '@')
    {
        ret = read_numbers(nums, N); // Read in a row
        newdiff = recur(nums, ret.i);
        printf("%zu: %ld\n", i, newdiff);
        sum += newdiff;
        i++;
    }

    printf("total = %ld", sum);

    //! Frees
    free(nums);

    return 0;
}
