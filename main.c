#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "menu.h"

#define DECK_SIZE 52
#define BANK_SIZE 5
#define HAND_SIZE 2
#define ACTIVE BANK_SIZE+HAND_SIZE


void deck_array_generate(int deck[DECK_SIZE][2]);
void double_array_printf(int array[][2], int ARR_SIZE);
void random_fill_in(int deck[DECK_SIZE][2], int array[][2], int arr_length);
void highest_card(int hand[HAND_SIZE][2], int combo[]);
void build_active(int bank[BANK_SIZE][2], int hand[HAND_SIZE][2], int active[ACTIVE][2]);
void search_numbers(int active[ACTIVE][2], int combo[]);


int main(int argc, char* args[])
{
    int deck[DECK_SIZE][2];
    int combo[5]; /* documentation for combo is in the end of this file */
    int bank[BANK_SIZE][2];
    int hand[HAND_SIZE][2];

    srand(time(NULL));

        /* $$$$$$$$$$$$$$$$$ MAIN STRUCTURE' PROTOTYPE $$$$$$$$$$$$$$$$ */
    while(1)
    {
        if(MainMenu()==3)
        {
            return 0;
        }

        deck_array_generate(deck);

        printf("\tDeck Array:\n\n");
        double_array_printf(deck, DECK_SIZE);


    /* FOR TESTING PURPOSES */
        random_fill_in(deck, bank, BANK_SIZE);

        printf("\n\nBANK:\n");
        double_array_printf(bank, BANK_SIZE);
        return 0;
    }
}



    /*
    random_fill_in

    filling in random cards from the DECK to ANY ARRAY (HAND or BANK)
    */
void random_fill_in(int deck[DECK_SIZE][2], int array[][2], int arr_length)
{
    int i,j,random;
    for(i=0; i<arr_length; i++)
    {
        random=rand()%52; /* main formula generating random card number */
        array[i][0]=deck[random][0];
        array[i][1]=deck[random][1];
        for(j=0; j<i; j++)
        {
            if(array[i][0]==array[j][0]&&array[i][1]==array[j][1])
                i--;
        }
    }
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
void double_array_printf(int array[][2], int ARR_SIZE)
{
    char suit;
    int i;
    for(i=1; i<=ARR_SIZE; i++)
    {
        printf("\t%d\t", i);
        switch(array[i-1][0]) {
            case 1:
                suit=3;
                printf("%c ", suit);
                break;
            case 2:
                suit=4;
                printf("%c ", suit);
                break;
            case 3:
                suit=5;
                printf("%c ", suit);
                break;
            case 4:
                suit=6;
                printf("%c ", suit);
                break;
        }
        switch(array[i-1][1]) {
            case 1:
                suit=2;
                printf("%d\n", suit);
                break;
            case 2:
                suit=3;
                printf("%d\n", suit);
                break;
            case 3:
                suit=4;
                printf("%d\n", suit);
                break;
            case 4:
                suit=5;
                printf("%d\n", suit);
                break;
            case 5:
                suit=6;
                printf("%d\n", suit);
                break;
            case 6:
                suit=7;
                printf("%d\n", suit);
                break;
            case 7:
                suit=8;
                printf("%d\n", suit);
                break;
            case 8:
                suit=9;
                printf("%d\n", suit);
                break;
            case 9:
                suit=10;
                printf("%d\n", suit);
                break;
            case 10:
                suit='J';
                printf("%c\n", suit);
                break;
            case 11:
                suit='Q';
                printf("%c\n", suit);
                break;
            case 12:
                suit='K';
                printf("%c\n", suit);
                break;
            case 13:
                suit='T';
                printf("%c\n", suit);
                break;
        }

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
    build_active

    simply fill array ACTIVE with the info from BANK and HAND
    */
void build_active(int bank[BANK_SIZE][2], int hand[HAND_SIZE][2], int active[ACTIVE][2])
{
    int i;

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
}


    /*  'PAIR'  ,  'TWO PAIRS'    AND   'THREE OF A KIND'   SEARCH*/
void search_numbers(int active[ACTIVE][2], int combo[])
{
    int array[ACTIVE][2], i, j;
    int pair=0, triplet=0;
    /*
        array[i][0] - card number
        array[i][1] - number of the same cards

    */

    /* we should turn array[] to NULL just to be sure we won't screw up with this enormous bunch of shite :) */
    for(i=0; i<ACTIVE; i++)
        array[i][1]=0;
    i=j=0;

    array[j][0]=active[i][1];
    array[j][1]++;

    for(i=1; i<ACTIVE; i++)
    {
        if(array[j][0]!=active[i][1])
        {
            j++;
            array[j][0]=active[i][1];
            array[j][1]++;
        }
        else if(array[j][0]==active[i][1])
        {
            array[j][0]=active[i][1];
            array[j][1]++;
        }
    }

    /* Once we've filled up the array we can check*/
    for(i=0; array[i][1]!=0; i++)
    {
        if(array[i][1]==2)
        {
            pair++;
            if(pair<=1)
            {
                combo[0]=2;
                combo[3]=array[i][0];
            }
            else
            {
                combo[0]=3;
                combo[4]=array[i][0];
            }
        }
        if(array[i][1]==3)
        {
            triplet++;
            if(triplet<=1)
            {
                combo[0]=4;
                combo[3]=array[i][0];
            }
            else
            {
                if(array[i][0]>combo[3])
                    combo[3]=array[i][0];
            }
        }
    }

}




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
