#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define DECK_SIZE 52
#define SUIT_SIZE 13
#define BANK_SIZE 5
#define HAND_SIZE 2
#define ACTIVE BANK_SIZE+HAND_SIZE
#define SEATS 7

enum bank_stages {BLIND=0, BANK3=3, BANK4, BANK5};
enum suit_t {HEARTS=3, DIAMONDS, CLUBS, SPADES};
enum rank_t {TWO='2', THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN=11, JACK='J', QUEEN='Q', KING='K', ACE='A'};
enum com_t {HIGHEST=1, PAIR, TWOPAIRS, THREE_OF, STRAIGHT, FLUSH, F_HOUSE, FOUR_OF, STR_FLUSH, ROYAL};
enum statements {NO=0, YES};

struct card {
    enum suit_t suit;
    enum rank_t rank;
    short int used;
    };

struct combo {
    enum com_t type; /* combination type */
    struct card depend;
    struct card kicker; /* card-kicker */
    struct card active[ACTIVE];
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
void build_active(int bank[BANK_SIZE][2], int hand[HAND_SIZE][2], int active[ACTIVE][2]);
void search_combination(int active[ACTIVE][2], int combo[]);

#endif /* MAIN_H_INCLUDED */
