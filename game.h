#ifndef GAME_H
#define GAME_H

#include "deck.h"

struct state {
	int die_1;
	int die_2;
	struct card before_card;
	struct card after_card;	
};

/* roll the dice and deal the cards*/
void init_game(struct state *game);

/* Beat Before */
int beat_before(struct state *game);

/* Beat After */
int beat_after(struct state *game);

/* Beat Both */
int beat_both(struct state *game);

/* Match Card Payout */
float match_card(struct state *game);

/* Match Dice Payout */
float match_dice(struct state *game);


#endif
