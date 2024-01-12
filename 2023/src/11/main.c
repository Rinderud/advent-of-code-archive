#include <stdlib.h>
#include <stdio.h>
#define DEBUG
#define SIZEOFTHEUNIVERSE 10 // 450

void debug(char ch[])
{
#ifdef DEBUG
    printf("%s", ch);
#endif
}

typedef struct
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
    /*
    1. allocate array of points
    2. read input and create points
    */
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

void expand_map(void)
{
    debug("expand_map\n");
    /*
    1. find edges (largest x and y)
    2. add one to the points affected walking from the bottom
    3. sort by x
    4. add one to the points affected walking from the right
    */
}

int manhattan_dist(point_t a, point_t b)
{
    int sum;
    sum = abs(a.x - b.x) + abs(a.y - b.y);
    return sum;
}

int main(void)
{
    int nbrgal;
    point_t *map;

    struct arrsiz retarr = read_in_map();
    map = retarr.arr;
    nbrgal = retarr.size;

    printf("Found %d galaxies on the map\n", nbrgal);
    pripoi(map[0]);
    pripoi(map[1]);
    pripoi(map[2]);
    pripoi(map[nbrgal - 1]);

    free(map);
    return 0;
}
