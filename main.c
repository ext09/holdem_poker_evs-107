#include <stdlib.h>
#include <stdio.h>

#define DECK_SIZE 52

int main()
{
    int deck[DECK_SIZE][2];
    int i, m=1, n=1;
    int s; /* TEMPORARY*/

    /* filling in the cards' ID in array "deck" */
    for(i=0; i<=DECK_SIZE-1; i++)
    {
        s=i+1; /* TEMPORARY*/
        printf("%d ", s); /* TEMPORARY*/

        deck[i][0]=m;
        deck[i][1]=n;

        printf("%d  %d", deck[i][0], deck[i][1]); /* TEMPORARY*/

        if((i+1)%13==0) /* stuff to make the suit number go from 1 to 4 */
            m++;
        if(n==13) /* stuff to make card nuber in exact suit go from 1 to 13*/
            n=1;
        else
            n++;


        printf("\n"); /* TEMPORARY*/
    }

    return 0;
}
