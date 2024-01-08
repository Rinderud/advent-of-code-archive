#include <stdio.h>
#include <ctype.h>

enum state_t
{
    comma,
    digit,
    rgb
};

unsigned int buff, red, green, blue, id, sum;
unsigned int minimum[3];
enum state_t state;

void reset_colors()
{
    red = 0;
    green = 0;
    blue = 0;
}

void reset_numbers()
{
    buff = 0;
}

int check_constraint(unsigned int con[3])
{
    int truth = 0;
    truth += red > con[0];
    // printf("red: %d\n", truth);
    truth += green > con[1];
    // printf("green: %d\n", truth);
    truth += blue > con[2];
    // printf("blue: %d\n", truth);
    return (truth == 0);
}

unsigned int part1(void)
{

    unsigned int constraint[3];
    constraint[0] = 12;
    constraint[1] = 13;
    constraint[2] = 14;
    /**
     * Color is {red, green, blue}
     * 1. Find id
     * 2. find number and then r,g,b
     * 3. semicolon resets which colors we have seen
     *      but not the numbers
     * 4. new-line resets everything
     */
    int character, result;
    sum = 0;
    id = 1;
    state = comma;

    while ((character = getchar()) != EOF)
    {
        // printf("(%d)::(%d,%d,%d)\n", id, red, green, blue);
        switch (state)
        {
        case comma:
            // printf("State: comma\n");
            if (character != ':')
            {
                continue;
            }
            reset_colors();
            reset_numbers();
            state = digit;
            break;

        case digit:
            // printf("State: digit\n");
            if (isdigit(character))
            {
                buff *= 10;
                buff += character - '0';
            }
            switch (character)
            {
            case ';':
                result = check_constraint(constraint);
                if (!result)
                {
                    state = comma;
                    printf("Game %d: %d\n", id, result);
                    id++;
                }
                reset_colors();
                reset_numbers();
                continue;

            case '\n':
                result = check_constraint(constraint);
                if (result)
                {
                    sum += id;
                }
                reset_colors();
                reset_numbers();
                state = comma;

                printf("Game %d: %d\n", id, result);
                id++;
                continue;

            case ' ':
                if (buff != 0)
                {
                    state = rgb;
                }
                break;

            default:
                break;
            }

            continue;

        case rgb:
            // printf("State: rgb\n");
            switch (character)
            {
            case 'r':
                red += buff;
                break;

            case 'g':
                green += buff;
                break;

            case 'b':
                blue += buff;
                break;

            default:
                continue;
            }
            state = digit;
            reset_numbers(); //?
            break;

        default:
            break;
        }
    }
    if (state != comma)
    {

        result = check_constraint(constraint); // TODO: DRY
        if (result)
        {
            sum += id;
        }
        reset_colors();
        reset_numbers();
        state = comma;

        printf("Game %d: %d\n", id, result);
    }

    return sum;
}

void check_minimum()
{
    if (red > minimum[0])
    {
        minimum[0] = red;
    }
    if (green > minimum[1])
    {
        minimum[1] = green;
    }
    if (blue > minimum[2])
    {
        minimum[2] = blue;
    }
}

void reset_minimum()
{
    minimum[0] = 0;
    minimum[1] = 0;
    minimum[2] = 0;
}

unsigned int part2(void)
{
    int character;
    reset_minimum();
    sum = 0;
    id = 1;
    state = comma;

    while ((character = getchar()) != EOF)
    {
        // printf("(%d)::(%d,%d,%d)\n", id, red, green, blue);
        switch (state)
        {
        case comma:
            // printf("State: comma\n");
            if (character != ':')
            {
                continue;
            }
            reset_colors();
            reset_numbers();
            state = digit;
            break;

        case digit:
            // printf("State: digit\n");
            if (isdigit(character))
            {
                buff *= 10;
                buff += character - '0';
            }
            switch (character)
            {
            case ';':
                check_minimum();
                reset_colors();
                reset_numbers();
                continue;

            case '\n':
                check_minimum();
                //printf("(%d,%d,%d)\n", minimum[0],minimum[1],minimum[2]);
                unsigned int power = minimum[0] * minimum[1] * minimum[2];
                sum += power;
                reset_colors();
                reset_numbers();
                reset_minimum();
                state = comma;
                printf("Game %d: %d\n", id, power);
                id++;
                continue;
            case ' ':
                if (buff != 0)
                {
                    state = rgb;
                }
                break;

            default:
                break;
            }

            continue;

        case rgb:
            // printf("State: rgb\n");
            switch (character)
            {
            case 'r':
                red += buff;
                break;

            case 'g':
                green += buff;
                break;

            case 'b':
                blue += buff;
                break;

            default:
                continue;
            }
            state = digit;
            reset_numbers(); //?
            break;

        default:
            break;
        }
    }
    check_minimum();
                unsigned int power = minimum[0] * minimum[1] * minimum[2];
                sum += power;
                reset_colors();
                reset_numbers();
                state = comma;
                printf("Game %d: %d\n", id, power);

    return sum;
}

int main(void)
{
    unsigned int result;
    // result = part1();
    result = part2();

    printf("%d", result);
    return 0;
}
