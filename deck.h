#ifndef DECK_H
#define DECK_H

#define DECKS 4
#define CARDS 13 /* was 13 */
#define SUITS 4

/* card suit definition */
enum suit {
	HEARTS = 3, 
	SPADES = 0, 
	CLUBS = 2, 
	DIAMONDS = 1
};

/* card rank definition */
enum rank {
        ACE = 0,
        TWO = 1,
        THREE = 2,
        FOUR = 3,
        FIVE = 4,
        SIX = 5,
        SEVEN = 6,
        EIGHT = 7,
        NINE = 8,
        TEN = 9,
        JACK = 10,
        QUEEN = 11,
        KING = 12
};

/* card definintion */
struct card {
        enum rank c_rank;
        enum suit c_suit;
	int value;
};

/* print card to standard output */
void print_card(struct card pc);

/* Initialize the deck of cards */
void init_deck(struct card *deck);

/* implement the Fisher-Yates shuffle algorithm */
void shuffle(struct card *deck);

#endif
