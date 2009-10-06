#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define DECK_SIZE 52
#define SUIT_SIZE 13
#define HAND_SIZE 2
#define SEATS 7

enum bank_stages {BLIND=0, BANK3=3, BANK4, BANK5};
enum suit_t {HEARTS=3, DIAMONDS, CLUBS, SPADES};
enum rank_t {TWO=2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
enum com_t {KICKER=1, PAIR, THREE_OF, FOUR_OF, TWOPAIRS, STRAIGHT, FLUSH, F_HOUSE, STR_FLUSH, ROYAL};
enum statements {NO=0, YES};

struct card {
    enum suit_t suit;
    enum rank_t rank;
    short int used;
    };

struct combo {
    enum com_t type; /* combination type */
    struct card depend[2];
    struct card kicker; /* card-kicker */
    struct card active[HAND_SIZE+BANK5];
    };

struct player {
    char name[15];
    int points;
    short int seat;
    struct combo c;
    struct card hand[HAND_SIZE];
    };

void deck_array_generate(struct card *deck);
void cards_printf(struct card *cards, int ARR_SIZE);
void random_fill_in(struct card *deck, struct card *array, int arr_length);
void find_kicker(struct card hand[HAND_SIZE], struct combo c);
void build_active(struct card bank[BANK5], struct card hand[HAND_SIZE], struct card active[HAND_SIZE+BANK5]);
void search_combination(struct combo c, int bank_size);

#endif /* MAIN_H_INCLUDED */
