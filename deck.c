// deck data structure by Claude Randalle

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#include "deck.h"


// * * * helper functions * * *


/* 
	return the size of the left cut deck
	the returned value is a 'rough' / random
	value emulating how a human cuts a deck

	note: if called multiple times withing
	the time frame of 1 second, all instances
	will be the same value unless the input
	'a' is changed between instances. In 
	normal usage, a can be left as 0.
*/
int left_deck(int a);

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// print the deck
	printf("original deck:\n");
	showDeck(d);

	// perfect riffle shuffle deck
	
	for (int i = 0; i < 9; i++) {
		printf("\nriffle shuffling deck:\n");
		d = riffle(d, 0);
		showDeck(d);
	}
	

	// show deck
	

	// free deck
	freeDeck(d);

	return 0;	
}

Card newCard(char suit, int value) {
	Card c = malloc(sizeof(*c));

	if (c == NULL) {
		fprintf(stderr, "couldn't allocate memory for card\n");
		exit(EXIT_FAILURE);
	}

	c->suit = suit;
	c->value = value;
	c->bellow = NULL;
	c->above = NULL;

	return c;
}

// create a new empty deck
Deck newEmptyDeck(void) {
	// allocate memory for the new deck
	// and initialize values
	Deck d = malloc(sizeof(*d));
	d->top = NULL;
	d->bottom = NULL;
	d->size = 0;

	// check memory was allocated correctly
	if (d == NULL) {
		fprintf(stderr, "couldn't allocate memory for the deck\n");
		exit(EXIT_FAILURE);
	}

	return d;
}

// create a new ordered deck
Deck newStandardDeck(void) {
	
	// initalize new empty deck
	Deck d = newEmptyDeck();

	// declare variables for card creating
	Card c;
	int v;
	char s;
	
	// make each card in the standard deck
	// and add it to the deck
	for (int i = 0; i < 4; i++) {		
		// set the suit 
		switch (i) {
			case 0:
				s = 's'; break;
			case 1:
				s = 'h'; break;
			case 2:
				s = 'c'; break;
			default:
				s = 'd';
		}

		// create a card for each value of the suit
		for (int v = 14; v >= 2; v--) {
			
			// create the card
			c = newCard(s, v);
			
			// add the card to the deck
			d = addCard(c, d);
		}
	}

	return d;
}

// add a card to a deck
Deck addCard(Card c, Deck d) {
	// check valid deck and card
	if (d == NULL || c == NULL) {
		fprintf(stderr, "couldn't allocate memory for the deck\n");
		exit(EXIT_FAILURE);
	}

	// set up a curr
	//Card cur = NULL;

	// add card to the top of the deck
	if (d->top == NULL) {
		d->top = c;
		d->bottom = c;
	} else {
		d->top->above = c;
		d->top->above->bellow = d->top;
		d->top = d->top->above;
	}
	//cur = c;
	d->size++;

	return d;
}

