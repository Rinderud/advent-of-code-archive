#include <stdlib.h>
#include <stdio.h>
// #define DEBUG
#define SIZEOFTHEUNIVERSE /*10*/ 450

void debug(char ch[])
{
#ifdef DEBUG
    printf("%s", ch);
#endif
}

typedef struct point_t
{
    int x;
    int y;
} point_t;

struct arrsiz
{
    int size;
    point_t *arr;
};

void pripoi(point_t p)
{
    printf("(%d,%d)\n", p.x, p.y);
}

struct arrsiz read_in_map(void)
{
    debug("read_in_map\n");
    int i, x, y, ch;
    point_t *map;

    map = calloc(SIZEOFTHEUNIVERSE, sizeof(*map));

    i = x = y = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            x = 0;
            y++;
            continue;
        }
        if (ch == '#')
        {
            if (i >= SIZEOFTHEUNIVERSE)
            {
                free(map);
                perror("Index out of bounds when trying to create a new point");
                exit(1);
            }
            map[i] = (point_t){.x = x, .y = y};
            i++;
        }
        x++;
    }

    return (struct arrsiz){.arr = map, .size = i};
}

int cmp_x(const void *a, const void *b)
{
    const point_t *p1 = a;
    const point_t *p2 = b;

    return (p1->x > p2->x);
}

void expand_map(point_t *map, int n)
{
    debug("expand_map\n");
    int i, j, previous, current;

    previous = map[n - 1].y;
    for (i = n - 2; i >= 0; i--)
    {
        current = map[i].y;
        if (previous - current > 1)
        {
            for (j = i + 1; j < n; j++)
            {
                map[j].y += previous - current - 1;
            }
        }
        previous = current;
    }

    qsort(map, n, sizeof(*map), cmp_x);

    previous = map[n - 1].x;
    for (i = n - 2; i >= 0; i--)
    {
        current = map[i].x;
        if (previous - current > 1)
        {
            for (j = i + 1; j < n; j++)
            {
                map[j].x += previous - current - 1;
            }
        }
        previous = current;
    }
}

int manhattan_dist(point_t a, point_t b)
{
    int sum;
    sum = abs(a.x - b.x) + abs(a.y - b.y);
    return sum;
}

int sum_distances(point_t *map, int n)
{
    int sum = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i + 1; j < n; j++)
        {
            sum += manhattan_dist(map[i], map[j]);
        }
    }
    return sum;
}

int main(void)
{
    int nbrgal;
    int sum;
    point_t *map;

    struct arrsiz retarr = read_in_map();
    map = retarr.arr;
    nbrgal = retarr.size;

    printf("Found %d galaxies on the map\n", nbrgal);

    expand_map(map, nbrgal);

    sum = sum_distances(map, nbrgal);
    printf("Total = %d\n", sum);

    // Frees
    free(map);
    return 0;
}
