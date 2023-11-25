#include <stdio.h>
#include <ctype.h>

int main(void)
{
    unsigned int max, elf, snack;
    int c;
    max = 0;
    elf = 0;
    snack = 0;

    while ((c = getchar()) != EOF)
    {
        if (isdigit(c))
        {
            snack = snack * 10 + (c - '0');
        }
        else if (c == '\n')
        {
            if (snack == 0)
            {
                elf = 0;
            }

            elf += snack;
            snack = 0;

            if (elf > max)
            {
                max = elf;
            }
        }
    }

    printf("%d", max);

    return 0;
}
