#include <stdio.h>
#include <ctype.h>

#define N 100

int bfr[N];
int a, b, sum, bi;

void reset_buffer()
{
    a = -1;
    b = -1;
    bi = 0;
    for (size_t i = 0; i < N; i++)
    {
        bfr[i] = 1;
    }
}

void push(int in)
{
    bfr[bi] = in;
    bi++;
}

void set_ab(int num)
{
    if (a == -1) // First time a digit comes
    {
        a = num;
    }
    else
    {
        b = num;
    }
}

void wrap_buffer()
{
    // Save the last few letters
    bfr[0] = bfr[bi - 4];
    bfr[1] = bfr[bi - 3];
    bfr[2] = bfr[bi - 2];
    bfr[3] = bfr[bi - 1];
    bfr[4] = bfr[bi];

    bi = 0;
}

void add_to_sum()
{
    if (b == -1) // If b was never initialized
    {
        b = a; // Assume b = a
    }

    sum += a * 10 + b;
}

int is_this(int stack[N], char truth[N])
{
    for (size_t i = 0; i < N; i++)
    {
        if (truth[i] == truth[N - 2]) // End of the string
        {
            return 1;
        }

        if (stack[i] != truth[i]) // Does not match
        {
            return 0;
        }
    }

    // error
    return 0;
}

int word_to_number(int stack[N])
{
    char one[N] = "one";
    char two[N] = "two";
    char three[N] = "three";
    char four[N] = "four";
    char five[N] = "five";
    char six[N] = "six";
    char seven[N] = "seven";
    char eight[N] = "eight";
    char nine[N] = "nine";

    if (is_this(stack, one))
        return 1;
    if (is_this(stack, two))
        return 2;
    if (is_this(stack, three))
        return 3;
    if (is_this(stack, four))
        return 4;
    if (is_this(stack, five))
        return 5;
    if (is_this(stack, six))
        return 6;
    if (is_this(stack, seven))
        return 7;
    if (is_this(stack, eight))
        return 8;
    if (is_this(stack, nine))
        return 9;

    return 0;
}

int check_with_offset(int offset)
{
    int stack[N];
    for (size_t i = 0; i < N - offset; i++)
    {
        stack[i] = bfr[i + offset];
    }
    return word_to_number(stack);
}

void check_set_buffer()
{
    for (size_t i = 0; i < N - 2; i++)
    {
        int num = check_with_offset(i);
        if (num != 0) // If it was a digit
        {
            set_ab(num);
            bfr[bi - 2] = 1; // Remove part of found digit word
        }
    }
}

int main(void)
{
    int c;

    reset_buffer();
    sum = 0;

    while ((c = getchar()) != EOF)
    {
        if (isdigit(c))
        {
            set_ab(c - '0');
        }
        else if (c == '\n') // Line is over, time to combine
        {
            add_to_sum();
            reset_buffer();
        }
        else
        {
            switch (c) // If the character is not of interest, don't save it
            {
            case 'o':
            case 'n':
            case 'e':
            case 't':
            case 'w':
            case 'h':
            case 'r':
            case 'f':
            case 'u':
            case 'i':
            case 'v':
            case 's':
            case 'x':
            case 'g':
                break;

            default:
                continue;
            }

            if (bi == N - 1) // End of the stack, should not happen but just in case
            {
                wrap_buffer();
            }
            push(c);
            check_set_buffer();
        }
    }
    check_set_buffer();
    add_to_sum();

    printf("%d", sum);

    return 0;
}
