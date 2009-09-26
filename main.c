#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "main.h"
#include "menu.h"

int main(int argc, char* args[])
{
    struct player players[SEATS];
    struct card deck[DECK_SIZE], bank[BANK_SIZE];

    short int i;
    srand(time(NULL));

        /* $$$$$$$$$$$$$$$$$ MAIN STRUCTURE' PROTOTYPE $$$$$$$$$$$$$$$$ */
    while(1)
    {
        switch(MainMenu())
        {
            case -1:
                return 0;
            case 1:
                puts("the game begins\n");
                break;
        }

        deck_array_generate(deck);
                        /* UNDER COMMENT SIGNS - JUST TO CLEAN UP THE OUTPUT */

        printf("\tDeck Array:\n\n");
        cards_printf(deck, DECK_SIZE);
        random_fill_in(deck, bank, BANK_SIZE);
        printf("\n\nBANK:\n");
        cards_printf(bank, BANK_SIZE);
        printf("\n\nPlayers' Personal Info\n\n");
        for (i=0; i<SEATS; i++)
        {
            printf("\n\nPlayer %d\n", i+1);
            random_fill_in(deck, players[i].hand, HAND_SIZE);
            find_kicker(players[i].hand, players[i].c);
            printf("\nHAND:\n");
            cards_printf(players[i].hand, HAND_SIZE);
        }
/*      build_active(bank, hand, active);
        printf("\n\nACTIVE:\n");
        cards_printf(active, ACTIVE);
        search_combination(active, combo);
        print_combo(combo);
    */


        printf("\nYou may test you code here.\n");
        return 0;
    }
}



void random_fill_in(struct card *deck, struct card *array, int arr_length)
{
    int i=0, random;

    for(i=0; i<arr_length; i++)
    {
        random=rand()%DECK_SIZE;
        if(deck[random].used!=YES)
        {
            array[i].suit=deck[random].suit;
            array[i].rank=deck[random].rank;
            deck[i].used=YES;
        }
        else
            i--;
    }
}


void deck_array_generate(struct card *deck)
{
    int i, m=1, n=1;

    for(i=0; i<DECK_SIZE; i++)
    {
        switch(m) {
            case 1:  deck[i].suit=HEARTS; break;
            case 2:  deck[i].suit=DIAMONDS; break;
            case 3:  deck[i].suit=CLUBS; break;
            case 4:  deck[i].suit=SPADES; break;
        }
        switch(n) {
            case 1:  deck[i].rank=TWO; break;
            case 2:  deck[i].rank=THREE; break;
            case 3:  deck[i].rank=FOUR; break;
            case 4:  deck[i].rank=FIVE; break;
            case 5:  deck[i].rank=SIX; break;
            case 6:  deck[i].rank=SEVEN; break;
            case 7:  deck[i].rank=EIGHT; break;
            case 8:  deck[i].rank=NINE; break;
            case 9:  deck[i].rank=TEN; break;
            case 10: deck[i].rank=JACK; break;
            case 11: deck[i].rank=QUEEN; break;
            case 12: deck[i].rank=KING; break;
            case 13: deck[i].rank=ACE; break;
        }
        deck[i].used=NO;

        if((i+1)%13==0) /* stuff to make the suit number go from 1 to 4 */
            m++;
        if(n==13) /* stuff to make card number in exact suit go from 1 to 13*/
            n=1;
        else
            n++;
    }
}


void cards_printf(struct card *cards, int ARR_SIZE)
{
    int i;
    for(i=0; i<ARR_SIZE; i++)
    {
        printf("\t%d\t", i);
        printf("%c\t%c\n", cards[i].suit, cards[i].rank);
    }
}


void find_kicker(struct card hand[HAND_SIZE], struct combo c)
{
    int i;
    if(hand[0].rank>hand[1].rank)
        i=0;
    else
        i=1;

        c.kicker.suit=hand[i].suit;
        c.kicker.rank=hand[i].rank;

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
void search_combination(int active[ACTIVE][2], int combo[])
{
    int array[SUIT_SIZE], i;
    short int pair=0, triplet=0, four=0;
    /*
        i+1 - card number
        array[i] - number of the same cards
    */

    /* we should turn array[] to NULL just to be sure we won't screw up with this enormous bunch of shite :) */
    for(i=0; i<SUIT_SIZE; i++)
        array[i]=0;

    /*for i cycles active[]. in there we should decide weither to put card on some previous place or on the new one. */
    for(i=0; i<ACTIVE; i++)
    {
        array[active[i][1]-1]++;
    }

    printf("array:\n");
    for(i=0; i<SUIT_SIZE; i++)
    {
        printf("\t%d\t%d\n", i+1, array[i]);
    }
    /* Once we've filled up the array we can check*/
    for(i=0; i<SUIT_SIZE; i++)
    {
        switch(array[i])
        {
            case 2:
                if(combo[0]<=2)
                {
                    pair++;
                    if(pair<=1)         /* one pair */
                    {
                        combo[0]=2;
                        combo[3]=i+1;
                    }
                    else            /* two pairs */
                    {
                        combo[0]=3;
                        if(combo[3]<(i+1))
                        {
                            combo[4]=combo[3];
                            combo[3]=i+1;
                        }
                        else
                            combo[4]=i+1;
                    }
                }
                break;
            case 3:
                if(combo[0]<=4)
                {
                    triplet++;
                    if(triplet==1&&pair>0)          /* full house */
                    {
                        combo[0]=7;
                        combo[4]=i+1;
                    }
                    else if(triplet==1&&pair==0)        /* three */
                    {
                        combo[0]=4;
                        combo[4]=i+1;
                    }
                    else if(triplet>1) /* if we find one more triple we write only the bigger one */
                    {
                        if((i+1)>combo[4])
                            combo[4]=i+1;
                    }
                }
                break;
            case 4:             /* four */
                four++;
                combo[0]=8;
                combo[3]=i+1;
                break;
        }
    }

    /*combo[] check for consistency*/
    printf("\n\ncombo\n");
    for(i=0; i<5; i++)
    {
        printf("\t%d\n", combo[i]);
    }

    /* searching all other combinations here*/
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
    combo[3] = NULL
    combo[4] = card # in suit (for triplet)

    if combo[0]=5 (Straight)
    combo[1] = suit (for highest card)
    combo[2] = card # in suit (for highest card)
    combo[3] = highest card in straight

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
    combo[3] = suit (for royal flush)

    DO NOT EDIT THIS INFO ** DO NOT EDIT THIS INFO
    */

/*
Идеи по реализации поиска комбинаций
массив структур card размера active

0) определить кикер в руке, записать, обновить тип комбинации
1) в графу used записывать кол-во карт с одинаковым rank'ом - для нахождения количественных комбинаций
(пара, две пары, тройка, четверка, фул хаус)
2) отсортировать список полученный в пункте 1) по возрастанию rank'a. искать 5 карт с rank'ом отличающимся от соседа на 1 -
- для поиска комбинаций(стрит)
3) проверить графу suit если имеется 5 и более карт одинаковой масти - (флэш)
вкупе со 2ым условием - (стрит флэш)
вкупе с предыдущим проверить последнюю карту стрит флеша - если Туз - (флэш рояль)

*/

