#include "game.h"
#include "deck.h"

/* result of the match card bet */
float match_card(struct state *game){
	
	struct card card_1 = game->before_card;
	struct card card_2 = game->after_card;

	/* Match Rank & Suit & Rank = Ace */
	if ( (card_1.c_rank == card_2.c_rank) && 
	    (card_1.c_suit == card_2.c_suit) &&
	    (card_1.c_rank == ACE) )
		return 100.0; // 80.0
	/* Match Rank and Rank = Ace */
	else if ( (card_1.c_rank == card_2.c_rank) &&
		    (card_1.c_rank == ACE))
		return 20.0;
	/* Match Rank and Suit */
	else if ( (card_1.c_rank == card_2.c_rank) &&
		    (card_1.c_suit == card_2.c_suit))
		return 6.0;
	/* Match Rank */
	else if ( ( card_1.c_rank == card_2.c_rank ) )
		return 3.0;
	/* Match Suit */
	else if ( (card_1.c_suit == card_2.c_suit ))
		return 1.0;
	/* No Match! */
	else 
		return -1.0;
	

}

/* result of the match dice bet */
float match_dice(struct state *game){

	int d_1 = game->die_1;
	int d_2 = game->die_2;

	/* dice match and are sixes*/
	if ( (d_1 == d_2) && (d_1 == 6) )
		return 10.0;
	/* dice match */
	else if ( d_1 == d_2) 
		return 3.0;
	/* no match ! */
	else
		return -1.0; 

}
