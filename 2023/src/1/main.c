#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int c, a, b, sum;

    a = -1;
    b = -1;
    sum = 0;

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

            // reset
            a = -1;
            b = -1;
        }
    }

    if (b == -1)
    {
        b = a;
    }

    sum += a * 10 + b;

    printf("%d", sum);

    return 0;
}
