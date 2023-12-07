#include <stdio.h>

#define HAND_SIZE 5
#define SIZE 1000

typedef struct
{
    int cards[HAND_SIZE];
    int bid;
} hand_t;

int cmp_hand(const void *a, const void *b)
{
    const hand_t *h1 = a;
    const hand_t *h2 = b;

    int result, i;
    result = 0;
    i = 0;
    while (result == 0)
    {
        result = (h1->cards[i] > h2->cards[i]);
        i++;
    }
    return result;
}

int part1()
{
    hand_t *hands;
    int nbr_hands, in, temp;
    nbr_hands = SIZE;
    hands = calloc(nbr_hands, sizeof(hand_t));
    in = '?';
    while (in != EOF)
    {
        in = getchar(); 
        switch (in)
        {
        case ' ':
            
            break;
        
        case '\n':
        case EOF:
            break;
        default:
            if (isdigit(in))
            {
                temp *= 10;
                temp += in -'0';
            }
            
            break;
        }
    }

    // Sort array
    qsort(hands, nbr_hands, sizeof(hand_t), cmp_hand);
}

int main(void)
{
    int result1 = part1();
    return 0;
}
