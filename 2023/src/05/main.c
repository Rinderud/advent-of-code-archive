#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 20
#define BIGSIZE 42

typedef struct
{
    long dest_strt;
    long src_strt;
    long length;
} range_t;

range_t create_range(long dest, long src, long l)
{
    range_t range;
    range.dest_strt = dest;
    range.src_strt = src;
    range.length = l;
    return range;
}

typedef struct
{
    long nbr_ranges;
    range_t ranges[BIGSIZE];
} range_list_t;

range_list_t create_range_list()
{
    range_list_t ranges;
    ranges.nbr_ranges = 0;
    return ranges;
}

typedef enum
{
    seed,
    soil,
    fert,
    water,
    light,
    temp,
    humid,
    location,
    init
} state_t;

state_t state;
range_list_t seed_soil, soil_fert, fert_water, water_light, light_temp, temp_humid, humid_location;
long seeds[SIZE];
long seed_index;

void push_seed(long seed)
{
    if (seed_index >= SIZE)
    {
        printf("Failed to push seed, index out of bounds\n");
        return;
    }
    seeds[seed_index] = seed;
    seed_index++;
}

void push_range(range_list_t *ranges, range_t range)
{
    if (ranges->nbr_ranges >= BIGSIZE)
    {
        printf("Failed to push seed, index out of bounds\n");
        return;
    }
    ranges->ranges[ranges->nbr_ranges] = range;
    ranges->nbr_ranges++;
}

long src_dest_converter(range_list_t ranges, long src)
{
    range_t range;
    long dx, dest;
    for (long i = 0; i < ranges.nbr_ranges; i++)
    {
        range = ranges.ranges[i];
        if ((range.src_strt <= src) && (src < range.src_strt + range.length))
        {
            dx = src - range.src_strt;
            dest = range.dest_strt + dx;
            return dest;
        }
    }
    return src;
}

long long recursive_src_dest(long long se)
{
    long long so, fe, wa, li, te, hu, lo;
    so = src_dest_converter(seed_soil, se);
    fe = src_dest_converter(soil_fert, so);
    wa = src_dest_converter(fert_water, fe);
    li = src_dest_converter(water_light, wa);
    te = src_dest_converter(light_temp, li);
    hu = src_dest_converter(temp_humid, te);
    lo = src_dest_converter(humid_location, hu);

    // printf("Seed %ld soil %ld fertilizer %ld water %ld light %ld temperature %ld humidity %ld location %ld\n", se, so, fe, wa, li, te, hu, lo);
    return lo;
}

long part_1()
{
    long character, src, dst, l, buff;
    range_t curr_range;
    range_list_t *curr_list;
    state_t next_state;

    curr_list = NULL;
    seed_index = 0;
    buff = -1;
    src = -1;
    dst = -1;
    l = -1;
    state = init;

    while ((character = getchar()) != EOF)
    {
        switch (state)
        {
        case seed: // : 79 14 55 13
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if (character == ' ' && buff != -1)
            {
                push_seed(buff);
                buff = -1;
            }
            next_state = soil;
            break;
        case soil: /*:
                       50 98 2
                       52 50 48 */
            curr_list = &seed_soil;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = fert;
            break;
        case fert:
            curr_list = &soil_fert;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = water;
            break;
        case water:
            curr_list = &fert_water;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = light;
            break;
        case light:
            curr_list = &water_light;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = temp;
            break;
        case temp:
            curr_list = &light_temp;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = humid;
            break;
        case humid:
            curr_list = &temp_humid;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = location;
            break;
        case location:
            curr_list = &humid_location;
            if (isdigit(character))
            {
                if (buff == -1)
                {
                    buff = 0;
                }
                buff *= 10;
                buff += character - '0';
            }
            else if ((character == ' ' || character == '\n') && buff != -1)
            {
                if (dst == -1)
                {
                    dst = buff;
                }
                else if (src == -1)
                {
                    src = buff;
                }
                else if (l == -1)
                {
                    l = buff;
                }
                buff = -1;
            }
            next_state = init;
            break;

        case init:
        default:
            next_state = seed;
            break;
        }

        if (character == '\n')
        {
            if (l == -1)
            {
                continue;
            }
            curr_range = create_range(dst, src, l);
            push_range(curr_list, curr_range);
            buff = -1;
            src = -1;
            dst = -1;
            l = -1;
        }
        else if (character == ':')
        {
            char result[20];
            switch (next_state)
            {
            case seed:
                strcpy(result, "seed");
                break;
            case soil:
                strcpy(result, "soil");
                break;
            case fert:
                strcpy(result, "fert");
                break;
            case water:
                strcpy(result, "water");
                break;
            case light:
                strcpy(result, "light");
                break;
            case temp:
                strcpy(result, "temp");
                break;
            case humid:
                strcpy(result, "humid");
                break;
            case location:
                strcpy(result, "location");
                break;
            case init:
                strcpy(result, "init");
                break;
            default:
                strcpy(result, "Invalid");
                break;
            }
            printf("Going to state: %s\n", result);
            state = next_state;
            // "reset"
            buff = -1;
            src = -1;
            dst = -1;
            l = -1;
        }
    }

    long min = __LONG_MAX__;
    long curr;
    for (size_t i = 0; i < seed_index; i++)
    {
        curr = recursive_src_dest(seeds[i]);
        if (curr < min)
        {
            min = curr;
        }
    }
    return min;
}

long long part_2()
{
    long long curr, x, dx;
    long long min = __LONG_LONG_MAX__;
    for (int i = 0; i < seed_index - 1; i += 2)
    {
        x = seeds[i];
        dx = seeds[i + 1];

        for (long long j = x; j < x + dx; j++)
        {
            curr = recursive_src_dest(j);

            if (curr < min)
            {
                min = curr;
                printf("min: %lld\n", min);
            }
        }
    }
    return min;
}

/*
long long part_2_electric_bogaloo()
{
    long long curr, x1, dx, x2;
    long long min = __LONG_LONG_MAX__;
    for (int i = 0; i < seed_index - 1; i += 2)
    {
        //TODO: make it not brute forces that Jonas would hate.
    }
    return min;
}
*/

int main(void)
{
    long ans1 = part_1();
    printf("Lowest location = %ld\n", ans1);

    long long ans2 = part_2();
    printf("Lowest location part 2 = %lld", ans2);

    return 0;
}
