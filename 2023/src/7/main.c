#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define HAND_SIZE 5
#define CARDS 14
#define SIZE 1000

typedef struct
{
    int cards[HAND_SIZE];
    int bid;
} hand_t;

typedef struct
{
    int rank;
    int value;
} combo_t;

combo_t find_combos(hand_t hand)
{
    int i, j;
    int card, matches;
    combo_t *combos;
    combo_t max_combo;
    combo_t combo;

    combos = calloc(CARDS+1, sizeof(combo_t));
    max_combo.rank = 0;
    max_combo.value = 0;

    for (i = 2; i <= CARDS; i++)
    {
        matches = 0;
        for (j = 0; j < HAND_SIZE; j++)
        {
            card = hand.cards[j];
            if (card == i)
            {
                matches++;
            }
        }
        if (matches >= max_combo.rank)
        {
            max_combo.rank = matches;
            max_combo.value = i;
        }

        combos[i].rank = matches;
        combos[i].value = i;
    }

    if (max_combo.rank >= 4)
    {
        combo = max_combo;
        combo.rank += 2; // Accounting for fh and 2 pair
    }
    else if (max_combo.rank == 3)
    {
        combo.value = max_combo.value;
        combo.rank = 3 + 1; // Accounting for 2 pair
        for (i = CARDS; i >= 0; i--)
        {
            if (combos[i].rank == 2 && combo.rank != 5)
            {
                combo.rank = 5; // Full house
            }
        }
    }
    else if (max_combo.rank == 2)
    {
        combo = max_combo;
        for (i = CARDS; i >= 0; i--)
        {
            if (combos[i].rank == 2 && combos[i].value != combo.value)
            {
                combo.rank = 2 + 1; // Two pair
            }
        }
    }
    else
    {
        combo = max_combo;
    }

    printf("found %d %ds\n", combo.rank, combo.value);

    free(combos);
    return combo;
}

int cmp_hand(const void *a, const void *b)
{
    int result, i, card1, card2;

    const hand_t *h1 = a;
    const hand_t *h2 = b;

    combo_t c1 = find_combos(*h1);
    combo_t c2 = find_combos(*h2);

    if (c1.rank - c2.rank != 0)
    {
        return c1.rank > c2.rank;
    }

    i = 0;
    card1 = h1->cards[i];
    card2 = h2->cards[i];
    result = card1 - card2;
    while (result == 0 && i < HAND_SIZE)
    {
        card1 = h1->cards[i];
        card2 = h2->cards[i];
        result = card1 - card2;
        i++;
    }
    return result;
}

int calc_result1(hand_t *hands, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += (i + 1) * hands[i].bid;
        for (int j = 0; j < HAND_SIZE; j++)
        {
            printf("%d ", hands[i].cards[j]);
        }
        
        printf(":%d * %d\n", hands[i].bid, i + 1);
    }
    return sum;
}

int part1()
{
    hand_t *hands;
    int nbr_hands, in, temp, state, i_hand, i_card;
    int temp_hand[HAND_SIZE];

    nbr_hands = SIZE;
    hands = calloc(nbr_hands, sizeof(hand_t));

    state = 0;
    temp = 0;
    i_hand = 0;
    i_card = 0;
    in = '?';
    while (in != EOF)
    {
        in = getchar();
        switch (in)
        {
        case ' ':
            state = 1;
            for (int i = 0; i < HAND_SIZE; i++)
            {
                hands[i_hand].cards[i] = temp_hand[i];
            }
            i_card = 0;
            break;

        case '\n':
        case EOF:
            state = 0;
            hands[i_hand].bid = temp;
            temp = 0;
            i_hand++;
            break;
        default:
            if (state)
            {
                if (isdigit(in))
                {
                    temp *= 10;
                    temp += in - '0';
                }
            }
            else
            {
                if (isdigit(in))
                {
                    temp = in - '0';
                }
                else
                {
                    switch (in)
                    {
                    case 'T':
                        temp = 10;
                        break;
                    case 'J':
                        temp = 11;
                        break;
                    case 'Q':
                        temp = 12;
                        break;
                    case 'K':
                        temp = 13;
                        break;
                    case 'A':
                        temp = 14;
                        break;
                    default:
                        break;
                    }
                }
                if (temp != 0 && i_card < HAND_SIZE)
                {
                    temp_hand[i_card] = temp;
                    temp = 0;
                    i_card++;
                }
            }

            break;
        }
    }
    printf("nbr_hands: %d | hands_read: %d\n", nbr_hands, i_hand);
    qsort(hands, nbr_hands, sizeof(hand_t), cmp_hand);
    int result = calc_result1(hands, nbr_hands);
    free(hands);
    return result;
}

int main(void)
{
    int result1 = part1();
    printf("Result = %d\n", result1); //254572894
    return 0;
}
