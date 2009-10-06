#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "main.h"

int main(int argc, char* args[])
{
    struct player players[SEATS];
    struct card deck[DECK_SIZE], bank[BANK5];

    short int i;
    srand(time(NULL));

        /* $$$$$$$$$$$$$$$$$ MAIN STRUCTURE' PROTOTYPE $$$$$$$$$$$$$$$$ */
    while(1)
    {
        deck_array_generate(deck);
                        /* UNDER COMMENT SIGNS - JUST TO CLEAN UP THE OUTPUT */

        printf("\tDeck Array:\n\n");
        cards_printf(deck, DECK_SIZE);
        random_fill_in(deck, bank, BANK5);
        printf("\n\nBANK:\n");
        cards_printf(bank, BANK5);
        printf("\n\nPlayers' Personal Info\n\n");
        for (i=0; i<SEATS; i++)
        {
            printf("\n\nPlayer %d\n", i+1);
            random_fill_in(deck, players[i].hand, HAND_SIZE);
            printf("\nHAND:\n");
            cards_printf(players[i].hand, HAND_SIZE);

            build_active(bank, players[i].hand, players[i].c.active);
            printf("\n\nACTIVE:\n");
            cards_printf(players[i].c.active, HAND_SIZE+BANK5);
            find_kicker(players[i].hand, players[i].c);
            /*search_combination(players[i].c, BANK5); */
            printf("\n\n\t%d\n", players[i].c.type);
        }

        printf("\nYou may test you code here.\n");
        return 0;
    }
}




void deck_array_generate(struct card *deck)
{
    int i, m=1, n=2;

    for(i=0; i<DECK_SIZE; i++)
    {
        deck[i].suit=m+2;
        deck[i].rank=n;
        deck[i].used=NO;

        if((i+1)%13==0) /* stuff to make the suit number go from 1 to 4 */
            m++;
        if(n==13) /* stuff to make card number in exact suit go from 1 to 13*/
            n=2;
        else
            n++;
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
            deck[random].used=YES;
        }
        else
            i--;
    }
}

void cards_printf(struct card *cards, int ARR_SIZE)
{
    int i;
    for(i=0; i<ARR_SIZE; i++)
    {
        printf("\t%d\t", i);
        printf("%c\t%d\n", cards[i].suit, cards[i].rank);
    }
}


void find_kicker(struct card hand[HAND_SIZE], struct combo c)
{
    int i;
    if(hand[0].rank>hand[1].rank)
        i=0;
    else if(hand[0].rank<=hand[1].rank)
        i=1;
    c.type=KICKER;
    c.kicker.suit=hand[i].suit;
    c.kicker.rank=hand[i].rank;
}

    /*
    build_active

    simply fill array ACTIVE with the info from BANK and HAND
    */
void build_active(struct card bank[BANK5], struct card hand[HAND_SIZE], struct card active[HAND_SIZE+BANK5])
{
    int i;

    for(i=0; i<HAND_SIZE+BANK5; i++)
    {
        if(i<2)
        {
            active[i].suit=hand[i].suit;
            active[i].rank=hand[i].rank;
        }
        else
        {
            active[i].suit=bank[i-HAND_SIZE].suit;
            active[i].rank=bank[i-HAND_SIZE].rank;
        }
    }
}


    /*  'PAIR'  ,  'TWO PAIRS'    AND   'THREE OF A KIND'   SEARCH*/
void search_combination(struct combo c, int bank_size)
{
    short int i, j, temp;
    short int ACTIVE = HAND_SIZE+bank_size;

    /* sorting active here*/
    for(i=1; i<ACTIVE; i++)
    {
        if(c.active[i].rank<c.active[i-1].rank)
        {
            for(j=i; c.active[j].rank<c.active[j-1].rank&&j>0; j--)
            {
                temp=c.active[j].rank;
                c.active[j].rank=c.active[j-1].rank;
                c.active[j-1].rank=temp;

                temp=c.active[j].suit;
                c.active[j].suit=c.active[j-1].suit;
                c.active[j-1].suit=temp;
            }
        }
    }

    printf("\nsorted active\n");
    cards_printf(c.active, ACTIVE);

    temp=1; /* int for number of repetitions - unnecessary*/
    for(i=1; i<ACTIVE; i++)
    {
        if(c.active[i].rank==c.active[i-1].rank&&c.type==KICKER) /*pair*/
        {
            c.type=PAIR;
            c.depend[0].suit=c.active[i].suit;
            c.depend[0].rank=c.active[i].rank;
            if((i+1)<ACTIVE)
            {
                if(c.active[i].rank==c.active[i+1].rank)
                {
                    c.type=THREE_OF;
                    if((i+2)<ACTIVE)
                    {
                        if(c.active[i].rank==c.active[i+2].rank)
                            c.type=FOUR_OF;
                    }
                }
            }
        }
        else if(c.active[i].rank==c.active[i-1].rank&&c.type!=KICKER)
        {
            switch(c.type) {
                case PAIR:
                    c.type=TWOPAIRS;
                    if(c.depend[0].rank>c.active[i].rank)
                    {
                        c.depend[1].suit=c.active[i].suit;
                        c.depend[1].rank=c.active[i].rank;
                    }
                    else
                    {
                        c.depend[1].suit=c.depend[0].suit;
                        c.depend[1].rank=c.depend[0].rank;
                        c.depend[0].suit=c.active[i].suit;
                        c.depend[0].rank=c.active[i].rank;
                    }
                    break;
                case THREE_OF:
                    c.type=F_HOUSE;
                    c.depend[1].suit=c.active[i].suit;
                    c.depend[1].rank=c.active[i].rank;
                    break;
                case FOUR_OF:
                    break;
                case TWOPAIRS:
                    if(c.active[i].rank>c.depend[0].rank)
                    {
                        c.depend[1].suit=c.depend[0].suit;
                        c.depend[1].rank=c.depend[0].rank;
                        c.depend[0].suit=c.active[i].suit;
                        c.depend[0].rank=c.active[i].rank;
                    }
                    else if(c.active[i].rank>c.depend[1].rank)
                    {
                        c.depend[1].suit=c.active[i].suit;
                        c.depend[1].rank=c.active[i].rank;
                    }
                    break;
                case F_HOUSE:
                    if(c.depend[1].rank<c.active[i].rank)
                    {
                        c.depend[1].suit=c.active[i].suit;
                        c.depend[1].rank=c.active[i].rank;
                    }
                    else
                        ;
                    break;
            }
        }
    }

    /* after these manipulations we should've dealt with all numeric combination,

    just to leave STRAIGHT, FLUSH, STRAIGHT FLUSH and ROYAL FLUSH*/


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

