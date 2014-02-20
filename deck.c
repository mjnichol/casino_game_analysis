#include "deck.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void init_deck(struct card *deck){

	int i, j, k;
	int card_index = 0;
	struct card card;

	for(i = 0 ; i < DECKS ; i++){
		for(j = 0 ; j < CARDS ; j++){
			for(k = 0 ; k < SUITS ; k++){
				
				card.c_suit = k;
				card.c_rank = j;
				if( j > 9 )
					printf("what the fuck!\n");

				if ( j == 0 )
					card.value = 11; 
				else if (j > 9)
					card.value = j - (j%10);
				else
					card.value = j + 1;
				
				deck[card_index] = card;
				card_index++;
			}
		}
	} 

}

/* make sure to seed the randomw number generator */
void shuffle(struct card *deck){
	
	struct card temp;
	int i;
	int j;

	for( i = (DECKS*CARDS*SUITS) - 1 ; i > 0 ; i--){
		j = rand()%(i+1);
		temp = deck[j];
		deck[j] = deck[i];
		deck[i] = temp;	
	}

}

void print_card(struct card pc){

	char *suit;
	char *rank;

	/* assign the rank */
	if (pc.c_rank == ACE)
		rank = "Ace";
	else if (pc.c_rank == TWO)
		rank = "Two";
	else if (pc.c_rank == THREE)
		rank = "Three";
	else if (pc.c_rank == FOUR)
		rank = "Four";
	else if (pc.c_rank == FIVE)
		rank = "Five";
	else if (pc.c_rank == SIX)
		rank = "Six";
	else if (pc.c_rank == SEVEN)
		rank = "Seven";
	else if (pc.c_rank == EIGHT)
		rank = "Eight";
	else if (pc.c_rank == NINE)
		rank = "Nine";
	else if (pc.c_rank == TEN)
		rank = "Ten";
	else if (pc.c_rank == JACK)
		rank = "Jack";
	else if (pc.c_rank == QUEEN)
		rank = "Queen";
	else if (pc.c_rank == KING)
		rank = "King";
	else
		rank = "ERROR";
	
	/* Assign the suit */
	if (pc.c_suit == HEARTS)
		suit = "Hearts";
	else if (pc.c_suit == SPADES)
		suit = "Spades";
	else if (pc.c_suit == CLUBS)
		suit = "Clubs";
	else if (pc.c_suit == DIAMONDS)
		suit = "Diamonds";
	else
		suit = "ERROR";

	printf("%s of %s\n",rank,suit);

}
