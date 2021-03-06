#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "game.h"
#include "deck.h"

struct stats{
	double mean;
	double stddev;
	int num_wins;
	int num_trials;
	int num_ties;
};

/* zero the statistics */
void init_stats(struct stats *gs){

	gs->mean = 0.0;
	gs->stddev = 0.0;
	gs->num_wins = 0;
	gs->num_trials = 0;
	gs->num_ties = 0;
}

/* incrementally update the statistics */
void inc_update_stats(struct stats *gs, float game_outcome, int trial){
	
	double prev_mean = gs->mean;
	gs->mean+= (game_outcome - gs->mean)/trial;
	gs->stddev+=(game_outcome - prev_mean)*(game_outcome - gs->mean);
	gs->num_trials++;

	if(game_outcome > 0)
		gs->num_wins++;
	else if(game_outcome == 0)
		gs->num_ties++;
}

void print_stats(struct stats *gs){
	printf("The mean is: %f\nThe std dev is: %f\nPercent of wins: %f\nPercent of ties: %f\n\n", 
	    gs->mean, gs->stddev, (double)gs->num_wins/(double)gs->num_trials, 
		(double)gs->num_ties/(double)gs->num_trials);
}

static void usage(){
	extern char *__progname;
	fprintf(stderr, "usage %s num_trials\n", __progname);
	exit(1);
}

int main(int argc, char *argv[]){

	char *ep;
	u_long temp, trials;
	struct state *gp;
	struct state game;
	
	/* structures to hold the stats */
	struct stats b_before;
	struct stats b_after;
	struct stats b_both;
	struct stats m_card, m_dice;
	
	struct stats game_stats;	

	struct card deck[DECKS*CARDS*SUITS];

	int i;
	int card_index = 0;
	float outcome; 
	int die_total;

	gp = &game;

	if (argc != 2)
		usage();

	temp = strtoul(argv[1], &ep, 10);
	if (*argv[1] == '\0'|| *ep != '\0'){
		fprintf(stderr, "%s - not a number\n", argv[1]);
		usage();
	}

	if (argv[1][0] == '-'){
		fprintf(stderr, "%s - no negative numbers\n", argv[1]);
		usage();
	}
	
	if (( errno == ERANGE && temp == ULONG_MAX ) && (temp > 1)){
		fprintf(stderr, "%s - value out of range\n", argv[1]);
		usage();
	}
	trials = temp;

	/* seed the random number generator */
	srand(time(NULL));
	
	/* initialize the deck */
	init_deck(deck);
	
	/* shuffle the cards */
	shuffle(deck);

	/* initialize the statistics structs */
	init_stats(&b_before);
	init_stats(&b_after);
	init_stats(&b_both);
	init_stats(&m_card);
	init_stats(&m_dice);
	init_stats(&game_stats);

	/* run the simulations */
	for (i = 0 ; i < trials ; i++){
		
		/* initialize the game */
		game.die_1 = rand()%6 + 1;
		game.die_2 = rand()%6 + 1;
		die_total = game.die_1 + game.die_2;

		game.before_card = deck[card_index];
		game.after_card = deck[card_index+1];
		card_index+=2;		

		/* beat before */
		if (die_total == 12)
			outcome = 4.0; 
		else if ( die_total > game.before_card.value )
			outcome = 1.0;
		else if ( die_total < game.before_card.value )
			outcome = -1.0;
		else
			outcome = 0.0;							
		inc_update_stats(&b_before, outcome, i+1);
 		inc_update_stats(&game_stats, outcome, i+1);
		
		/* beat after */
		if (die_total == 12)
			outcome = 4.0; 
		else if ( die_total > game.after_card.value )
			outcome = 1.0;
		else if ( die_total < game.after_card.value )
			outcome = -1.0;
		else
			outcome = 0.0;

		inc_update_stats(&b_after, outcome, i+1);
		inc_update_stats(&game_stats, outcome, i+1);
		
		/* beat both */
		if (die_total == 12)
			outcome = 6.0;

		else if ( (die_total > game.after_card.value) &&
		    (die_total > game.before_card.value) )
			outcome = 3.0;
		else if ( (die_total == game.after_card.value) &&
			(die_total == game.before_card.value))
			outcome = 0.0;	
		else
			outcome = -1.0;

		inc_update_stats(&b_both, outcome, i+1);
		inc_update_stats(&game_stats, outcome, i+1);
		
		/* match card */
		outcome = match_card(gp);
		inc_update_stats(&m_card, outcome, i+1);
		inc_update_stats(&game_stats, outcome, i+1);
		
		/* match dice */
		outcome = match_dice(gp);
		inc_update_stats(&m_dice, outcome, i+1);
 		inc_update_stats(&game_stats, outcome, i+1);

		if(card_index > (DECKS*SUITS*CARDS - 52)){
			card_index = 0;
			shuffle(deck);
		}

	}

	/* finalize the standard deviations */	
	b_before.stddev = sqrt(b_before.stddev/(trials-1));
	b_after.stddev = sqrt(b_after.stddev/(trials-1));
	b_both.stddev = sqrt(b_both.stddev/(trials-1));
	m_card.stddev = sqrt(m_card.stddev/(trials-1));
	m_dice.stddev = sqrt(m_dice.stddev/(trials-1));
	game_stats.stddev = sqrt(game_stats.stddev/(trials-1));

	/* Print the statistics of the each game's square */
	printf("Beat Before:\n");
	print_stats(&b_before);	
	printf("Beat After:\n");
	print_stats(&b_after);	
	printf("Beat Both:\n");
	print_stats(&b_both);	
	printf("Match Card:\n");
	print_stats(&m_card);	
	printf("Match Dice:\n");
	print_stats(&m_dice);	
	
	/* Print the game's overall EV */
	printf("Game Statistics:\n");
	print_stats(&game_stats);	

	return 0;

}
