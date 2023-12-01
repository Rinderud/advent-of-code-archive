#include <stdio.h>
#include <ctype.h>

#define N 1000

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

int check_with_offset(int stack[N], int offset)
{
    int new_stack[N];
    for (size_t i = 0; i < N - offset; i++)
    {
        new_stack[i] = stack[i + offset];
    }
    return word_to_number(new_stack);
}

void print_stack(int stack[N], int j)
{
    for (size_t i = 0; i < j; i++)
    {
        if (stack[i] == stack[N - 2])
        {
            printf("\n");
            return;
        }

        printf("%c ", stack[i]);
    }
    printf("\n");
}

int main(void)
{
    int c, a, b, sum;

    int empty[N];
    int prevs[N];
    int i;

    a = -1;
    b = -1;
    sum = 0;

    i = 0;
    while ((c = getchar()) != EOF)
    {
        if (isdigit(c))
        {
            if (a == -1)
            {
                a = c - '0';
            }
            else
            {
                b = c - '0';
            }
        }
        else if (c == '\n')
        {
            if (b == -1)
            {
                b = a;
            }

            sum += a * 10 + b;

            printf("sum:%d, a=%d, b=%d\n", sum, a, b);

            // print_stack(prevs, i);
            //  reset
            a = -1;
            b = -1;
            i = 0;
            for (size_t j = 0; j < N; j++)
            {
                prevs[j] = empty[j];
            }
        }
        else
        {
            switch (c)
            {
            case 'o':
            case 't':
            case 'w':
            case 'h':
            case 'r':
            case 'e':
            case 'u':
            case 'f':
            case 'i':
            case 'v':
            case 's':
            case 'x':
            case 'n':
            case 'g':
                break;

            default:
                continue;
            }

            if (i == N-1)
            {
                prevs[0] = prevs[i];
                i = 0;
            }
            // printf("%c", c);
            prevs[i] = c;
            i++;

            if (a == 8)
            {
                //print_stack(prevs, i);
            }

            for (size_t k = 0; k < N - 2; k++)
            {
                int num = check_with_offset(prevs, k);
                if (num != 0)
                {
                    // printf("::num:%d\n", num);
                    prevs[i-2] = empty[i-2];
                    //i = 0;
                    for (size_t j = 0; j < N; j++)
                    {
                        //prevs[j] = empty[j];
                    }

                    if (a == -1)
                    {
                        a = num;
                    }
                    else
                    {
                        b = num;
                    }
                }
            }
        }
    }

    for (size_t k = 0; k < N - 2; k++)
    {
        int num = check_with_offset(prevs, k);
        if (num != 0)
        {
            // printf("::num:%d\n", num);
            //i = 0;
            for (size_t j = 0; j < N; j++)
            {
                //prevs[j] = empty[j];
            }

            if (a == -1)
            {
                a = num;
            }
            else
            {
                b = num;
            }
        }
    }

    if (b == -1)
    {
        b = a;
    }

    sum += a * 10 + b;

    printf("sum:%d, a=%d, b=%d\n", sum, a, b);
    printf("%d", sum);

    return 0;
}
