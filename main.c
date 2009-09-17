#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DECK_SIZE 52
#define BANK_SIZE 5
#define HAND_SIZE 2
#define ACTIVE BANK_SIZE+HAND_SIZE


void deck_array_generate(int deck[DECK_SIZE][2]);
void deck_array_printf(int deck[DECK_SIZE][2]);


int main()
{
    int deck[DECK_SIZE][2];

    int combo[5];
    /*
    array combo
    combo[0]-combination #

    DO NOT EDIT THIS INFO ** DO NOT EDIT THIS INFO

    if combo[0]=1 (highest card)
    combo[1] = suit
    combo[2] = card # in suit

    if combo[0]=2 (one pair)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = card # in suit (for pair)

    if combo[0]=3 (two pairs)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = card # in suit (for 1st pair)
    combo[4] = card # in suit (for 2nd pair)

    if combo[0]=4 (three of a kind)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = card # in suit (for triplet)

    if combo[0]=5 (Straight)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[4] = highest card in straight

    if combo[0]=6 (Flush)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = highest card in flush

    if combo[0]=7 (Full House)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = card # in suit (for triplet)
    combo[4] = card # in suit (for pair)

    if combo[0]=8 (Four of a kind)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = card # in suit (for cuartet)

    if combo[0]=9 (Straight Flush)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = highest card for straight flush

    if combo[0]=10 (Royal Flush)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = card # in suit (for 1st pair)
    combo[4] = card # in suit (for 2nd pair)

    DO NOT EDIT THIS INFO ** DO NOT EDIT THIS INFO
    */

    int bank[BANK_SIZE];
    int hand[HAND_SIZE];

    srand(time(NULL));

    deck_array_generate(deck);
    deck_array_printf(deck);

    /*formula for randomizer
    card=rand()%52;
    printf("random card number: %d\n", card);
    */
    return 0;
}


/*
    deck_array_generate

    RECEIVES: integer array with # of cols - DECK_SIZE, and # of rows - 2
    EFFECT:
        -fills 1st col with suit number (from 1 to 4)
        -fills 2nd col with card number in each suit (from 1 to 13)
*/
void deck_array_generate(int deck[DECK_SIZE][2])
{
    int i, m=1, n=1;



    for(i=0; i<DECK_SIZE; i++)
    {
        deck[i][0]=m;
        deck[i][1]=n;

        if((i+1)%13==0) /* stuff to make the suit number go from 1 to 4 */
            m++;
        if(n==13) /* stuff to make card number in exact suit go from 1 to 13*/
            n=1;
        else
            n++;
    }
}


/*
    deck_array_printf

    RECEIVES: integer array with # of cols - DECK_SIZE, and # of rows - 2
    EFFECT:
        -prints out the whole array with lines' numbers
*/
void deck_array_printf(int deck[DECK_SIZE][2])
{
    int i;
    printf("\tDeck array:\n\n");
    for(i=1; i<=DECK_SIZE; i++)
    {
        printf("\t%d\t%d\t%d\n", i, deck[i-1][0], deck[i-1][1]);
    }
}



/*
    highest_card

    RECEIVES: array HAND[] and array combo[]
    EFFECT:
        -writes the highest card info to combo
*/
void highest_card(int hand[HAND_SIZE][2], int combo[])
{
    int i;
    if(hand[0][1]>hand[1][1])
        i=0;
    else
        i=1;

    combo[1]=hand[i][0];
    combo[2]=hand[i][1];
}


/*
    search_combination NOT FINISHED _ NOT TESTED

    RECEIVES: array BANK[] and array HAND[] and array combo[]
    EFFECT:
        -returns the number of combination (int)
*/
void search_combination(int bank[BANK_SIZE][2], int hand[HAND_SIZE][2], int combo[])
{
    int i, j;
    int active[ACTIVE][2];


    /* We copy first BANK and then HAND to ACTIVE just to make things easier here :) */
    for(i=0; i<ACTIVE; i++)
    {
        if(i<5)
        {
            active[i][0]=bank[i][0];
            active[i][1]=bank[i][1];
        }
        else
        {
            active[i][0]=hand[i-BANK_SIZE][0];
            active[i][1]=hand[i-BANK_SIZE][1];
        }
    }


    /* from here we start searching the combinations*/

    /* PAIR SEARCH */
    for(i=0; i<ACTIVE; i++)
    {
        for(j=1; j<ACTIVE; j++)
        {
            if(active[i][1]==active[j][1]&&i!=j)
            {
                combo[0]=2; /* PAIR FOUND*/
                combo[3]=active[i][1];
            }
        }
    }

    /* TWO PAIRS SEARCH */

}