// remove and return the top card from the deck
Card removeTopCard(Deck d) {
	
	if (d->size == 0) return newCard('x', 0);

	// set card c as the top card
	Card c = d->top;

	// check this is not the last card
	if (d->top == d->bottom) {
		c = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else {
		// remove links between top card
		// and the card bellow it
		d->top->bellow->above = NULL;
		d->top = d->top->bellow;
		c->bellow = NULL;
	}

	// deincrament size of deck
	d->size--;

	// return the top card
	return c;	
}

Card removeBottomCard(Deck d) {
	if (d->size == 0) return newCard('x', 0);

	// set card c as the bottom card
	Card c = d->bottom;

	// check this is not the last card
	if (d->top == d->bottom) {
		//c = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else {
		// remove links between bottom card
		// and the card above it
		d->bottom = d->bottom->above;
		d->bottom->bellow = NULL;
		c->above = NULL;
	}

	// deincrament size of deck
	d->size--;

	// return the top card
	return c;	
}

// print out entire deck to stdin
void showDeck(Deck d) {
	
	Card c = d->top;

	if (c == NULL) {
		printf("this deck is empty\n");
		return;
	}

	printf("TOP->");
	while (c != NULL) {
		
		printCard(c);
		printf(" ");

		if (c == d->bottom) {
			break;
		} else {
			c = c->bellow;
		}
	}
	printf("<-BOTTOM\n");	
}

// free all memory used for the deck
void freeDeck(Deck d) {
	Card c = d->top;
	while (c != NULL) {
		Card temp = c;
		c = c->bellow;
		free(temp);
	}
	free(d);
}

void printCard(Card c) {
	if (c == NULL) return;

	switch (c->value) {
		case 11:
			printf("J%c", c->suit); break;
		case 12:
			printf("Q%c", c->suit); break;
		case 13:
			printf("K%c", c->suit); break;
		case 14:
			printf("A%c", c->suit); break;
		default:
			printf("%d%c", c->value, c->suit);
	}
}

int left_deck(int a) {
	
	// generate random number [0:99]
	srand(time(NULL) + a);
	int r = rand() % 100;
	
	// determine size of left deck
	int n = 26;
	
	if (r < 2) {
		n = 21;
	} else if (r < 4) {
		n = 31;
	} else if (r < 7) {
		n = 22;
	} else if (r < 10) {
		n = 30;
	} else if (r < 15) {
		n = 23;
	} else if (r < 20) {
		n = 29;
	} else if (r < 30) {
		n = 24;
	} else if (r < 40) {
		n = 28;
	} else if (r < 55) {
		n = 25;
	} else if (r < 70) {
		n = 27;
	}	

	return n;
}

/*
	cut the deck "around about" 
	half way, and then return 
	two seperate decks in DDeck

	allocate memory for the new
	DDeck

	destoy old deck
*/



DoubleDeck cutDeck(Deck d, int size) {
	// allocate memory for new DDeck
	DoubleDeck dd = malloc(sizeof(*dd));

	// initalized the double deck
	dd->left = newEmptyDeck();
	dd->right = d;											// assumption 3

	// get random number
	int left_deck_size = left_deck(0);

	// loop through removing cards and adding them 
	// to the left double deck
	Card c;													// assumption 2
	for (int i = 0; i < size; i++) {
		c = removeBottomCard(d);
		dd->left = addCard(c, dd->left);
	}

	return dd;
}

Deck riffle(Deck d, int kind) {

	/*
	kind:
		0 	perfect shuffle
		1	human like shuffle
	*/

	// check valid deck
	if (d == NULL) {
		printf("this deck is empty\n");
		exit(1);
	} else if (d->size < 2) {
		printf("cannot shuffle a deck with less than 2 cards\n");
	}

	// declare variables
	int size; 
	int count = 0;
	DoubleDeck dd;
	Deck return_deck;
	Card c, insert_card;

	// get size to cut the deck
	if (kind == 0) {
		size = 26;
	} else if (kind == 1) {
		size = left_deck(0);
	} else {
		printf("[riffle] must specifiy kind of riffle shuffle\n0	perfect shuffle\n1	human life inperfect shuffle\n");
		exit(1);
	}

	// cut the deck
	dd = cutDeck(d, size);

	// riffle shuffle deck
	if (kind == 0) {
		c = dd->right->bottom;
		while (c != NULL) {
			if ((count % 2) == 0) {
				insert_card = removeBottomCard(dd->left);
				insert_card->bellow = c;
				
				if (c == dd->right->top) {
					c->above = insert_card;
					dd->right->top = insert_card;
				} else {
					insert_card->above = c->above;
					c->above = insert_card;
					insert_card->above->bellow = insert_card;
				}
			} 

			c = c->above;			
			count++;
		}
	}

	// assign the return deck to the right deck
	return_deck = dd->right;

	// free double deck structure
	freeDeck(dd->left);
	free(dd);

	// return the right deck 
	return return_deck;
}








