#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define DECK_SIZE 52


void deck_array_generate(int deck[DECK_SIZE][2]);
void deck_array_printf(int deck[DECK_SIZE][2]);


int main()
{
    int deck[DECK_SIZE][2];
    int card;
    srand(time(NULL));

    deck_array_generate(deck);
    deck_array_printf(deck);

    /*formula for randomizer*/
    card=rand()%52;
    printf("random card number: %d\n", card);

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
