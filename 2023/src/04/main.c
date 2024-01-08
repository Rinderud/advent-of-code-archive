#include <stdio.h>
#include <ctype.h>

#define SIZE 10
#define BIG_SIZE 200
#define INI 0
#define COR 1
#define INP 2

int in, num, sum, id, nbr_match, score;
int correct[SIZE];
int index;

int calc_score()
{
    if (nbr_match == 0)
    {
        return 0;
    }
    return 1 << (nbr_match - 1);
}

void reset(void)
{
    num = 0;
    nbr_match = 0;
    score = 0;
    for (int i = 0; i < SIZE; i++)
    {
        correct[i] = -1;
    }
    index = 0;
}

int push(int a)
{
    if ((index < SIZE) && (index >= 0))
    {
        correct[index] = a;
        index++;
        return 1;
    }
    else
    {
        printf("when pushing %d\n%d, index out of bounds\n", a, index);
        return 0;
    }
}

int match(int a)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (a == correct[i])
        {
            return 1;
        }
    }
    return 0;
}

void part1(void)
{
    int state = INI;
    reset();
    sum = 0;
    id = 1;

    while ((in = getchar()) != EOF)
    {
        switch (state)
        {
        case INI:
            if (in == ':')
            {
                printf("Card %d: ", id);
                id++;
                state = COR;
            }
            break;
        case COR:
            if (isdigit(in))
            {
                num *= 10;
                num += in - '0';
            }
            else if (in == ' ')
            {
                if (num != 0)
                {
                    push(num);
                    num = 0;
                }
            }
            else if (in == '|')
            {
                state = INP;
            }

            break;
        case INP:
            if (isdigit(in))
            {
                num *= 10;
                num += in - '0';
            }
            else if (in == ' ')
            {
                if (match(num))
                {
                    nbr_match++;
                    printf("%d, ", num);
                }

                num = 0;
            }
            else if (in == '\n')
            {
                if (match(num))
                {
                    nbr_match++;
                    printf("%d, ", num);
                }

                score = calc_score();
                sum += score;
                printf("score=%d\n", score);
                reset();
                state = INI;
            }

            break;

        default:
            break;
        }
    }
    if (match(num))
    {
        nbr_match++;
        printf("%d, ", num);
    }

    score = calc_score();
    sum += score;
    printf("score=%d\n", score);

    printf("Sum = %d", sum);
}

int nbr_correct[BIG_SIZE];

void calc_sum()
{
    int nbr_cards[BIG_SIZE];
    int i, j;
    for (i = 1; i <= id; i++)
    {
        nbr_cards[i] = 1;
    }

    for (i = 1; i <= id; i++)
    {
        for (j = 0; j < nbr_correct[i]; j++)
        {
            nbr_cards[i + j + 1] += nbr_cards[i];
        }
        printf("Card %d: %d\n", i-1, nbr_cards[i]);
    }

    sum = -1;
    for (i = 1; i <= id; i++)
    {
        sum += nbr_cards[i];
    }
}

void part2(void)
{
    int state = INI;
    reset();
    sum = 0;
    id = 1;

    while ((in = getchar()) != EOF)
    {
        switch (state)
        {
        case INI:
            if (in == ':')
            {
                id++;
                state = COR;
            }
            break;
        case COR:
            if (isdigit(in))
            {
                num *= 10;
                num += in - '0';
            }
            else if (in == ' ')
            {
                if (num != 0)
                {
                    push(num);
                    num = 0;
                }
            }
            else if (in == '|')
            {
                state = INP;
            }

            break;
        case INP:
            if (isdigit(in))
            {
                num *= 10;
                num += in - '0';
            }
            else if (in == ' ')
            {
                if (match(num))
                {
                    nbr_match++;
                }

                num = 0;
            }
            else if (in == '\n')
            {
                if (match(num))
                {
                    nbr_match++;
                }
                nbr_correct[id] = nbr_match;
                reset();
                state = INI;
            }

            break;

        default:
            break;
        }
    }
    if (match(num))
    {
        nbr_match++;
    }
    nbr_correct[id] = nbr_match;

    calc_sum();
    printf("Sum = %d", sum);
}

int main(void)
{
    part2();
    return 0;
}
